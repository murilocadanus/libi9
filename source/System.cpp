#include "System.hpp"

#define TAG "[System] "

namespace Sascar {

System System::instance;

System::System()
{
}

System::~System()
{
}

bool System::Initialize()
{
	return true;
}

bool System::Shutdown()
{
	return true;
}

}

