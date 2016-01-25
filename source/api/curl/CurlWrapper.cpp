#include <memory>
#include <algorithm>
#include <curl/curl.h>

#include "api/curl/CurlWrapper.hpp"

namespace Sascar {

CurlWrapper::CurlWrapper()
	: pCurl(curl_easy_init()),
	  cCode(CURLE_OK)
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
	std::fill(cErrorBuffer, cErrorBuffer + CURL_ERROR_SIZE + 1, 0);
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

std::string CurlWrapper::GetErrorMessage()
{
	return std::string(cErrorBuffer);
}

} // namespace
