#include "Memory.hpp"

#if defined(DEBUG)

void *operator new(std::size_t size, eAllocationTag tag, const char *stmt, const char *func, const char *file, int line)
{
	return Sascar::Allocator::Alloc(size, tag, stmt, func, file, line);
}

void *operator new(std::size_t size) I9_THROW
{
	return Sascar::Allocator::Alloc(size, eAllocationTag::DoNotTrack);
}

void operator delete(void *p) I9_NOEXCEPT
{
	Sascar::Allocator::Free(p);
}

void operator delete(void *p, eAllocationTag, const char *, const char *, const char *, int)
{
	Sascar::Allocator::Free(p);
}

void *operator new[](std::size_t size, eAllocationTag tag, const char *stmt, const char *func, const char *file, int line)
{
	return Sascar::Allocator::Alloc(size, tag, stmt, func, file, line);
}

void *operator new[](std::size_t size) I9_THROW
{
	return Sascar::Allocator::Alloc(size, eAllocationTag::DoNotTrack);
}

void operator delete[](void *p) I9_NOEXCEPT
{
	Sascar::Allocator::Free(p);
}

void operator delete[](void *p, eAllocationTag, const char *, const char *, const char *, int)
{
	Sascar::Allocator::Free(p);
}

#endif
