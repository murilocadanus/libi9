#include "Defines.hpp"
#include "File.hpp"
#include "util/Log.hpp"
#include "Enum.hpp"

#define TAG		"[File] "

namespace Sascar {

File::File()
	: pHandle(nullptr)
	, pData(nullptr)
	, sFilename()
	, iSize(0)
{
}

File::File(const String &filename)
	: pHandle(nullptr)
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
	I9_ASSERT_MSG(sFilename.length(), "Error: No filename was given to open file!");
	pHandle = fopen(sFilename.c_str(), "r");
	if (!pHandle)
	{
		Log(TAG "Error: file: %s", sFilename.c_str());
		//I9_ASSERT_MSG(false, "Aborted, file not found.");
		return false;
	}
	else
		iSize = static_cast<u32>(PHYSFS_fileLength(pHandle));

	return ret;
}

void File::Close()
{
	if (pData)
		free(pData);
	pData = nullptr;

	if (pHandle)
		fclose(pHandle);
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
	//WARNING(FIXME - mutex lock guard here)
	if (pData)
		return pData;

	if (this->Check())
	{
		pData = (u8 *)malloc(iSize + 1);
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

} // namespace
