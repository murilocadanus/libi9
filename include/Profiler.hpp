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

#ifndef PROFILER_HPP
#define PROFILER_HPP

#if defined(I9_ENABLE_PROFILER)
#include "Defines.h"

#include <map>
#include <stack>

namespace Sascar {

#define I9_FUNCTION_PROFILER					ProfileContext _ctx_func(__PRETTY_FUNCTION__ ); //__FUNCTION__); // Check: MSVC and Xcode
#define I9_BEGIN_REGION_PROFILER(name, str)	ProfileContext _c##name(str, Profiler::regionProfilerInstance);
#define I9_END_REGION_PROFILER(name)			_c##name.Terminate();
#define ProfilerReportPrint						Profiler::funcProfilerInstance->Dump(); Profiler::regionProfilerInstance->Dump();
#define ProfilerTerminate						do { \
													delete Profiler::funcProfilerInstance; \
													Profiler::funcProfilerInstance = nullptr; \
													delete Profiler::regionProfilerInstance; \
													Profiler::regionProfilerInstance = nullptr; \
												} \
												while (0);

class ProfileContext;

/// Profile Entry Data
struct ProfilerEntry
{
	f32 time;
	f32 maxtime;
	u32 calls;
	f32 stack[256];
	u32 pos;

	ProfilerEntry()
		: time(0)
		, maxtime(0)
		, calls(0)
		, stack()
		, pos(0)
	{}
};

typedef std::map<const char *, ProfilerEntry *> FuncTimeMap;
typedef std::pair<const char *, ProfilerEntry *> FuncTimePair;
typedef FuncTimeMap::iterator FuncTimeMapIt;
typedef std::stack<ProfileContext *> ContextStack;

/// Profiler
class Profiler
{
	public:
		Profiler(const char *name);
		~Profiler();

		void AddSlice(const char *func, f32 time);
		void AddTotal(const char *func, f32 time);
		void Dump();
		void Reset();

		static Profiler *funcProfilerInstance;
		static Profiler *regionProfilerInstance;

	private:
		const char *pName;
		FuncTimeMap mapSubjectSlice;
		FuncTimeMap mapSubjectTotal;
};

/// Profiler Context
class ProfileContext
{
	public:
		ProfileContext(const char *f, Profiler *prof = Profiler::funcProfilerInstance);
		~ProfileContext();

		void Terminate();
		void StopPrevious();
		void RestorePrevious();
		void StopAndCommit();
		void StartOrContinue();
		void Push();
		void Pop();

		static ContextStack stack;

	private:
		const char *func;
		Milliseconds beg;
		Milliseconds begTotal;
		bool bTerminated;

		Profiler *pProf;
};

} // namespace

#else

#define I9_FUNCTION_PROFILER
#define I9_BEGIN_REGION_PROFILER(name, str)
#define I9_END_REGION_PROFILER(name)
#define ProfilerReportPrint
#define ProfilerTerminate

#endif // I9_ENABLE_PROFILER

#endif //PROFILER_HPP
