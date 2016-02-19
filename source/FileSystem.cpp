#include "FileSystem.hpp"
#include "util/Log.hpp"
#include <sys/inotify.h>
#include <dirent.h>
#include <unistd.h>

#define TAG "[FileSystem] "

namespace Sascar {

FileSystem FileSystem::instance;

FileSystem::FileSystem()
	: sPath("")
{

}

FileSystem::~FileSystem()
{

}

bool FileSystem::Initialize()
{
	Log(TAG "Initialize");

	if(!sPath.empty())
	{
		// Set to start listening only 1 directory
		eWatchType = WatchType::LOCAL_PATH;

		// Start the notify listener
		iNotifier = inotify_init();

		// Add path to notify listener
		AddPath(sPath);

		return true;
	}
	else
		return false;
}

bool FileSystem::Update(float dt)
{
	char *readPtr;
	char buffer[EVENT_BUFFER_LENGTH];
	struct inotify_event *event;

	// Watch path
	WatchPath(sPath);

	// Read from notifier
	long inputLen = read(iNotifier, buffer, EVENT_BUFFER_LENGTH);

	if(inputLen <= 0)
	{
		Error(TAG "Can't read from notifier listener");
		exit(EXIT_FAILURE);
	}

	readPtr = buffer;
	while(readPtr < buffer + inputLen)
	{
		event = (struct inotify_event *) readPtr;
		if(event->name[0] != '.' && event->len > 0)
		{
			if( (event->mask & IN_CREATE) && (event->mask & IN_ISDIR))
			{
				// Watch new folder to process
				Log(TAG "Created folder %s%s", mWatchingPaths[event->wd].c_str(), event->name);
			}
			else if ((event->mask & IN_CLOSE_WRITE) && !(event->mask & IN_ISDIR))
			{
				Log(TAG "Created file %s%s", mWatchingPaths[event->wd].c_str(), event->name);
			}
		}

		readPtr += sizeof (struct inotify_event) +event->len;
	}

	return true;
}

void FileSystem::AddPath(const std::string &path)
{
	int watchFd = inotify_add_watch(iNotifier, path.c_str(), IN_CLOSE | IN_CREATE);

	if (watchFd < 0)
	{
		Log(TAG "It was not possible to watch path: %s", path.c_str());
		exit(EXIT_FAILURE);
	}
	else
	{
		Log(TAG "Watching path: %s", path.c_str());
		mWatchingPaths[watchFd] = path;
	}
}

void FileSystem::WatchPath(const std::string &path)
{
	struct dirent *dir;
	DIR *openedDir = opendir(path.c_str());
	std::string folder;

	if(openedDir)
	{
		if((dir = readdir(openedDir)) != NULL)
		{
			// Ignore hidden files
			if(dir->d_name[0] != '.')
			{
				if(dir->d_type == DT_REG)
				{
					/*EventFileSystem ev;
					ev.SetDirName(path);
					ev.SetEventType(DT_REG);

					Info(TAG "Processing directory listening");
					this->SendEventFileSystemNotifyChange(&ev);*/
				}
				else if(dir->d_type == DT_DIR && this->eWatchType == WatchType::RECURSIVE_PATH)
				{
					folder = path;
					folder += dir->d_name;
					folder += "/";

					// Add folder path to watch
					AddPath(folder);

					// Recursively watch
					WatchPath(folder);
				}
			}
		}
		closedir(openedDir);
	}
}

bool FileSystem::Shutdown()
{
	Log(TAG "Shutdown");
	return true;
}

}
