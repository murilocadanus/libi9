#include "FileSystem.hpp"
#include "util/Log.hpp"
#include <sys/inotify.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sstream>
#include <iomanip>
#include <fcntl.h>
#include <errno.h>

#define TAG "[FileSystem] "

namespace Sascar {

FileSystem FileSystem::instance;

FileSystem::FileSystem()
	: sPath("")
	, pDirPath(NULL)
	, iDirFd(0)
{

}

FileSystem::~FileSystem()
{

}

bool FileSystem::Initialize()
{
	Info(TAG "Initialize");

	if(!sPath.empty())
	{
		// Set to start listening only 1 directory
		eWatchType = WatchType::RECURSIVE_PATH;

		// Start the notify listener
		iNotifier = inotify_init();

		// Add path to notify listener
		AddPath(sPath);

		// Watch path
		WatchPath(sPath);

		return true;
	}
	else
		return false;
}

void FileSystem::SetPath(std::string path)
{
	this->sPath = path;

	if(this->iDirFd)
	{
		close(this->iDirFd);
		this->iDirFd = 0;
	}

	if(this->pDirPath)
	{
		closedir(this->pDirPath);
		this->pDirPath = NULL;
	}

	if(access(this->sPath.c_str(), R_OK | W_OK) != 0)
	{
		std::cout << strerror( errno ) << " - " << this->sPath << std::endl;
		abort();
	}

	this->pDirPath = opendir(this->sPath.c_str());

	if(!this->pDirPath)
	{
		throw PathNotFoundException();
	}

	this->iDirFd = dirfd(this->pDirPath);

	if(!this->iDirFd)
	{
		throw PathNotFoundException();
	}
}

void FileSystem::SaveFile(std::string pathClient, std::string pathPlate, std::string pathFile, const uint8_t *bufferFile, uint32_t sizeBufferFile)
{
	if(this->pDirPath == NULL) throw PathNotDefinedException();
	std::string pathClientPlateFile = pathClient + "/" + pathPlate + "/" + pathFile;

	int fd = openat(this->iDirFd, pathClientPlateFile.c_str(), O_CREAT | O_RDWR | O_TRUNC, 0666);
	Dbg(TAG "Status of open file: %s, openat handler: %d", strerror(errno), fd);

	if(fd != -1)
	{
		Info(TAG "Writing: %s", pathClientPlateFile.c_str());

		int escrito = write(fd, bufferFile, sizeBufferFile);
		Dbg(TAG "Status of write file: %s, size buffer file to write: %d, wrote size buffer: %d", strerror(errno), bufferFile, escrito);

		close(fd);

		if(escrito < sizeBufferFile)
		{
			Error(TAG "Can't write file.");
			throw FileWriteException();
		}
		else
		{
			EventFileSystem ev;
			ev.SetDirName(pathClientPlateFile);
			ev.SetEventType(DT_REG);

			Dbg(TAG "Processing file %s", ev.GetDirName().c_str());
			this->SendEventFileSystemNotifyChange(&ev);
		}
	}
	else
	{
		Info(TAG "File do not exist: %s", pathFile.c_str());

		if( errno == ENOSPC)
		{
			throw NotSpaceAvaiableException();
		}

		std::string pathClientPlate = pathClient + "/" + pathPlate;
		mkdirat(this->iDirFd, pathClient.c_str(),  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		mkdirat(this->iDirFd, pathClientPlate.c_str(),  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

		this->SaveFile(pathClient, pathPlate, pathFile, bufferFile, sizeBufferFile);

		throw PathNotDefinedException();
	}
}

void FileSystem::AddPath(const std::string &path)
{
	int watchFd = inotify_add_watch(iNotifier, path.c_str(), IN_CLOSE | IN_CREATE);

	if (watchFd < 0)
	{
		Error(TAG "It was not possible to watch path: %s", path.c_str());
		exit(EXIT_FAILURE);
	}
	else
	{
		Dbg(TAG "Watching path: %s", path.c_str());
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
		while((dir = readdir(openedDir)) != NULL)
		{
			// Ignore hidden files
			if(dir->d_name[0] != '.')
			{
				if(dir->d_type == DT_REG)
				{
					EventFileSystem ev;
					ev.SetDirName(path);
					ev.SetFileName(dir->d_name);
					ev.SetEventType(DT_REG);

					Dbg(TAG "Processing file %s%s", path.c_str(), dir->d_name);
					this->SendEventFileSystemNotifyChange(&ev);
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
	Info(TAG "Shutdown");
	return true;
}

}
