#include "ResourceGroup.hpp"
#include "interface/IResource.hpp"
#include "ResourceManager.hpp"
#include "System.hpp"
#include "Memory.hpp"

namespace Sascar {

ResourceGroup::ResourceGroup()
	: queue()
	, bLoaded(false)
{
}

ResourceGroup::~ResourceGroup()
{
	Vector<QueueItem *>().swap(queue);
}

void ResourceGroup::Add(const String &filename, TypeId resourceType, ResourceManager *res)
{
	auto newItem			= sdNew(QueueItem());
	newItem->filename 		= filename;
	newItem->resource 		= nullptr;
	newItem->resourceType 	= resourceType;
	newItem->resManager		= res;
	newItem->startTime		= pTimer->GetMilliseconds();
	newItem->erased			= false;

	queue += newItem;
}

bool ResourceGroup::Load()
{
	for (auto each: queue)
	{
		if (each->resource)
			continue;

		IResource *res = each->resManager->Get(each->filename, each->resourceType);
		each->resource = res;
	}

	return true;
}

bool ResourceGroup::Unload()
{
	for (auto each: queue)
	{
		sdRelease(each->resource);
		sdDelete(each);
	}

	queue.clear();
	QueueVector().swap(queue);

	return true;
}

void ResourceGroup::SetLoaded()
{
	bLoaded = true;
}

bool ResourceGroup::IsLoaded() const
{
	return bLoaded;
}

} // namespace

