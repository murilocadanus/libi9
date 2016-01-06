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

#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <string>
#include <chrono>
#include <stdarg.h>
#include <stdint.h>
#include "Config.hpp"
#include "util/Log.hpp"
#include "util/String.hpp"

// Types
typedef unsigned long long int 	u64;
typedef unsigned int 			u32;
typedef unsigned short int 		u16;
typedef unsigned char 			u8;
typedef signed long long int	s64;
typedef signed int 				s32;
typedef signed short int 		s16;
typedef signed char 			s8;
typedef float 					f32;

#define HALT					do { exit(-1); } while (1);
#define UNUSED(var)				(void)var;

template <typename T, size_t N>
constexpr size_t countof(T(&)[N])
{
	return N;
}

// Debugging
#if defined(DEBUG)
	#if defined(__GNUC__)
		#define __FUNC__					__PRETTY_FUNCTION__
	#else
		#define __FUNC__					__FUNCSIG__
	#endif

	#define SEED_ASSERT(x)					if (!(x)) { Err("%s:%d: " #x, __FILE__, __LINE__); HALT}
	#define SEED_ASSERT_MSG(x, msg)			if (!(x)) { Err("%s:%d: (" #x "): " #msg, __FILE__, __LINE__); HALT}
	#define SEED_ASSERT_FMT(x, msg, ...)	if (!(x)) { Err("%s:%d: (" #x "): " #msg, __FILE__, __LINE__, __VA_ARGS__); HALT}
	#define SEED_WARNING(x, msg, ...)		if (x)    { Wrn("%s:%d: WARNING: (" #x "): " #msg, __FILE__, __LINE__, __VA_ARGS__); }
	#define SEED_CHECK_RETURN(x, ret, msg, ...)	if (!(x)) { Err("%s:%d: ERROR: (" #x "): " #msg, __FILE__, __LINE__); return ret; }
	#define SEED_ABSTRACT_METHOD			Dbg(I9_TAG "WARNING: Calling an 'abstract' method: [%s] (%s:%d).", __FUNC__, __FILE__, __LINE__);
	#define SEED_DEPRECATED_METHOD			Dbg(I9_TAG "WARNING: Calling a deprected method, please fix it: [%s] (%s:%d)", __FUNC__, __FILE__, __LINE__);
#else
	#define SEED_CHECK_RETURN(x, ret, msg, ...)	if (!(x)) { Err("ERROR: " #msg); return ret; }

	#define SEED_ABSTRACT_METHOD
	#define SEED_DEPRECATED_METHOD

	#if defined(__GNUC__)
		#define SEED_ASSERT(...)
		#define SEED_ASSERT_MSG(...)
		#define SEED_ASSERT_FMT(...)
		#define SEED_WARNING(...)
	#else
		#define SEED_ASSERT
		#define SEED_ASSERT_MSG
		#define SEED_ASSERT_FMT
		#define SEED_WARNING
	#endif // __GNUC__

#endif // DEBUG

#define SEED_ASSERT(x)					if (!(x)) { Err("%s:%d: " #x, __FILE__, __LINE__); HALT}

#define WARNING(desc)	//Wrn("WARNING: " __FILE__ "(" SEED_STRINGIZE(__LINE__) "): " SEED_STRINGIZE(desc));

#define SEED_COMPILE_TIME_ASSERT(name, x)	typedef int __seed_compile_assert_ ## name[(x) * 2 - 1]

SEED_COMPILE_TIME_ASSERT(u8,  sizeof(u8) == 1);
SEED_COMPILE_TIME_ASSERT(s8,  sizeof(s8) == 1);
SEED_COMPILE_TIME_ASSERT(u16, sizeof(u16) == 2);
SEED_COMPILE_TIME_ASSERT(s16, sizeof(s16) == 2);
SEED_COMPILE_TIME_ASSERT(u32, sizeof(u32) == 4);
SEED_COMPILE_TIME_ASSERT(s32, sizeof(s32) == 4);
SEED_COMPILE_TIME_ASSERT(u64, sizeof(u64) == 8);
SEED_COMPILE_TIME_ASSERT(s64, sizeof(s64) == 8);

typedef enum { SEED_ENUM_ASSERT_VALUE } SEED_ENUM_ASSERT;
SEED_COMPILE_TIME_ASSERT(enum, sizeof(SEED_ENUM_ASSERT) == sizeof(u32));

namespace Sascar {
	typedef std::chrono::high_resolution_clock Clock;
	typedef long long Milliseconds; // we use the raw numbers directly internally, no conversions needed.
	typedef float Seconds; // same here
	typedef std::chrono::duration<Milliseconds, std::milli> Duration;
	typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;
}

#define LEAF(x)

#endif // DEFINES_HPP
