#include "interface/ISystem.hpp"

namespace Sascar {

ISystem::ISystem()
	: mTimer()
	, pStrAppName(nullptr)
	, pStrAppDescription(nullptr)
{
}

ISystem::~ISystem()
{
}

}
