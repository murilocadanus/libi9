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


#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "Defines.hpp"
#include "Container.hpp"

namespace Sascar {

class IManager;

/// Module Manager
class Manager
{
	I9_DECLARE_CONTAINER(Vector, IManager)

	public:
		Manager();
		virtual ~Manager();

		static Manager instance;

		static inline Manager *GetInstance()
		{
			return &Manager::instance;
		}

		static inline void DestroyInstance(){}

		bool Add(IManager *obj);
		bool Remove(IManager *obj);

		void Disable(const char *managerName);
		void Enable(const char *managerName);
		bool IsEnabled(const char *managerName);

		bool Initialize();
		bool Reset();
		bool Shutdown();

		void Print();

	private:
		IManagerVector vManager;
};

#define pManager Manager::GetInstance()

} // namespace

#endif // MANAGER_HPP

