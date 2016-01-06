#include <curl/curl.h>
#include <iconv.h>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/reader.h>

#include "location/libGeoWeb.hpp"

extern "C"
{
#include <string.h>
#include <stdlib.h>
}

using namespace rapidjson;

/*
 * Converte de um encode para outro (Ex. de UTF-8 para ISO-8859-1)
 */
void converteEncode( const char* encodeOriginal, const char* encodeNovo, char* bufferEntrada, char* bufferSaida, size_t maximo )
{
	size_t tmOriginal;

	iconv_t cd = iconv_open( encodeNovo, encodeOriginal );

	tmOriginal = strlen( bufferEntrada );

	memset( bufferSaida, 0, maximo );

	iconv( cd, &bufferEntrada, &tmOriginal, &bufferSaida, &maximo );

	if ( iconv_close( cd ) != 0 )
	{
		memset( bufferSaida, 0, maximo );
		perror( "iconv_close" );
	}
}

/*
 * Callback do curl para adicionar no buffer o response da url requesitada.
 */
static size_t writeCurlCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

/*
 * Faz a resolucao de endereco
 */
int32_t revGeoWeb( double latit, double longit, struct endereco_posicao_mapa *end)
{
	// Declara as variaveis para fazer o request da resolucao de endereco.
	Document document;

	readBufferRevgeo.clear();

	//Inicializa CURL apenas umas vez por programa, quando for chamado
	if(curlPostRevgeo == NULL)
	{
		// Configura o header para o request
		headers = curl_slist_append(headers, "Accept: application/json");
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, "charsets: utf-8");

		//Monta CURL para request
		curlPostRevgeo = curl_easy_init();
		curl_easy_setopt(curlPostRevgeo, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curlPostRevgeo, CURLOPT_URL, REV_GEO_WEB_URL);
		curl_easy_setopt(curlPostRevgeo, CURLOPT_POST, 1);
		curl_easy_setopt(curlPostRevgeo, CURLOPT_WRITEFUNCTION, writeCurlCallback);
		curl_easy_setopt(curlPostRevgeo, CURLOPT_WRITEDATA, &readBufferRevgeo);
		curl_easy_setopt(curlPostRevgeo, CURLOPT_TIMEOUT, REV_GEO_TIMEOUT);
	}

	// Cria os parametros para o request
	sprintf(webParams, "{\"adresslocationList\":[{\"latitude\":\"%lf\",\"longitude\":\"%lf\",\"localBusca\":\"google\"}]}", latit, longit);

	// Faz o request com curl
	curl_easy_setopt(curlPostRevgeo, CURLOPT_POSTFIELDSIZE, strlen(webParams));
	curl_easy_setopt(curlPostRevgeo, CURLOPT_POSTFIELDS, webParams);
	result = curl_easy_perform(curlPostRevgeo);

	// Verifica se o endereco foi encontrado
	if (readBufferRevgeo.length() == 0) {
		fprintf(stderr, "[R1] - Read buffer vazio - Ultimo erro: %s\n");
		return 0;
	}

	// Faz o parse do JSON
	if (document.Parse<0>(readBufferRevgeo.c_str()).HasParseError()) {
		fprintf(stderr, "[R2] - N�o foi poss�vel realizar o parser do JSON\n--JSON enviado: %s\n --Recebido: %s\n", webParams, readBufferRevgeo.c_str());
		return 0;
	}

	// Verifica se existem dados
	if (!document["adresslocationList"].IsArray()) {
		fprintf(stderr, "[R3] - Sem address list\n");
		return 0;
	}

	// Verifica se o endereco foi resolvido
	if (document["adresslocationList"][0u].HasMember("msgErro")) {
		fprintf(stderr, "[R4] - Erro ao resolver endere�o\n");
		return 0;
	}

	// --- PAIS ---
	// Faz a coversao de UTF-8 para ISO-8859-1 do pais.
	if (document["adresslocationList"][0u]["country"].IsString())
	{
		std::string pais = document["adresslocationList"][0u]["country"].GetString();
		converteEncode( "UTF8",
						"LATIN1",
						(char*) pais.c_str(),
						end->pais,
						strlen((char *) pais.c_str()));
		end->pais[strlen(pais.c_str())] = '\0';
	}

	// --- ESTADO ---
	// Faz a coversao de UTF-8 para ISO-8859-1 do estado.
	if (document["adresslocationList"][0u]["state"].IsString())
	{
		std::string uf = document["adresslocationList"][0u]["state"].GetString();
		converteEncode( "UTF8",
						"LATIN1",
						(char*) uf.c_str(),
						end->uf,
						8);

		// Limita o Uf para 2 bytes, adicionando espaco na 3 posicao
		end->uf[8] = '\0';
	}

	// --- MUNICIPIO ---
	// Faz a coversao de UTF-8 para ISO-8859-1 do municipio.
	if (document["adresslocationList"][0u]["cityName"].IsString())
	{
		std::string municipio = document["adresslocationList"][0u]["cityName"].GetString();
		converteEncode( "UTF8",
						"LATIN1",
						(char*) municipio.c_str(),
						end->municipio,
						strlen((char *) municipio.c_str()));
		end->municipio[strlen(municipio.c_str())] = '\0';
	}

	// --- BAIRRO ---
	// Faz a coversao de UTF-8 para ISO-8859-1 do municipio.
	if (document["adresslocationList"][0u]["bairro"].IsString())
	{
		std::string bairro = document["adresslocationList"][0u]["bairro"].GetString();
		converteEncode( "UTF8",
						"LATIN1",
						(char*) bairro.c_str(),
						end->bairro,
						strlen((char *) bairro.c_str()));
		end->bairro[strlen(bairro.c_str())] = '\0';
	}

	// --- RUA ---
	// Faz a coversao de UTF-8 para ISO-8859-1 da rua.
	if (document["adresslocationList"][0u]["street"].IsString())
	{
		std::string rua = document["adresslocationList"][0u]["street"].GetString();
		converteEncode( "UTF8",
						"LATIN1",
						(char*) rua.c_str(),
						end->rua,
						strlen((char *) rua.c_str()));
		end->rua[strlen(rua.c_str())] = '\0';
	}

	// --- NUMERO ---
	// Faz a coversao de UTF-8 para ISO-8859-1 do numero.
	if (document["adresslocationList"][0u]["houseNumber"].IsString())
	{
		std::string numero = document["adresslocationList"][0u]["houseNumber"].GetString();
		converteEncode( "UTF8",
						"LATIN1",
						(char*) numero.c_str(),
						end->numero,
						strlen((char *) numero.c_str()));
		end->numero[strlen(numero.c_str())] = '\0';
	}

	// --- CEP ---
	// Faz a coversao de UTF-8 para ISO-8859-1 do cep.
	if (document["adresslocationList"][0u]["zip"].IsString())
	{
		std::string cep = document["adresslocationList"][0u]["zip"].GetString();
		converteEncode( "UTF8",
						"LATIN1",
						(char*) cep.c_str(),
						end->cep,
						strlen((char *) cep.c_str()));
		end->cep[strlen(cep.c_str())] = '\0';
	}

	// --- ACESSO_CARRO ---
	// Faz a coversao de UTF-8 para ISO-8859-1 do acesso_carro.
	if (document["adresslocationList"][0u]["carAccess"].IsString())
	{
		std::string acesso_carro = document["adresslocationList"][0u]["carAccess"].GetString();
		converteEncode( "UTF8",
						"LATIN1",
						(char*) acesso_carro.c_str(),
						end->acesso_carro,
						strlen((char *) acesso_carro.c_str()));
		end->acesso_carro[strlen(acesso_carro.c_str())] = '\0';
	}

	// C'est fini
	return 1;

}

void finalizaGeoWeb()
{
	curl_slist_free_all(headers);
	curl_easy_cleanup(curlPostRevgeo);
	curlPostRevgeo = NULL;
}

