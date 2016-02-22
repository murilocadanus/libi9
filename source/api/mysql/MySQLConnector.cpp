#include "api/mysql/MySQLConnector.hpp"
#include "util/Log.hpp"

#define TAG "[MySQL Connector] "

namespace Sascar {

MysqlConnector::MysqlConnector()
{
}

MysqlConnector::~MysqlConnector()
{
	/*delete pRes;
	delete pPrepStmt;
	delete pStmt;
	delete pCon;*/
}

/*void MysqlConnector::ManageException(sql::SQLException& e)
{
	if (e.getErrorCode() != 0)
	{
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
}*/

void MysqlConnector::Initialize()
{
	mysql_init(&dbConnection);
}

void MysqlConnector::Connect(const string &host, const string &user, const string &password, const string &scheme)
{
	try
	{
		mysql_real_connect(&dbConnection, host.c_str(), user.c_str(), password.c_str(), scheme.c_str(), 0, NULL, 0);
	}
	catch (int e)
	{
		e = mysql_errno(&dbConnection);
		Error(TAG "FATAL ERROR: %d: %s", e, mysql_error(&dbConnection));
	}

	/*try
	{
		pDriver = get_driver_instance();
		pCon = pDriver->connect(sHost, sUser, sPassword);
	}
	catch (sql::SQLException &e)
	{
		ManageException(e);
	}*/
}

void MysqlConnector::Disconnect()
{
	try
	{
		mysql_close(&dbConnection);
	}
	catch (int e)
	{
		e = mysql_errno(&dbConnection);
		Error(TAG "FATAL ERROR: %d: %s", e, mysql_error(&dbConnection));
	}
}


void MysqlConnector::SwitchDb(const string& dbName)
{
	/*try
	{
		pCon->setSchema(dbName);
		pStmt = pCon->createStatement();
	}
	catch (sql::SQLException &e)
	{
		ManageException(e);
	}*/
}

void MysqlConnector::Prepare(const string& query)
{
	try
	{
		mysql_stmt_prepare(&stmt, query.c_str(), query.length());
	}
	catch (int e)
	{
		e = mysql_stmt_errno(&stmt);
		Error(TAG "FATAL ERROR: %d: %s", e, mysql_error(&dbConnection));
	}
}

void MysqlConnector::SetInt(const int& num, const int& data)
{
	//pPrepStmt->setInt(num, data);
}

void MysqlConnector::SetString(const int& num, const string& data)
{
	//pPrepStmt->setString(num, data);
}

void MysqlConnector::Execute(const string& query)
{
	try
	{
		if (query != "")
		{
			mysql_query(&dbConnection, query.c_str());
			//pRes = pStmt->executeQuery(query);
		}
		/*else
		{
			pRes = pPrepStmt->executeQuery();
			pPrepStmt->close();
		}*/
	}
	catch (int e)
	{
		e = mysql_stmt_errno(&stmt);
		Error(TAG "FATAL ERROR: %d: %s", e, mysql_error(&dbConnection));
	}
}

bool MysqlConnector::Fetch()
{
	return 0;//pRes->next();
}

string MysqlConnector::Print(const string& field)
{
	return "";//pRes->getString(field);
}

string MysqlConnector::Print(const int& index)
{
	return "";//pRes->getString(index);
}

}
