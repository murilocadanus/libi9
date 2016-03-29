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

#ifndef IEVENTMESSAGEQUEUE
#define IEVENTMESSAGEQUEUE

#include "interface/IEvent.hpp"
#include "EventQueue.hpp"
#include "Container.hpp"

namespace Sascar {

class IEventMessageQueueListener;

class IEventMessageQueue
{
	I9_DECLARE_CONTAINER(Vector, IEventMessageQueueListener)

	public:
		IEventMessageQueue();
		virtual ~IEventMessageQueue();

		virtual void AddQueueListener(IEventMessageQueueListener *listener);
		virtual void RemoveQueueListener(IEventMessageQueueListener *listener);

	protected:
		void SendEventQueueNotifyChange(EventMessageQueue *ev);

	protected:
		IEventMessageQueueListenerVector vQueueListeners;
};

} // namespace

#endif // IEVENTMESSAGEQUEUE

