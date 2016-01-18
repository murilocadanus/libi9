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

#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>
#include "Enum.hpp"

using namespace std;

namespace Sascar {

class Configuration
{
	public:
		Configuration();
		virtual ~Configuration();

		static Configuration instance;

		static inline Configuration *GetInstance()
		{
			return &Configuration::instance;
		}

		static inline void DestroyInstance(){}

		void Load(const string &file);

		inline void SetTitle(const string title){ sTitle = title; }
		inline const string &GetTitle() const { return sTitle; }

		inline void SetMongoDBHost(const string mongoDBHost){ sMongoDBHost = mongoDBHost; }
		inline const string &GetMongoDBHost() const { return sMongoDBHost; }

		inline void SetMongoDBCollection(const string mongoDBCollection){ sMongoDBCollection = mongoDBCollection; }
		inline const string &GetMongoDBCollection() const { return sMongoDBCollection; }

		inline void SetServiceURL(const string serviceURL){ sServiceURL = serviceURL; }
		inline const string &GetServiceURL() const { return sServiceURL; }

		inline void SetServiceKey(const string serviceKey){ sServiceKey = serviceKey; }
		inline const string &GetServiceKey() const { return sServiceKey; }

		inline void SetServiceTimeOut(const u_int32_t serviceTimeOut){ iServiceTimeOut = serviceTimeOut; }
		inline const u_int32_t &GetServiceTimeOut() const { return iServiceTimeOut; }

		inline eReaderType GetReaderType() const { return nReaderType; }

	private:
		string sTitle;
		string sMongoDBHost;
		string sMongoDBCollection;
		string sServiceURL;
		string sServiceKey;
		u_int32_t iServiceTimeOut;

		eReaderType nReaderType;
};

#define pConfiguration Configuration::GetInstance()

} // end namespace

#endif // CONFIGURATION_HPP
