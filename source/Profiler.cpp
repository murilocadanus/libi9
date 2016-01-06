#if defined(I9_ENABLE_PROFILER)

#include "System.hpp"
#include "Profiler.hpp"
#include "util/Log.hpp"

namespace Sascar {

#define TAG "[Profiler] "
#define STORE_VALUE(v) { p->stack[p->pos++] = v; if (p->pos > 256) p->pos = 0; }

Profiler *Profiler::funcProfilerInstance = new Profiler("Function");
Profiler *Profiler::regionProfilerInstance = new Profiler("Region");

ContextStack ProfileContext::stack;

Profiler::Profiler(const char *name)
	: pName(name)
	, mapSubjectSlice()
	, mapSubjectTotal()
{
}

Profiler::~Profiler()
{
	this->Reset();
}

void Profiler::AddSlice(const char *func, f32 time)
{
	FuncTimeMapIt it = mapSubjectSlice.find(func);
	if (it != mapSubjectSlice.end())
	{
		ProfilerEntry *p = (*it).second;
		p->calls++;
		p->time += time;
		STORE_VALUE(time);

		if (time > p->maxtime)
			p->maxtime = time;
	}
	else
	{
		ProfilerEntry *p = new ProfilerEntry();
		p->calls = 0;
		p->time = time;
		p->maxtime = time;
		STORE_VALUE(time);

		mapSubjectSlice.insert(FuncTimePair(func, p));
	}
}

void Profiler::AddTotal(const char *func, f32 time)
{
	FuncTimeMapIt it = mapSubjectTotal.find(func);
	if (it != mapSubjectTotal.end())
	{
		ProfilerEntry *p = (*it).second;
		p->calls++;
		p->time += time;
		STORE_VALUE(time);

		if (time > p->maxtime)
			p->maxtime = time;
	}
	else
	{
		ProfilerEntry *p = new ProfilerEntry();
		p->calls = 1;
		p->time = time;
		p->maxtime = time;
		STORE_VALUE(time);

		mapSubjectTotal.insert(FuncTimePair(func, p));
	}
}

void Profiler::Dump()
{
#ifdef DEBUG
	Log(TAG "Dumping %s Totals: %d", pName, (int)mapSubjectTotal.size());

	for (auto each: mapSubjectTotal)
	{
		ProfilerEntry *entry = each.second;
		int calls = entry->calls;
		float average = static_cast<float>((float)entry->time / (float)calls);
		Log(TAG "%s: %s [average time %fms, called %d times]", pName, each.first, average, calls);
	}

	Log(TAG "Dumping %s Slices: %d", pName, (int)mapSubjectSlice.size());

	for (auto each: mapSubjectSlice)
	{
		ProfilerEntry *entry = each.second;
		int calls = entry->calls;
		float average = static_cast<float>((float)entry->time / (float)calls);
		Log(TAG "%s: %s [average time %fms, interrupted %d times]", pName, each.first, average, calls);
	}
#endif
}

void Profiler::Reset()
{
	for (auto each: mapSubjectTotal)
		delete each.second;
	mapSubjectTotal.clear();

	for (auto each: mapSubjectSlice)
		delete each.second;
	mapSubjectSlice.clear();
}

ProfileContext::ProfileContext(const char *f, Profiler *prof)
	: func(f)
	, beg(0)
	, begTotal(0)
	, bTerminated(false)
	, pProf(prof)
{
	begTotal = pTimer->GetMilliseconds();
	this->Push();
	this->StartOrContinue();
}

ProfileContext::~ProfileContext()
{
	this->Terminate();
}

void ProfileContext::Terminate()
{
	if (bTerminated)
		return;

	u64 end = pTimer->GetMilliseconds(); //clock();

	f32 diff = 0;
	diff = static_cast<f32>(end - begTotal);// / CLOCKS_PER_SEC;

	pProf->AddTotal(func, diff);

	this->StopAndCommit();
	this->Pop();
	bTerminated = true;
}

void ProfileContext::StopPrevious()
{
	if (!stack.empty())
	{
		ProfileContext *parent = stack.top();
		parent->StopAndCommit();
	}
}

void ProfileContext::RestorePrevious()
{
	if (!stack.empty())
	{
		ProfileContext *parent = stack.top();
		parent->StartOrContinue();
	}
}

void ProfileContext::StopAndCommit()
{
	u64 end = pTimer->GetMilliseconds();

	f32 diff = 0;
	diff = static_cast<f32>(end - beg);// / CLOCKS_PER_SEC;

	pProf->AddSlice(func, diff);
	beg = 0;
}

void ProfileContext::StartOrContinue()
{
	beg = pTimer->GetMilliseconds();
}

void ProfileContext::Push()
{
	this->StopPrevious();
	stack.push(this);
}

void ProfileContext::Pop()
{
	if (!stack.empty())
		stack.pop();
	this->RestorePrevious();
}

} // namespace

#endif // I9_ENABLE_PROFILER
