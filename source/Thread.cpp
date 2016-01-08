
#include "Thread.hpp"
#include "ThreadManager.hpp"

#define TAG 	"[Thread] "

namespace Sascar {

Thread::Thread()
	: cThread()
	, bRunning(false)
{
}

Thread::~Thread()
{
	this->Destroy();
}

void Thread::Create()
{
	I9_ASSERT_MSG(bRunning != true, TAG "Already created.");

#if (I9_USE_THREAD == 1)
	cThread = std::thread([&](){
		while (this->Run()) {};
	});

	std::thread::id defaultId;
	UNUSED(defaultId)
	I9_ASSERT_MSG(defaultId != cThread.get_id(), TAG "Failed to create thread.");
#else
	pThreadManager->Add(this);
#endif

	bRunning = true;
}

void Thread::Destroy()
{
	if (!bRunning)
		return;

	bRunning = false;
#if (I9_USE_THREAD == 1)
	cThread.join();
#else
	pThreadManager->Remove(this);
#endif
}

} // namespace

