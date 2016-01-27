/*
* Copyright (c) 2016, Sascar
* All rights reserved.
*
* THIS SOFTWARE IS PROVIDED BY SASCAR ''AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL SASCAR BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CURL_WRAPPER_HPP
#define CURL_WRAPPER_HPP

#include <string>
#include <curl/curl.h>

using namespace std;

namespace Sascar
{

class CurlWrapper
{
	public:
		CurlWrapper();
		~CurlWrapper();

		void Init();
		void Cleanup();
		void Reset();

		template <typename T, typename V>
		void SetOption(T option, V parameter)
		{
			curl_easy_setopt(pCurl, option, parameter);
		}

		static string sBuffer;
		static int Writer(char *data, size_t size, size_t nmemb, string *buffer)
		{
			int result = 0;
			if (buffer != NULL)
			{
				buffer->append(data, size * nmemb);
				result = size * nmemb;
			}

			return result;
		}

		void Perform();
		bool IsOK();
		CURLcode GetError();
		string GetErrorMessage();
		void UrlComposer(const char *message, ...);

		inline const char* GetUrlWithParams() const { return urlWithParams; }

	private:
		void ErrorBuffer(char* buffer);

	private:
		char urlWithParams[2048];
		CURL *pCurl;
		char cErrorBuffer[CURL_ERROR_SIZE + 1];
		CURLcode cCode;
};

} // namespace

#endif // CURL_WRAPPER_HPP
