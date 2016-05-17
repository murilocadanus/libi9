#include "Configuration.hpp"
#include "File.hpp"
#include "util/Log.hpp"
#include "util/String.hpp"
#include "Reader.hpp"

namespace Sascar {

Configuration Configuration::instance;

Configuration::Configuration()
	: sTitle("")
	, sMongoDBHost("")
	, sMongoDBCollections()
	, nReaderType(eReaderType::Default)
{
}

Configuration::~Configuration()
{
}

void Configuration::Load(const string &file)
{
	File *f = new File(file);

	if(f && f->GetData())
	{
		Reader r(f);

		sTitle = r.ReadString("sTitle", "");
		sMongoDBHost = r.ReadString("sMongoDBHost", "");
		sMongoDBCollections = StringUtil::split(r.ReadString("sMongoDBCollections", ""), '|');
		sServiceURL = r.ReadString("sServiceURL", "");
		sServiceKey = r.ReadString("sServiceKey", "");
		iServiceTimeOut = r.ReadU32("lServiceTimeOut", 5L);
		iSleepProcessInterval = r.ReadU32("iSleepProcessInterval", 10L);
		iQueryLimit = r.ReadU32("iQueryLimit", 500);
		sMySQLHost = r.ReadString("sMySQLHost", "");
		sMySQLUser = r.ReadString("sMySQLUser", "");
		sMySQLPassword = r.ReadString("sMySQLPassword", "");
		sMySQLScheme = r.ReadString("sMySQLScheme", "");
		sAppListeningPath = r.ReadString("sAppListeningPath", "");
		iProjectId = r.ReadU32("iProjectId", 1);
		sActiveMQTarget = r.ReadString("sActiveMQTarget", "");
		sActiveMQUser = r.ReadString("sActiveMQUser", "");
		sActiveMQPassword = r.ReadString("sActiveMQPassword", "");
		sActiveMQQueue = r.ReadString("sActiveMQQueue", "");
		iActiveMQTimeout = r.ReadU32("iActiveMQTimeout", 30000L);
	}

	if (f)
		delete(f);

	f = nullptr;
}

} // namespace

