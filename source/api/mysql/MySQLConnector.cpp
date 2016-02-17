#include "api/mysql/MySQLConnector.hpp"

namespace Sascar {

MysqlConnector::MysqlConnector()
	: sHost("tcp://127.0.0.1:3306")
	, sUser("root")
	, sPassword("")
{
}

MysqlConnector::MysqlConnector(const string &host, const string &user, const string &password)
{
	sHost = host; sUser = user; sPassword = password;
}

MysqlConnector::~MysqlConnector()
{
	delete pRes;
	delete pPrepStmt;
	delete pStmt;
	delete pCon;
}

void MysqlConnector::ManageException(sql::SQLException& e)
{
	if (e.getErrorCode() != 0)
	{
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
}

void MysqlConnector::Connect()
{
	try
	{
		pDriver = get_driver_instance();
		pCon = pDriver->connect(sHost, sUser, sPassword);
	}
	catch (sql::SQLException &e)
	{
		ManageException(e);
	}
}

void MysqlConnector::Disconnect()
{
	try
	{
		pCon->close();
	}
	catch (sql::SQLException &e)
	{
		ManageException(e);
	}
}


void MysqlConnector::SwitchDb(const string& dbName)
{
	try
	{
		pCon->setSchema(dbName);
		pStmt = pCon->createStatement();
	}
	catch (sql::SQLException &e)
	{
		ManageException(e);
	}
}

void MysqlConnector::Prepare(const string& query)
{
	try
	{
		pPrepStmt = pCon->prepareStatement(query);
	}
	catch (sql::SQLException &e)
	{
		ManageException(e);
	}
}

void MysqlConnector::SetInt(const int& num, const int& data)
{
	pPrepStmt->setInt(num, data);
}

void MysqlConnector::SetString(const int& num, const string& data)
{
	pPrepStmt->setString(num, data);
}

void MysqlConnector::Execute(const string& query)
{
	try
	{
		if (query != "")
		{
			pRes = pStmt->executeQuery(query);
		}
		else
		{
			pRes = pPrepStmt->executeQuery();
			pPrepStmt->close();
		}
	}
	catch (sql::SQLException &e)
	{
		ManageException(e);
	}
}

bool MysqlConnector::Fetch()
{
	return pRes->next();
}

string MysqlConnector::Print(const string& field)
{
	return pRes->getString(field);
}

string MysqlConnector::Print(const int& index)
{
	return pRes->getString(index);
}

}
