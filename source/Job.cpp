
#include "Job.hpp"

namespace Sascar {

Job::Job(JobCallback fun)
	: fnCallback(fun)
{
}

Job::~Job()
{
}

void Job::Create()
{
	ScopedMutexLock lock(cMutex);
	nState = eJobState::Running;
	Thread::Create();
}

void Job::Abort()
{
	ScopedMutexLock lock(cMutex);
	nState = eJobState::Aborted;
	Thread::Destroy();
}

eJobState Job::GetState() const
{
	return nState;
}

bool Job::Run()
{
	return true;
}

void Job::OnFinished()
{
	if (fnCallback)
		fnCallback(this);
}

} // namespace
