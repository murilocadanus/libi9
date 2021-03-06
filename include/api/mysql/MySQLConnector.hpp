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

#ifndef MYSQLCONNECTOR_HPP
#define MYSQLCONNECTOR_HPP

#include <string>
#include <mysql/mysql.h>

using namespace std;

namespace Sascar {

class MysqlConnector
{
	public:

		MysqlConnector();
		virtual ~MysqlConnector();

		static MysqlConnector instance;

		static inline MysqlConnector *GetInstance()
		{
			return &MysqlConnector::instance;
		}

		static inline void DestroyInstance(){}

		//void ManageException(sql::SQLException& e);
		void Initialize();
		void Connect(const string &host, const string &user, const string &password, const string &scheme);
		void Disconnect();
		void SwitchDb(const string& dbName);
		void Prepare(const string& query);
		void SetInt(const int& num, const int& data);
		void SetString(const int& num, const string& data);
		bool Execute(const string& query = "");
		MYSQL_RES* Result();
		void FreeResult(MYSQL_RES *result);
		bool Fetch();
		int InsertedID();
		MYSQL_ROW FetchRow(MYSQL_RES *result);
		string Print(const string& field);
		string Print(const int& index);

	private:
		MYSQL dbConnection;
		MYSQL_STMT stmt;

		/*sql::Driver *pDriver;
		sql::Connection *pCon;
		sql::Statement *pStmt;
		sql::PreparedStatement *pPrepStmt;
		sql::ResultSet *pRes;*/
};

#define pMysqlConnector MysqlConnector::GetInstance()

} // namespace

#endif // MYSQLCONNECTOR_HPP
