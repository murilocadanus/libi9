#ifndef IEVENTFILESYSTEM
#define IEVENTFILESYSTEM

#include "interface/IEvent.hpp"
#include "EventFileSystem.hpp"
#include "Container.hpp"

namespace Sascar {

class IEventFileSystemListener;

class IEventFileSystem
{
	I9_DECLARE_CONTAINER(Vector, IEventFileSystemListener)

	public:
		IEventFileSystem();
		virtual ~IEventFileSystem();

		virtual void AddFileSystemListener(IEventFileSystemListener *listener);
		virtual void RemoveFileSystemListener(IEventFileSystemListener *listener);

	protected:
		void SendEventFileSystemNotifyChange(EventFileSystem *ev);

	protected:
		IEventFileSystemListenerVector vFileSystemListeners;
};

} // namespace

#endif // IEVENTFILESYSTEM

