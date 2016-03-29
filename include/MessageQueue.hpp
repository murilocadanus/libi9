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

#ifndef MESSAGEQUEUE
#define MESSAGEQUEUE

#include "interface/IManager.hpp"
#include "interface/IUpdatable.hpp"
#include "interface/IEventMessageQueue.hpp"
#include <cms/Connection.h>

namespace Sascar {

using namespace cms;

class MessageQueue : public IManager, public IUpdatable, public IEventMessageQueue
{
		I9_DECLARE_MANAGER(Queue)

		public:
			MessageQueue();
			virtual ~MessageQueue();

			static MessageQueue instance;

			static inline MessageQueue *GetInstance()
			{
				return &MessageQueue::instance;
			}

			static inline void DestroyInstance(){}

			// IManager
			virtual bool Initialize() override;
			virtual bool Shutdown() override;

			// IUpdatable
			virtual bool Update(float dt) override;

			void SetName(const std::string &name) { sName = name; }
			inline const std::string &GetName() { return sName; }

		private:
			Connection *pConn;
			Session *pSession;
			Destination *pDestination;
			MessageConsumer *pConsumer;
			std::string sName;
};

#define pMessageQueue MessageQueue::GetInstance()

} // namespace

#endif // QUEUE
