#include "Reader.hpp"
#include "Configuration.hpp"
#include "api/yajl/JsonReader.hpp"
#include "util/Log.hpp"
#include "Memory.hpp"

#define TAG "[Reader] "

namespace Sascar {

IReader cNullReader;

Reader::Reader()
	: IReader()
	, pOpaque(&cNullReader)
{
	this->Init();
}

Reader::Reader(File *file)
	: IReader()
	, pOpaque(&cNullReader)
{
	this->Init();
	pOpaque->Load(file->GetData());
}

Reader::Reader(Reader &reader)
	: IReader()
	, pOpaque(&cNullReader)
{
	this->Init();

	IReader *r = reader.pOpaque;
	pOpaque->Load(*r);
}

Reader::~Reader()
{
	if (pOpaque != &cNullReader)
		sdDelete(pOpaque);

	pOpaque = nullptr;
}

void Reader::Init()
{
	if (pOpaque == &cNullReader || pOpaque == nullptr)
	{
		switch (pConfiguration->GetReaderType())
		{
#if defined(SEED_USE_JSON)
			case eReaderType::Json:
			{
				Info(TAG "Creating reader json");
				pOpaque = sdNew(JsonReader());
			}
			break;
#endif

			default:
			{
#if defined(SEED_USE_JSON)
				Info(TAG "Creating reader json");
				pOpaque = sdNew(JsonReader());
#else
				Info(TAG "Failed creating reader, using null");
#endif
			}
			break;
		}
	}
}

const char *Reader::ReadString(const char *key, const char *value) const
{
	return pOpaque->ReadString(key, value);
}

s32 Reader::ReadS32(const char *key, s32 value) const
{
	return pOpaque->ReadS32(key, value);
}

u32 Reader::ReadU32(const char *key, u32 value) const
{
	return pOpaque->ReadU32(key, value);
}

u32 Reader::GetU32(u32 value) const
{
	return pOpaque->GetU32(value);
}

const char *Reader::GetKey(u32 atPos) const
{
	return pOpaque->GetKey(atPos);
}

f32 Reader::ReadF32(const char *key, f32 value) const
{
	return pOpaque->ReadF32(key, value);
}

bool Reader::ReadBool(const char *key, bool value) const
{
	return pOpaque->ReadBool(key, value);
}

u32 Reader::SelectArray(const char *key)
{
	return pOpaque->SelectArray(key);
}

void Reader::SelectNext()
{
	pOpaque->SelectNext();
}

void Reader::UnselectArray()
{
	pOpaque->UnselectArray();
}

bool Reader::IsNode(const char *key) const
{
	return pOpaque->IsNode(key);
}

bool Reader::SelectNode(const char *key)
{
	return pOpaque->SelectNode(key);
}

void Reader::UnselectNode()
{
	pOpaque->UnselectNode();
}

} // namespace

