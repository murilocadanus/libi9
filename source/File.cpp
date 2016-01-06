
#include "Defines.hpp"
#include "File.hpp"
#include "FileSystem.hpp"
#include "util/Log.hpp"
#include "Enum.hpp"
#include "Memory.hpp"

#define TAG		"[File] "

namespace Sascar {

File::File()
	: IObject()
	, pHandle(nullptr)
	, pData(nullptr)
	, sFilename()
	, iSize(0)
{
}

File::File(const String &filename)
	: IObject()
	, pHandle(nullptr)
	, pData(nullptr)
	, sFilename(filename)
	, iSize(0)
{
	this->Load(filename);
}

File::~File()
{
	this->Close();
}

bool File::Load(const String &filename)
{
	this->Close();
	sFilename = filename;
	return this->Open();
}

bool  File::Unload()
{
	this->Close();
	return true;
}

bool File::Open()
{
	bool ret = true;
	SEED_ASSERT_MSG(sFilename.length(), "Error: No filename was given to open file!");
	pHandle = PHYSFS_openRead(sFilename.c_str());
	if (!pHandle)
	{
		Log(TAG "Error: file: %s - %s", sFilename.c_str(), PHYSFS_getLastError());
		//SEED_ASSERT_MSG(false, "Aborted, file not found.");
		return false;
	}
	else
		iSize = static_cast<u32>(PHYSFS_fileLength(pHandle));

	return ret;
}

void File::Close()
{
	sdFree(pData);
	if (pHandle)
		PHYSFS_close(pHandle);
	iSize = 0;
	sFilename = "";
}

bool File::Check() const
{
	bool ret = true;
	if (!pHandle)
	{
		Log(TAG "Error: Invalid handle, open the file before call this function");
		ret = false;
	}

	return ret;
}

u8 *File::GetData() const
{
	WARNING(FIXME - mutex lock guard here)
	if (pData)
		return pData;

	if (this->Check())
	{
		pData = (u8 *)sdAlloc(iSize + 1);
		pData[iSize] = 0;
		if (PHYSFS_read(pHandle, pData, iSize, 1) != -1)
			return pData;
	}

	return nullptr;
}

u32 File::GetSize() const
{
	return iSize;
}

const String &File::GetName() const
{
	return sFilename;
}


FileLoader::FileLoader(const String &filename, JobCallback fun)
	: Job(fun)
	, sFilename(filename)
	, pFile(nullptr)
{
}

FileLoader::~FileLoader()
{
	sdDelete(pFile);
}

bool FileLoader::Run()
{
	Log("[Job:FileLoader] Load: %s", sFilename.c_str());

	cMutex.lock();
	bool run = (nState == eJobState::Running);
	cMutex.unlock();

	if (run)
	{
		pFile = sdNew(File(sFilename));
		pFile->GetData();
		Log("[Job:FileLoader] Loaded: %s (%d bytes)", sFilename.c_str(), pFile->GetSize());

		cMutex.lock();
		nState = eJobState::Completed;
		cMutex.unlock();

		Log("[Job:FileLoader] Completed: %s", sFilename.c_str());
	}

	return false;
}

} // namespace
