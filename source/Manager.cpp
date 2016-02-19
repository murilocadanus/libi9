#include "Manager.hpp"
#include "interface/IManager.hpp"
#include "util/Log.hpp"

#define TAG "[Manager] "

namespace Sascar {

Manager Manager::instance;

Manager::Manager()
	: vManager()
{
}

Manager::~Manager()
{
	IManagerVector().swap(vManager);
}

bool Manager::Add(IManager *obj)
{
	vManager += obj;
	bool ret = obj->Initialize();

	if (!ret)
	{
		if (obj->IsRequired())
		{
			Info(TAG "CRITICAL: Manager '%s' failed to initialize.", obj->GetName().c_str());
		}
		else
		{
			Info(TAG "WARNING: Manager '%s' failed to initialize.", obj->GetName().c_str());
			ret = true; // we can continue as this manager isn't critical.
		}
	}

	return ret;
}

bool Manager::Remove(IManager *obj)
{
	vManager -= obj;
	return obj->Shutdown();
}

void Manager::Disable(const char *managerName)
{
	UNUSED(managerName);
}

void Manager::Enable(const char *managerName)
{
	UNUSED(managerName);
}

bool Manager::IsEnabled(const char *managerName)
{
	UNUSED(managerName);
	return true;
}

bool Manager::Initialize()
{
	bool ret = true;

	for (auto each: vManager)
		ret = ret && (each->Initialize() || !each->IsRequired());

	return ret;
}

bool Manager::Reset()
{
	bool ret = true;

	for (auto each: vManager)
		ret = ret && (each->Reset() || !each->IsRequired());

	return ret;
}

bool Manager::Shutdown()
{
	bool ret = true;

	u32 len = (u32)vManager.Size() - 1;
	for (s32 i = len; i >= 0; i--)
	{
		IManager *each = vManager[i];
		Info(TAG "Terminating manager %s.", each->GetName().c_str());
		ret = ret && (each->Shutdown() || !each->IsRequired());
	}

	return ret;
}

void Manager::Print()
{
	Info(TAG "Listing current managers:");

	for (auto each: vManager)
	{
		Info(TAG "\tManager: %s.", each->GetName().c_str());
	}
}

}

