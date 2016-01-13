#include "Configuration.hpp"
#include "File.hpp"
#include "util/Log.hpp"

namespace Sascar {

Configuration Configuration::instance;

Configuration::Configuration()
	: sMongoDBHost("")
	, sMongoDBCollection("")
{
}

Configuration::~Configuration()
{
}

void Configuration::Load(const string &file)
{
	File *f = new File(file);
	if(f && f->GetData())
		Log("------------- Readed");

	sMongoDBHost = "mngdbsascloud.sasweb-fleet.net";
	sMongoDBCollection = "murilo.posicao";

	if (f)
		delete(f);
	f = nullptr;
}

} // namespace

