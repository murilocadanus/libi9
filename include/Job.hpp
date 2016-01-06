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

#ifndef JOB_HPP
#define JOB_HPP

#include "Defines.hpp"
#include "Thread.hpp"
#include "Enum.hpp"

#include <functional>
#include <mutex>

namespace Sascar {

class Job : public Thread
{
	friend class JobManager;

	public:
		typedef std::function<void(Job *)> JobCallback;

		Job(JobCallback fun);
		virtual ~Job();

		void Abort();
		eJobState GetState() const;

	protected:
		virtual void OnFinished();

		// Thread
		virtual bool Run() override;
		virtual void Create() override;

	protected:
		JobCallback fnCallback;
		Mutex cMutex;
		eJobState nState = eJobState::Stopped;
};

} // namespace

#endif // JOB_HPP
