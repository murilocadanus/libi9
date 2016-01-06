#include "interface/IResource.hpp"

namespace Sascar {

IResource::IResource()
	: pRes(nullptr)
	, sFilename()
	, iRefCount(0)
	, bLoaded(false)
{
}

IResource::~IResource()
{
}

void IResource::Release()
{
	this->DecrementReference();
}

void IResource::Acquire()
{
	this->IncrementReference();
}

u32 IResource::GetUsedMemory() const
{
	return sizeof(this);
}

void IResource::IncrementReference()
{
	iRefCount++;
}

void IResource::DecrementReference()
{
	iRefCount--;
}

u32 IResource::GetReferenceCount() const
{
	return iRefCount;
}

const String &IResource::GetFilename() const
{
	return sFilename;
}

} // namespace

