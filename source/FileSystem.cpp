
#include "FileSystem.hpp"
#include "util/Log.hpp"
#include "File.hpp"
#include "I9Init.hpp"
#include "Configuration.hpp"
#include <physfs.h>

#define FS_CHECK(x)	{ if (!x) { const char *_err = PHYSFS_getLastError(); UNUSED(_err); Log(TAG "Error: %s", _err); }}

#define TAG	"[FileSystem] "

namespace Sascar {

I9_SINGLETON_DEFINE(FileSystem)

FileSystem::FileSystem()
{
}

FileSystem::~FileSystem()
{
	this->Shutdown();
}

bool FileSystem::Initialize()
{
	Info(TAG "Executable: %s", Sascar::Private::pcArgv[0]);
	FS_CHECK(PHYSFS_init(Sascar::Private::pcArgv[0]));
	FS_CHECK(PHYSFS_setSaneConfig(".", "", "zip", false, false));
	FS_CHECK(PHYSFS_addToSearchPath(pConfiguration->GetWorkingDirectory().c_str(), 0));
	Info(TAG "Using working directory as: %s", PHYSFS_getBaseDir());
	return true;
}

void FileSystem::Prepare() const
{
	FS_CHECK(PHYSFS_setSaneConfig(Sascar::pConfiguration->GetPublisherName().c_str(), Sascar::pConfiguration->GetApplicationTitle().c_str(), "zip", false, false));
}

bool FileSystem::Shutdown()
{
	if (bInitialized)
		FS_CHECK(PHYSFS_deinit());

	return true;
}

const char *FileSystem::GetWorkDirectory() const
{
	return PHYSFS_getBaseDir();
}

const char *FileSystem::GetWriteableDirectory() const
{
	return PHYSFS_getWriteDir();
}

bool FileSystem::IsRequired() const
{
	return true;
}

} // namespace
