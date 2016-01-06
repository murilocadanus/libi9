#include "util/Log.hpp"
#include "ResourceLoader.hpp"
#include "ResourceGroup.hpp"
#include "EventResourceLoader.hpp"
#include "interface/IEventResourceLoaderListener.hpp"
#include "System.hpp"
#include "Memory.hpp"

#define TAG		"[ResourceLoader] "

namespace Sascar {

I9_SINGLETON_DEFINE(ResourceLoader)

ResourceLoader::ResourceLoader()
	: vListeners()
	, vGroups()
{
}

ResourceLoader::~ResourceLoader()
{
}

bool ResourceLoader::Reset()
{
	IManager::Reset();
	return true;
}

bool ResourceLoader::Initialize()
{
	Log(TAG "Initializing...");
	IManager::Initialize();
	this->Create();
	Log(TAG "Initialization completed.");

	return true;
}

bool ResourceLoader::Shutdown()
{
	this->Destroy();
	IManager::Shutdown();
	Log(TAG "Terminated.");

	return true;
}

bool ResourceLoader::Update(Seconds dt)
{
	UNUSED(dt);

	if (!this->IsRunning())
		return false;

	ResourceGroup *group = nullptr;

	ScopedMutexLock lock(cMutex);
	if (vGroups.size() > 0)
	{
		group = (*vGroups.begin());
	}

	if (!group)
		return true;

	if (group->IsLoaded())
	{
		EventResourceLoader ev;
		ev.SetGroup(group);
		SendEventGroupLoaded(&ev);

		group->Unload();

		GroupIterator p = std::find(vGroups.begin(), vGroups.end(), group);
		if (p != vGroups.end())
			vGroups.erase(p);

		if (vGroups.size() == 0)
		{
			vGroups.clear();
			Vector<ResourceGroup *>().swap(vGroups);
		}

		//glResourceManager.Print();
	}

	return true;
}

bool ResourceLoader::Run()
{
	if (this->IsRunning())
	{
		ResourceGroup *group = nullptr;

		ScopedMutexLock lock(cMutex);
		if (vGroups.size() > 0)
		{
			group = (*vGroups.begin());
		}

		if (!group)
			return true;

		if (group->IsLoaded())
			return true;

		if (group->Load())
			group->SetLoaded();
	}

	pTimer->Sleep(Milliseconds(10));
	return this->IsRunning();
}

void ResourceLoader::Add(ResourceGroup *group)
{
	if (this->IsRunning())
	{
		ScopedMutexLock lock(cMutex);
		vGroups.push_back(group);
	}
}

void ResourceLoader::AddListener(IEventResourceLoaderListener *listener)
{
	vListeners += listener;
}

void ResourceLoader::RemoveListener(IEventResourceLoaderListener *listener)
{
	I9_ASSERT(listener);
	ListenerIterator p = std::find(vListeners.begin(), vListeners.end(), listener);

	if (p != vListeners.end())
		vListeners.erase(p);

	if (!vListeners.size())
	{
		vListeners.clear();
		ListenerVector().swap(vListeners);
	}
}

void ResourceLoader::SendEventGroupLoaded(const EventResourceLoader *ev)
{
	for (auto target: vListeners)
		target->OnGroupLoaded(ev);
}

void ResourceLoader::SendEventQueueEmpty(const EventResourceLoader *ev)
{
	for (auto target: vListeners)
		target->OnQueueEmpty(ev);
}

} // namespace
