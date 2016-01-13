#include "Configuration.hpp"
#include "File.hpp"
#include "util/Log.hpp"
#include "Reader.hpp"

namespace Sascar {

Configuration Configuration::instance;

Configuration::Configuration()
	: sMongoDBHost("")
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

		//sMongoDBHost = "mngdbsascloud.sasweb-fleet.net";
		sMongoDBHost = r.ReadString("sMongoDBHost", false);

		//sMongoDBCollection = "murilo.posicao";
		sMongoDBCollection = r.ReadString("sMongoDBCollection", false);
	}

	if (f)
		delete(f);

	f = nullptr;
}

} // namespace

