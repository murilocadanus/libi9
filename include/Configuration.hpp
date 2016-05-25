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
#include <vector>
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

		inline void SetMongoDBUser(const string mongoDBUser){ sMongoDBUser = mongoDBUser; }
		inline const string &GetMongoDBUser() const { return sMongoDBUser; }

		inline void SetMongoDBPassword(const string mongoDBPassword){ sMongoDBPassword = mongoDBPassword; }
		inline const string &GetMongoDBPassword() const { return sMongoDBPassword; }

		inline void SetMongoDBAuthMechanism(const string mongoDBAuthMechanism){ sMongoDBAuthMechanism = mongoDBAuthMechanism; }
		inline const string &GetMongoDBAuthMechanism() const { return sMongoDBAuthMechanism; }

		inline void SetMongoDBDatabase(const string mongoDBDatabase){ sMongoDBDatabase = mongoDBDatabase; }
		inline const string &GetMongoDBDatabase() const { return sMongoDBDatabase; }

		inline void SetMongoDBCollections(const std::vector<std::string> mongoDBCollections){ sMongoDBCollections = mongoDBCollections; }
		inline const std::vector<std::string> &GetMongoDBCollections() const { return sMongoDBCollections; }

		inline void SetServiceURL(const string serviceURL){ sServiceURL = serviceURL; }
		inline const string &GetServiceURL() const { return sServiceURL; }

		inline void SetServiceKey(const string serviceKey){ sServiceKey = serviceKey; }
		inline const string &GetServiceKey() const { return sServiceKey; }

		inline void SetServiceTimeOut(const uint32_t serviceTimeOut){ iServiceTimeOut = serviceTimeOut; }
		inline const uint32_t &GetServiceTimeOut() const { return iServiceTimeOut; }

		inline void SetSleepProcessInterval(const uint32_t sleepProcessInterval){ iSleepProcessInterval = sleepProcessInterval; }
		inline const uint32_t &GetSleepProcessInterval() const { return iSleepProcessInterval; }

		inline void SetQueryLimit(const uint32_t queryLimit){ iQueryLimit = queryLimit; }
		inline const uint32_t &GetQueryLimit() const { return iQueryLimit; }

		inline void SetMySQLHost(const string mysqlHost){ sMySQLHost = mysqlHost; }
		inline const string &GetMySQLHost() const { return sMySQLHost; }

		inline void SetMySQLUser(const string mysqlUser){ sMySQLUser = mysqlUser; }
		inline const string &GetMySQLUser() const { return sMySQLUser; }

		inline void SetMySQLPassword(const string mysqlPassword){ sMySQLPassword = mysqlPassword; }
		inline const string &GetMySQLPassword() const { return sMySQLPassword; }

		inline void SetMySQLScheme(const string mysqlScheme){ sMySQLScheme = mysqlScheme; }
		inline const string &GetMySQLScheme() const { return sMySQLScheme; }

		inline void SetAppListeningPath(const string appListeningPath){ sAppListeningPath = appListeningPath; }
		inline const string &GetAppListeningPath() const { return sAppListeningPath; }

		inline void SetProjectId(const uint32_t projectId){ iProjectId = projectId; }
		inline const uint32_t &GetProjectId() const { return iProjectId; }

		inline eReaderType GetReaderType() const { return nReaderType; }

		inline void SetActiveMQTarget(const uint32_t activeMQTarget){ sActiveMQTarget = activeMQTarget; }
		inline const string &GetActiveMQTarget() const { return sActiveMQTarget; }

		inline void SetActiveMQUser(const uint32_t activeMQUser){ sActiveMQUser = activeMQUser; }
		inline const string &GetActiveMQUser() const { return sActiveMQUser; }

		inline void SetActiveMQPassword(const uint32_t activeMQPassword){ sActiveMQPassword = activeMQPassword; }
		inline const string &GetActiveMQPassword() const { return sActiveMQPassword; }

		inline void SetActiveMQQueue(const uint32_t activeMQQueue){ sActiveMQQueue = activeMQQueue; }
		inline const string &GetActiveMQQueue() const { return sActiveMQQueue; }

		inline void SetActiveMQTimeout(const uint32_t activeMQTimeout){ iActiveMQTimeout = activeMQTimeout; }
		inline const uint32_t &GetActiveMQTimeout() const { return iActiveMQTimeout; }

	private:
		string sTitle;
		string sMongoDBHost;
		string sMongoDBUser;
		string sMongoDBPassword;
		string sMongoDBDatabase;
		string sMongoDBAuthMechanism;
		std::vector<std::string> sMongoDBCollections;
		string sServiceURL;
		string sServiceKey;
		uint32_t iServiceTimeOut;
		uint32_t iSleepProcessInterval;
		uint32_t iQueryLimit;
		string sMySQLHost;
		string sMySQLUser;
		string sMySQLPassword;
		string sMySQLScheme;
		string sAppListeningPath;
		uint32_t iProjectId;
		eReaderType nReaderType;
		string sActiveMQTarget;
		string sActiveMQUser;
		string sActiveMQPassword;
		string sActiveMQQueue;
		uint32_t iActiveMQTimeout;
};

#define pConfiguration Configuration::GetInstance()

} // end namespace

#endif // CONFIGURATION_HPP
