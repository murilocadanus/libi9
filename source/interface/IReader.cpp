#include "interface/IReader.hpp"
#include "util/Log.hpp"

namespace Sascar {

IReader::IReader()
{
}

IReader::~IReader()
{
}

IReader::IReader(const File &file)
{
	UNUSED(file)
}

IReader::IReader(const IReader &other)
{
	UNUSED(other)
}

IReader &IReader::operator=(const IReader &other)
{
	UNUSED(other)
	return *this;
}

bool IReader::Load(const void *data)
{
	UNUSED(data)
	return false;
}

bool IReader::Load(IReader &reader)
{
	UNUSED(reader)
	return false;
}

const char *IReader::ReadString(const char *key, const char *value) const
{
	UNUSED(key)
	return value;
}

u32 IReader::ReadU32(const char *key, u32 value) const
{
	UNUSED(key)
	return value;
}

u32 IReader::GetU32(u32 value) const
{
	return value;
}

const char *IReader::GetKey(u32 atPos) const
{
	UNUSED(atPos)
	return nullptr;
}

s32 IReader::ReadS32(const char *key, s32 value) const
{
	UNUSED(key)
	return value;
}

f32 IReader::ReadF32(const char *key, f32 value) const
{
	UNUSED(key)
	return value;
}

bool IReader::ReadBool(const char *key, bool value) const
{
	UNUSED(key)
	return value;
}

u32 IReader::SelectArray(const char *key)
{
	UNUSED(key)
	return 0;
}

void IReader::SelectNext()
{
}

void IReader::UnselectArray()
{
}

bool IReader::IsNode(const char *key) const
{
	UNUSED(key)
	return false;
}

bool IReader::SelectNode(const char *key)
{
	UNUSED(key);
	return false;
}

void IReader::UnselectNode()
{
}

} // namespace
