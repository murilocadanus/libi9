#include "Configuration.hpp"
#include "File.hpp"
#include "util/Log.hpp"
#include "Reader.hpp"

namespace Sascar {

Configuration Configuration::instance;

Configuration::Configuration()
	: sTitle("")
	, sMongoDBHost("")
	, sMongoDBCollection("")
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
		sMongoDBCollection = r.ReadString("sMongoDBCollection", "");
	}

	if (f)
		delete(f);

	f = nullptr;
}

} // namespace

