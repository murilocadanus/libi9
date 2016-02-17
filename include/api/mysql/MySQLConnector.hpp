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

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

namespace Sascar {

class MysqlConnector
{
	public:
		MysqlConnector();
		MysqlConnector(const string &host, const string &user, const string &password);
		~MysqlConnector();

		void ManageException(sql::SQLException& e);
		void Connect();
		void Disconnect();
		void SwitchDb(const string& dbName);
		void Prepare(const string& query);
		void SetInt(const int& num, const int& data);
		void SetString(const int& num, const string& data);
		void Execute(const string& query = "");
		bool Fetch();
		string Print(const string& field);
		string Print(const int& index);

	private:
		string sHost;
		string sUser;
		string sPassword;
		sql::Driver *pDriver;
		sql::Connection *pCon;
		sql::Statement *pStmt;
		sql::PreparedStatement *pPrepStmt;
		sql::ResultSet *pRes;
};

} // namespace

#endif // MYSQLCONNECTOR_HPP
