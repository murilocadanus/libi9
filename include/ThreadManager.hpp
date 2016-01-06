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

#ifndef THREADMANAGER_HPP
#define THREADMANAGER_HPP

#if (I9_USE_THREAD == 0)

#include "interface/IManager.hpp"
#include "interface/IUpdatable.hpp"
#include "Singleton.hpp"
#include "Container.hpp"

namespace Sascar {

class Thread;

/// Thread Manager is used when no threads are enabled to run threads in serial
class ThreadManager : public IManager, public IUpdatable
{
	I9_DECLARE_SINGLETON(ThreadManager)
	I9_DECLARE_MANAGER(ThreadManager)
	I9_DECLARE_CONTAINER(Vector, Thread)

	public:
		void Add(Thread *thread);
		void Remove(Thread *thread);

		// IManager
		virtual bool Initialize() override;
		virtual bool Reset() override;
		virtual bool Shutdown() override;

		virtual void Disable() override;
		virtual void Enable() override;

		// IUpdatable
		virtual bool Update(Seconds dt) override;

	private:
		ThreadVector vThread;
		bool bEnabled : 1;
};

#define pThreadManager ThreadManager::GetInstance()

} // namespace

#endif // I9_USE_THREAD

#endif // THREADMANAGER_HPP
