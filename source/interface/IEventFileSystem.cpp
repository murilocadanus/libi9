#include "interface/IEventFileSystem.hpp"
#include "interface/IEventFileSystemListener.hpp"

namespace Sascar {

IEventFileSystem::IEventFileSystem()
	: vFileSystemListeners()
{
}

IEventFileSystem::~IEventFileSystem()
{
	IEventFileSystemListenerVector().swap(vFileSystemListeners);
}

void IEventFileSystem::AddFileSystemListener(IEventFileSystemListener *listener)
{
	vFileSystemListeners += listener;
}

void IEventFileSystem::RemoveFileSystemListener(IEventFileSystemListener *listener)
{
	vFileSystemListeners -= listener;
}

void IEventFileSystem::SendEventFileSystemNotifyChange(EventFileSystem *ev)
{
	IEventFileSystemListenerVector listeners = vFileSystemListeners;
	for (IEventFileSystemListener *each: listeners)
	{
		each->OnFileSystemNotifyChange(ev);
	}
}

}
