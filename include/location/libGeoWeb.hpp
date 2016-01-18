#ifndef __LIBGEOWEB_H_
#define __LIBGEOWEB_H_

#include <curl/curl.h>
#include "location/revgeo.hpp"
#include <string>

class LibGeoWeb
{
	public:
		CURL *curlPostRevgeo;
		CURLcode resultURLCode;
		struct curl_slist *headers;
		std::string readBufferRevgeo;
		char webParams[128];
		char urlWithParams[2048];

	public:
		void converteEncode( const char* encodeOriginal, const char* encodeNovo, char* bufferEntrada, char* bufferSaida, size_t maximo );
		void Url(const char* message, ...);
		u_int32_t revGeoWeb(struct endereco_posicao_mapa *end, u_int32_t timeOut);
		void finalizaGeoWeb();
};
#endif // _LIBGEOWEB_H_
