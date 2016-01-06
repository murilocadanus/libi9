#include "Defines.hpp"
#include "util/Log.hpp"
#include "ResourceManager.hpp"
#include "System.hpp"
#include "Memory.hpp"

#define TAG		"[ResourceManager] "

#if defined(SEED_LOG_RESOURCEMANAGER)
	#define LOG		Log
#else
	#define LOG		_hid_rmlog
	void _hid_rmlog(const char *pMessage, ...);
	void _hid_rmlog(const char *pMessage, ...)
	{
		UNUSED(pMessage);
	}
#endif

namespace Sascar {

LoaderMap ResourceManager::mapLoaders;

ResourceManager::ResourceManager(const String &name)
	: sName(name)
	, mapResources()
{
}

ResourceManager::~ResourceManager()
{
	if (mapResources.size())
	{
		Log(TAG "WARNING: Some resources still allocated in '%s'.", sName.c_str());
		this->Print();
	}

	this->Reset();
}

void ResourceManager::Reset()
{
	for (auto each: mapResources)
	{
		LOG(TAG "Deallocating %s.", each.first.c_str());
		sdDelete(each.second);
	}

	ResourceMap().swap(mapResources);
}

IResource *ResourceManager::Get(const String &filename, TypeId resourceType)
{
	IResource *res = nullptr;

	if (mapResources.find(filename) == mapResources.end())
	{
		Log(TAG "Resource %s not found in '%s'.", filename.c_str(), sName.c_str());
		LoaderMapIterator it = mapLoaders.find(resourceType);
		if (it == mapLoaders.end())
		{
			Log(TAG "Resource loader for %s not found.", filename.c_str());
			return nullptr;
		}

		res = ((*it).second)(filename, this);

		if (res)
		{
			this->Add(filename, res);
		}
		else
		{
			Log(TAG "WARNING: Resource file '%s' not found - couldn't load.", filename.c_str());
		}
	}
	else
	{
		res = mapResources[filename];
	}

	if (res)
		res->IncrementReference();

	return res;
}

void ResourceManager::GarbageCollect()
{
#if defined(DEBUG)
	Milliseconds tbegin = pTimer->GetMilliseconds();
	Milliseconds tend = 0;
#endif // DEBUG

	u32 amount = 0;
	ResourceMapIterator it = mapResources.begin();
	while (it != mapResources.end())
	{
		IResource *res = (*it).second;
		u32 r = res->GetReferenceCount();
		LOG(TAG "> %s -> %d", res->GetFilename().c_str(), r);
		if (!r)
		{
			amount++;
			mapResources.erase(it++);
			sdDelete(res);
		}
		else
		{
			++it;
		}
	}

#if defined(DEBUG)
	tend = pTimer->GetMilliseconds();
	LOG(TAG "Garbage collection done in %d milliseconds, cleared %d objects.",  (u32)(tend - tbegin), amount);
	LOG(TAG "Resources inside '%s': ", sName.c_str());
	this->Print();
#endif // DEBUG
}

void ResourceManager::Unload(TypeId resourceType)
{
	for (auto each: mapResources)
	{
		IResource *res = each.second;

		if (res->GetTypeId() == resourceType)
		{
			Log(TAG "Unloading %s %s.", res->GetTypeName(), each.first.c_str());
			res->Unload();
		}
	}
}

void ResourceManager::Reload(TypeId resourceType)
{
	for (auto each: mapResources)
	{
		IResource *res = each.second;
		if (res->GetTypeId() == resourceType)
		{
			Log(TAG "Reloading %s %s.", res->GetTypeName(), each.first.c_str());
			res->Load(res->sFilename, res->pRes);
		}
	}
}

void ResourceManager::Register(TypeId resourceType, pResourceLoaderFunc pfunc)
{
	if (mapLoaders.find(resourceType) != mapLoaders.end())
	{
		LOG(TAG "This resource loader is already registered.");
		return;
	}

	mapLoaders[resourceType] = pfunc;
}

void ResourceManager::Unregister(TypeId resourceType)
{
	LoaderMapIterator it = mapLoaders.find(resourceType);

	if (it == mapLoaders.end())
	{
		LOG(TAG "Resource loader not found.");
		return;
	}

	mapLoaders.erase(it);
}

void ResourceManager::Add(const String &filename, IResource *res)
{
	if (mapResources.find(filename) != mapResources.end())
	{
		LOG(TAG "The resource %s already is allocated in '%s'.", filename.c_str(), sName.c_str());
		return;
	}

	mapResources[filename] = res;
}

void ResourceManager::Remove(const String &filename)
{
	ResourceMapIterator it = mapResources.find(filename);

	if (it == mapResources.end())
	{
		LOG(TAG "Resource %s not found in '%s'.", filename.c_str(), sName.c_str());
		return;
	}

	mapResources.erase(it);
}

void ResourceManager::PrintUsedMemoryByResource()
{
	u32 total = 0;

	for (auto each: mapResources)
	{
		IResource *res = each.second;
		Dbg(TAG "Resource: %s Memory: %d References: %d Type: %s", res->sFilename.c_str(), res->GetUsedMemory(), res->GetReferenceCount(), res->GetTypeName());
		total += res->GetUsedMemory();
	}

	Dbg(TAG "Total: %d", total);
}

u32 ResourceManager::GetTotalUsedMemory()
{
	u32 total = 0;

	for (auto each: mapResources)
	{
		IResource *res = each.second;
		total += res->GetUsedMemory();
	}

	return total;
}

void ResourceManager::Print()
{
#if defined(DEBUG) && defined(SEED_LOG_RESOURCEMANAGER)
	u32 cnt = 0;
	Log(TAG "Listing %d loaded resources in '%s':", mapResources.size(), sName.c_str());

	for (auto each: mapResources)
	{
		IResource *res = each.second;
		const String name = each.first;

		Log(TAG "\t%s [%s] [%d]", name.c_str(), res->GetTypeName(), res->GetReferenceCount());
		cnt++;
	}

	Log(TAG "%s Total: %d resources.", sName.c_str(), cnt);
#endif // DEBUG
}

} // namespace
