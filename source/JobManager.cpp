#include "JobManager.hpp"
#include "Defines.hpp"
#include "util/Log.hpp"
#include "Enum.hpp"
#include "Job.hpp"
#include "Memory.hpp"

#define TAG		"[JobManager] "

namespace Sascar {

I9_SINGLETON_DEFINE(JobManager)

JobManager::JobManager()
{
}

JobManager::~JobManager()
{
}

bool JobManager::Reset()
{
	while (vQueue.size())
	{
		auto job = vQueue.front();
		vQueue.pop();

		job->Abort();
		sdDelete(job);
	}

	for (auto job: vRunning)
	{
		job->Abort();
		sdDelete(job);
	}

	JobVector().swap(vRunning);

	return true;
}

bool JobManager::Shutdown()
{
	while (vQueue.size())
	{
		auto job = vQueue.front();
		vQueue.pop();

		job->Abort();
	}

	for (auto job: vRunning)
		job->Destroy();

	JobVector().swap(vRunning);

	return IManager::Shutdown();
}

void JobManager::StartThreads()
{
	if (vQueue.empty())
		return;

	ScopedMutexLock lock(cMutex);
	while (vRunning.Size() < iMaxThreads && !vQueue.empty())
	{
		auto job = vQueue.front();
		vQueue.pop();

		vRunning += job;
		job->Create();
	}
}

bool JobManager::Update(Seconds dt)
{
	UNUSED(dt)
	if (bEnabled)
	{
		this->StartThreads();
		auto list = vRunning;

		for (auto job: list)
		{
			switch (job->GetState())
			{
				case eJobState::Completed:
				case eJobState::Aborted:
				{
					vRunning -= job;
					job->OnFinished();
				}
				break;

				default:
				break;
			}
		}

		this->StartThreads();
	}

	return true;
}

Job *JobManager::Add(Job *job)
{
	ScopedMutexLock lock(cMutex);
	vQueue.push(job);
	return job;
}

void JobManager::Disable()
{
	bEnabled = false;
}

void JobManager::Enable()
{
	bEnabled = true;
}

} // namespace
