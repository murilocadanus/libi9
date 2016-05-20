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
	return true;
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

bool FileSystem::SaveFile(std::string pathClient, std::string pathPlate, std::string pathFile, const uint8_t *bufferFile, uint32_t sizeBufferFile)
{
	if(this->pDirPath == NULL) throw PathNotDefinedException();

	bool written = false;
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
			written = true;
			//this->SendEventFileSystemNotifyChange(&ev);
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

		written = this->SaveFile(pathClient, pathPlate, pathFile, bufferFile, sizeBufferFile);
	}

	return written;
}

bool FileSystem::Shutdown()
{
	Info(TAG "Shutdown");
	return true;
}

}
