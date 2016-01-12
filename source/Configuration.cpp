#include "Configuration.hpp"

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
	// TODO create a file handler to read from it

	sMongoDBHost = "mngdbsascloud.sasweb-fleet.net";
	sMongoDBCollection = "murilo.posicao";
}

} // namespace

