/*
* Copyright (c) 2016, Sascar
* All rights reserved.
*
* THIS SOFTWARE IS PROVIDED BY SASCAR ''AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL SASCAR BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <new>
#include <string.h>

#if !defined(__FUNC__)
	#if defined(__GNUC__)
		#define __FUNC__	__PRETTY_FUNCTION__
	#else
		#define __FUNC__	__FUNCSIG__
	#endif
#endif

enum class eAllocationTag
{
	DoNotTrack,
	Unknown, // C static initializers, STL operators, others.
	User = 1000,

};

#if defined(DEBUG)

#if !defined(_MSC_VER)
#define I9_THROW
#define I9_NOEXCEPT	noexcept(true)
#elif __LINUX__
#define I9_THROW		_GLIBCXX_THROW (std::bad_alloc)
#define I9_NOEXCEPT	_GLIBCXX_NOEXCEPT
#else
#define I9_THROW
#define I9_NOEXCEPT
#endif

void *operator new(std::size_t size, eAllocationTag tag, const char *stmt, const char *func, const char *file = __FILE__, int line = __LINE__);
void *operator new(std::size_t size) I9_THROW;
void operator delete(void *p) I9_NOEXCEPT;
void operator delete(void *p, eAllocationTag, const char *, const char *, const char *, int);
void *operator new[](std::size_t size, eAllocationTag tag, const char *stmt, const char *func, const char *file = __FILE__, int line = __LINE__);
void *operator new[](std::size_t size) I9_THROW;
void operator delete[](void *p) I9_NOEXCEPT;
void operator delete[](void *p, eAllocationTag, const char *, const char *, const char *, int);

#include "Defines.hpp"
#include "System.hpp"

#define sdNew(T)				new (eAllocationTag::User, #T, __FUNC__, __FILE__, __LINE__) T
#define sdDelete(ptr)			{ if (ptr) delete ptr; ptr = nullptr; }
#define sdNewArray(T, L)		new (eAllocationTag::User, #T "[" #L "]", __FUNC__, __FILE__, __LINE__) T[(L)]
#define sdDeleteArray(ptr)		{ if (ptr) delete[] ptr; ptr = nullptr; }
#define sdAlloc(S)				Allocator::Alloc(S, eAllocationTag::User, #S, __FUNC__, __FILE__, __LINE__)
#define sdFree(ptr)				{ if (ptr) free(ptr); ptr = nullptr; }

namespace Sascar {

I9_COMPILE_TIME_ASSERT(Milliseconds, sizeof(Milliseconds) == 8);

struct AllocationInfo
{
	u64           iAddr;
	u64           iSize;
	Milliseconds  iTime;
	Milliseconds  iLifetime;
	u32           iLine;
	u32           iFrame;
	char          strCall[256];
	char          strFile[256];
	char          strFunc[256];
	bool          bFreed;
};

struct FreeInfo
{
	intptr_t      iAddr;
	u32           iFrame;
	Milliseconds  iTime;
};

class Allocator
{
	public:
		static void *Alloc(size_t size, eAllocationTag tag = eAllocationTag::Unknown, const char *stmt = "", const char *func = "", const char *file = __FILE__, int line = __LINE__)
		{
			UNUSED(tag)
			UNUSED(stmt)
			UNUSED(file)
			UNUSED(line)
			UNUSED(func)
			I9_ASSERT_FMT(size, "allocing 0 bytes at %s:%d: %s.", file, line, func);

			auto addr = malloc(size);

			if (tag != eAllocationTag::DoNotTrack)
			{
				AllocationInfo info;
				info.iAddr = (intptr_t)addr;
				info.iLine = line;
				info.iFrame = 0;
				info.bFreed = false;
				info.iLifetime = 0;
				info.iTime = pTimer->GetMilliseconds();
				info.iSize = size;
				strcpy(info.strCall, stmt);
				strcpy(info.strFile, file);
				strcpy(info.strFunc, func);
				UNUSED(info);
				LEAF(Alloc(&info, sizeof(AllocationInfo)));
			}

			return addr;
		}

		static void Free(void *p, bool track = true)
		{
			I9_ASSERT_MSG(p, "freeing null pointer.");

			if (track)
			{
				FreeInfo info;
				info.iAddr = (intptr_t)p;
				info.iFrame = 0;
				info.iTime = pTimer->GetMilliseconds();
				UNUSED(info);
				LEAF(Free(&info, sizeof(FreeInfo)));
			}
			free(p);
		}
};

}

#else // DEBUG

#include <stdlib.h>

#define sdNew(T)				new T
#define sdDelete(ptr)			{ if (ptr) delete ptr; ptr = nullptr; }
#define sdNewArray(T, L)		new T[L]
#define sdDeleteArray(ptr)		{ if (ptr) delete []ptr; ptr = nullptr; }
#define sdAlloc(S)				malloc(S)
#define sdFree(ptr)				{ free(ptr); ptr = nullptr;}

class Allocator
{
	public:
		static void *Alloc(std::size_t size, eAllocationTag, const char *, const char *, const char *, int)
		{
			return malloc(size);
		}

		static void Free(void *p, bool)
		{
			free(p);
		}
};

#endif // DEBUG

#define I9_DECLARE_NEW_AND_DELETE_OPERATORS													\
		inline void *operator new(size_t size, eAllocationTag tag, const char *stmt, const char *func, const char *file = __FILE__, int line = __LINE__) \
		{																						\
			return Allocator::Alloc(size, tag, stmt, func, file, line);							\
		}																						\
																								\
		inline void operator delete(void *p) 													\
		{																						\
			Allocator::Free(p);																	\
		}																						\
																								\
		inline void *operator new[](std::size_t size, eAllocationTag tag, const char *stmt, const char *func, const char *file = __FILE__, int line = __LINE__) \
		{																						\
			return Allocator::Alloc(size, tag, stmt, func, file, line);							\
		}																						\
																								\
		inline void operator delete[](void* p)													\
		{																						\
			Allocator::Free(p);																	\
		}																						\
																								\
		inline void *operator new(std::size_t, void *place, eAllocationTag tag, const char *stmt, const char *func, const char *file = __FILE__, int line = __LINE__) \
		{																						\
			return place;																		\
		}																						\
																								\
		inline void operator delete(void *, void *)												\
		{																						\
																								\
		}																						\
																								\
		inline void* operator new[](std::size_t, void *place, eAllocationTag tag, const char *stmt, const char *func, const char *file = __FILE__, int line = __LINE__) \
		{																						\
			return place;																		\
		}																						\
																								\
		inline void operator delete[](void *, void *)											\
		{																						\
																								\
		}

#endif // MEMORY_HPP
