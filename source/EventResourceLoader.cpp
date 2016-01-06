#include "EventResourceLoader.hpp"

namespace Sascar {

EventResourceLoader::EventResourceLoader()
	: IEvent()
	, pGroup(nullptr)
{
}

EventResourceLoader::~EventResourceLoader()
{
}

void EventResourceLoader::SetGroup(ResourceGroup *group)
{
	pGroup = group;
}

ResourceGroup *EventResourceLoader::GetGroup() const
{
	return pGroup;
}

} // namespace
