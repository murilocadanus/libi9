#include <curl/curl.h>
#include <iconv.h>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/reader.h>

#include "location/libGeoWeb.hpp"

#include "util/Log.hpp"

using namespace rapidjson;

/*
 * Converte de um encode para outro (Ex. de UTF-8 para ISO-8859-1)
 */
void LibGeoWeb::converteEncode( const char* encodeOriginal, const char* encodeNovo, char* bufferEntrada, char* bufferSaida, size_t maximo )
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

void LibGeoWeb::Url(const char *message, ...)
{
	va_list ap;

	va_start(ap, message);
	vsnprintf(urlWithParams, 2048, message, ap);
	va_end(ap);
}

/*
 * Faz a resolucao de endereco
 */
u_int32_t LibGeoWeb::revGeoWeb(struct endereco_posicao_mapa *end, u_int32_t timeOut)
{
	if(!urlWithParams)
	{
		fprintf(stderr, "Empty URL request\n");
		return 0;
	}

	Log(urlWithParams);

	// Declara as variaveis para fazer o request da resolucao de endereco.
	Document document;

	headers = NULL;
	readBufferRevgeo.clear();

	//Inicializa CURL apenas umas vez por programa, quando for chamado
	//if(curlPostRevgeo == NULL)
	//{
		// Configura o header para o request
		headers = curl_slist_append(headers, "Accept: application/json");
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, "charset: utf-8");

		//Monta CURL para request
		curlPostRevgeo = curl_easy_init();
		curl_easy_setopt(curlPostRevgeo, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curlPostRevgeo, CURLOPT_HTTPGET, 1);
		curl_easy_setopt(curlPostRevgeo, CURLOPT_WRITEFUNCTION, writeCurlCallback);
		curl_easy_setopt(curlPostRevgeo, CURLOPT_WRITEDATA, &readBufferRevgeo);
		curl_easy_setopt(curlPostRevgeo, CURLOPT_TIMEOUT, timeOut);
	//}

	// Faz o request com curl
	//curl_easy_setopt(curlPostRevgeo, CURLOPT_POSTFIELDSIZE, strlen(webParams));
	//curl_easy_setopt(curlPostRevgeo, CURLOPT_POSTFIELDS, webParams);

	// Cria os parametros para o request

	curl_easy_setopt(curlPostRevgeo, CURLOPT_URL, urlWithParams);

	resultURLCode = curl_easy_perform(curlPostRevgeo);

	if(resultURLCode != CURLE_OK)
	{
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(resultURLCode));
		return 0;
	}

	// Verifica se o endereco foi encontrado
	if (readBufferRevgeo.length() == 0)
	{
		fprintf(stderr, "[R1] - Read buffer vazio - Ultimo erro: %s\n");
		return 0;
	}

	// Faz o parse do JSON
	if (document.Parse<0>(readBufferRevgeo.c_str()).HasParseError())
	{
		fprintf(stderr, "[R2] - Nao foi possivel realizar o parser do JSON\n--JSON enviado: %s\n --Recebido: %s\n", webParams, readBufferRevgeo.c_str());
		return 0;
	}

	// Verifica se existem dados
	if (!document["results"].IsArray())
	{
		fprintf(stderr, "[R3] - Sem address list\n");
		return 0;
	}

	const Value& results = document["results"];
	assert(results.IsArray());

	const Value& addresses = results[0]["address_components"];
	assert(addresses.IsArray());

	for (SizeType i = 0; i < addresses.Size(); i++)
	{
		std::string type = addresses[i]["types"][0].GetString();

		// --- PAIS ---
		// Faz a coversao de UTF-8 para ISO-8859-1 do pais.
		if (type == "country")
		{
			std::string pais = addresses[i]["short_name"].GetString();
			strcpy(end->pais, pais.c_str());
		}

		// --- ESTADO ---
		// Faz a coversao de UTF-8 para ISO-8859-1 do estado.
		if (type == "administrative_area_level_1")
		{
			std::string uf = addresses[i]["short_name"].GetString();
			strcpy(end->uf, uf.c_str());
		}

		// --- MUNICIPIO ---
		// Faz a coversao de UTF-8 para ISO-8859-1 do municipio.
		if (type == "locality")
		{
			std::string municipio = addresses[i]["long_name"].GetString();
			strcpy(end->municipio, municipio.c_str());
		}

		// --- BAIRRO ---
		// Faz a coversao de UTF-8 para ISO-8859-1 do municipio.
		if (type == "sublocality_level_1")
		{
			std::string bairro = addresses[i]["long_name"].GetString();
			strcpy(end->bairro, bairro.c_str());
		}

		// --- RUA ---
		// Faz a coversao de UTF-8 para ISO-8859-1 da rua.
		if (type == "route")
		{
			std::string rua = addresses[i]["long_name"].GetString();
			strcpy(end->rua, rua.c_str());
		}

		// --- NUMERO ---
		// Faz a coversao de UTF-8 para ISO-8859-1 do numero.
		if (type == "street_number")
		{
			std::string numero = addresses[i]["long_name"].GetString();
			strcpy(end->numero, numero.c_str());
		}
	}

	curl_slist_free_all(headers);

	/* always cleanup */
	curl_easy_cleanup(curlPostRevgeo);

	// C'est fini
	return 1;

}

void LibGeoWeb::finalizaGeoWeb()
{
	curl_slist_free_all(headers);
	curl_easy_cleanup(curlPostRevgeo);
	curlPostRevgeo = NULL;
}

