#include "interface/IEventMessageQueue.hpp"
#include "interface/IEventMessageQueueListener.hpp"

namespace Sascar {

IEventMessageQueue::IEventMessageQueue()
	: vQueueListeners()
{
}

IEventMessageQueue::~IEventMessageQueue()
{
	IEventMessageQueueListenerVector().swap(vQueueListeners);
}

void IEventMessageQueue::AddQueueListener(IEventMessageQueueListener *listener)
{
	vQueueListeners += listener;
}

void IEventMessageQueue::RemoveQueueListener(IEventMessageQueueListener *listener)
{
	vQueueListeners -= listener;
}

void IEventMessageQueue::SendEventQueueNotifyChange(EventMessageQueue *ev)
{
	IEventMessageQueueListenerVector listeners = vQueueListeners;
	for (IEventMessageQueueListener *each: listeners)
	{
		each->OnMessageQueueNotifyChange(ev);
	}
}

}
