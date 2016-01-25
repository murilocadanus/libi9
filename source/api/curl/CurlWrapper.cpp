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

int CurlWrapper::Writer(char *data, size_t size, size_t nmemb, string *buffer)
{
	int result = 0;
	if (buffer != NULL)
	{
		buffer->append(data, size * nmemb);
		result = size * nmemb;
	}

	return result;
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

} // namespace
