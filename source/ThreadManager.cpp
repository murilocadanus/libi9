
#if (SEED_USE_THREAD == 0)

#include "ThreadManager.hpp"
#include "Defines.hpp"
#include "util/Log.hpp"
#include "Enum.hpp"
#include "Thread.hpp"

#define TAG		"[ThreadManager] "

namespace Sascar {

SEED_SINGLETON_DEFINE(ThreadManager)

ThreadManager::ThreadManager()
	: vThread()
	, bEnabled(true)
{
}

ThreadManager::~ThreadManager()
{
	this->Reset();
}

bool ThreadManager::Initialize()
{
	return IManager::Initialize();
}

bool ThreadManager::Reset()
{
	ThreadVector().swap(vThread);
	return true;
}

bool ThreadManager::Shutdown()
{
	this->Reset();
	return IManager::Shutdown();
}

bool ThreadManager::Update(Seconds dt)
{
	UNUSED(dt)
	if (bEnabled)
	{
		ThreadVector completed;

		for (auto each: vThread)
		{
			if (!each->Run())
				completed += each;
		}

		for (auto each: completed)
			vThread -= each;
	}

	return true;
}

void ThreadManager::Add(Thread *obj)
{
	vThread += obj;
}

void ThreadManager::Remove(Thread *obj)
{
	vThread -= obj;
}

void ThreadManager::Disable()
{
	bEnabled = false;
}

void ThreadManager::Enable()
{
	bEnabled = true;
}

} // namespace

#endif // SEED_USE_THREAD
