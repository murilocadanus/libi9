#ifndef __LIBGEOWEB_H_
#define __LIBGEOWEB_H_
#include "location/revgeo.hpp"

// URL para chamar o web service de resolucao de endereco
//#define REV_GEO_WEB_URL "http://revgeowebdev1.sascar.com.br/revgeoWeb-webapp/resources/geolocalizacao/recuperaGeoLocalizacao"
#define REV_GEO_WEB_URL "http://revgeowebtst1.sascar.com.br/revgeoWeb-webapp/resources/geolocalizacao/recuperaGeoLocalizacao"
//#define REV_GEO_WEB_URL "http://revgeowebhom1.sascar.com.br/revgeoWeb-webapp/resources/geolocalizacao/recuperaGeoLocalizacao"
//#define REV_GEO_WEB_URL "http://revgeo.sascar-dc.br/revgeoWeb-webapp/resources/geolocalizacao/recuperaGeoLocalizacao"

// Timeout em segundos
#define REV_GEO_TIMEOUT 5L

static CURL *curlPostRevgeo = NULL;
CURLcode result;
struct curl_slist *headers = NULL;
std::string readBufferRevgeo;
char webParams[128];

#ifdef __cplusplus
extern "C"
{
#endif

void converteEncode( const char* encodeOriginal, const char* encodeNovo, char* bufferEntrada, char* bufferSaida, size_t maximo );
int32_t revGeoWeb( double latit, double longit, struct endereco_posicao_mapa *end);
void finalizaGeoWeb();

#ifdef __cplusplus
}
#endif



#endif
