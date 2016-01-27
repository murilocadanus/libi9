#include <memory>
#include <algorithm>
#include <cstdarg>
#include <curl/curl.h>

#include "api/curl/CurlWrapper.hpp"

namespace Sascar {

string CurlWrapper::sBuffer = "";

CurlWrapper::CurlWrapper()
	: pCurl(curl_easy_init())
	, cCode(CURLE_OK)
{
}

CurlWrapper::~CurlWrapper()
{
	curl_easy_cleanup(pCurl);
}

void CurlWrapper::Init()
{
}

void CurlWrapper::Cleanup()
{
	curl_easy_cleanup(pCurl);
}

void CurlWrapper::Reset()
{
	curl_easy_reset(pCurl);
	fill(cErrorBuffer, cErrorBuffer + CURL_ERROR_SIZE + 1, 0);
	ErrorBuffer(cErrorBuffer);
	cCode = CURLE_OK;
}

void CurlWrapper::ErrorBuffer(char *buffer)
{
	SetOption(CURLOPT_ERRORBUFFER, (void*)buffer);
}

void CurlWrapper::Perform()
{
	cCode = curl_easy_perform(pCurl);
}

bool CurlWrapper::IsOK()
{
	return cCode == CURLE_OK;
}

CURLcode CurlWrapper::GetError()
{
	return cCode;
}

string CurlWrapper::GetErrorMessage()
{
	return string(cErrorBuffer);
}

void CurlWrapper::UrlComposer(const char *message, ...)
{
	va_list ap;

	va_start(ap, message);
	vsnprintf(urlWithParams, 2048, message, ap);
	va_end(ap);
}

} // namespace
