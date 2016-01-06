/*
* Copyright (c) 2016, Sascar
* All rights reserved.
*
* THIS SOFTWARE IS PROVIDED BY SASCAR ''AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL SASCAR BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef JOBMANAGER_HPP
#define JOBMANAGER_HPP

#include "interface/IManager.hpp"
#include "interface/IUpdatable.hpp"
#include "Singleton.hpp"
#include "Container.hpp"
#include "Thread.hpp"

#include <queue>

namespace Sascar {

class Job;

/// Job Manager
class JobManager : public IManager, public IUpdatable
{
	I9_DECLARE_SINGLETON(JobManager)
	I9_DECLARE_MANAGER(JobManager)
	I9_DECLARE_CONTAINER(Vector, Job)

	public:
		Job *Add(Job *job);

		// IManager
		virtual bool Reset() override;
		virtual bool Shutdown() override;

		virtual void Disable() override;
		virtual void Enable() override;

		// IUpdatable
		virtual bool Update(Seconds dt) override;

	protected:
		void StartThreads();

	private:
		Mutex cMutex;

		std::queue<Job *> vQueue;
		JobVector vRunning;

		u32 iMaxThreads = 8;
		bool bEnabled = true;
};

#define pJobManager JobManager::GetInstance()

} // namespace

#endif // JOBMANAGER_HPP
