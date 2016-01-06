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

#ifndef THREAD_HPP
#define THREAD_HPP

#include "Defines.hpp"
#include <thread>
#include <mutex>

typedef std::mutex Mutex;
typedef std::lock_guard<Mutex> ScopedMutexLock;
typedef std::unique_lock<Mutex> UniqueMutexLock;

namespace Sascar {

class Thread
{
	public:
		Thread();
		virtual ~Thread();

		virtual void Create();
		virtual void Destroy();

		virtual bool Run() = 0;

		bool IsRunning() const
		{
			return bRunning;
		}

	private:
		std::thread cThread;
		bool bRunning : 1;
};

} // namespace

#endif // THREAD_HPP
