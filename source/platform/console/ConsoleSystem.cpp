#if defined(BUILD_CONSOLE)

#include "Defines.hpp"
#include "System.hpp"
#include "util/Log.hpp"
#include "Timer.hpp"
#include "EventSystem.hpp"
#include "Configuration.hpp"
#include <physfs.h>
#include "platform/console/Platform.hpp"

#define TAG "[System] "

#define MAX_FRAMESKIP_THRESHOLD 10

namespace Sascar { namespace Console {

I9_SINGLETON_DEFINE(System)

System::System()
	: iLastFrameTime(0)
	, iFpsTime(0)
	, fElapsedTime(0.0f)
	, iRetraceCount(0)
	, iFrameRate(0)
	, iRetraceIndex(0)
	, arRetraceCount()
	, bShutdown(false)
	, bSleeping(false)
{
}

System::~System()
{
}

bool System::Reset()
{
	return true;
}

bool System::Initialize()
{
	Log(TAG "Initializing...");
	print_system_info();

	Log(TAG "Initialization completed.");

	return true;
}

bool System::Shutdown()
{
	this->bShutdown = true;
	Log(TAG "Terminating...");

	return true;
}

bool System::Update(f32 dt)
{
	UNUSED(dt);

#if !defined(EMSCRIPTEN)
	//u8 state = SDL_GetAppState();
	//if ((state & SDL_APPACTIVE) != SDL_APPACTIVE || (state & SDL_APPINPUTFOCUS) != SDL_APPINPUTFOCUS)
	//{
	//	if (!this->bSleeping)
	//	{
	//		this->bSleeping = true;

	//		EventSystem ev;
	//		this->SendEventSleep(&ev);
	//	}
	//}
	//else
	//{
		if (this->bSleeping)
		{
			this->bSleeping = false;

			EventSystem ev;
			this->SendEventSleep(&ev);
		}
	//}
#endif
	this->WaitForRetrace();
	return true;
}

void System::Sleep()
{
	Log(TAG "WARNING: Platform doesnt support sleep mode.");
}

bool System::IsSleeping() const
{
	return this->bSleeping;
}

bool System::IsShuttingDown() const
{
	return this->bShutdown;
}

bool System::IsResetting() const
{
	return false;
}

void System::WaitForRetrace()
{
	++iRetraceCount;

	if (!iLastFrameTime)
		iLastFrameTime = pTimer->GetMilliseconds();

	f32 frameMaxTime			= 1000.0f / iFrameRate;

	do
	{
		//hold fps
		u64 time		= pTimer->GetMilliseconds();
		u64 frameTime	= time - iLastFrameTime;
		iFpsTime		+= frameTime;
		fElapsedTime	+= (f32)frameTime;
		iLastFrameTime	= time;
	} while (fElapsedTime < frameMaxTime);

	fElapsedTime -= frameMaxTime;

	//Raptor: test fix for when WM_PAINT stops comming for a long time due to the
	//user moving the window, for instance. Tries to avoid the retrace trying to
	//catch up with the lost frame time
	if ((fElapsedTime / frameMaxTime) > MAX_FRAMESKIP_THRESHOLD)
		fElapsedTime = 0;

	if (iFpsTime > 1000)
	{
		Dbg("FPS: %d", iRetraceCount);

		arRetraceCount[iRetraceIndex++] = iRetraceCount;
		if (iRetraceIndex >= SYSTEM_RETRACE_HISTORY_MAX)
			iRetraceIndex = 0;

		iFpsTime -= 1000;
		iRetraceCount = 0;
	}
}

const char *System::GetUsername() const
{
	return get_user_name();
}

const char *System::GetHomeFolder() const
{
	return PHYSFS_getUserDir();
}

const char *System::GetApplicationDataFolder() const
{
	return PHYSFS_getBaseDir();
}

void System::GoToMenu()
{
}

void System::OnHomeCalled()
{
}

void System::GoToDataManager()
{
}

void System::HangUp()
{
}

bool System::IsHomeEnabled() const
{
	return false;
}

bool System::IsHomeRunning() const
{
	return false;
}

bool System::InitializeHome()
{
	return true;
}

void System::EnableHome()
{
}

void System::DisableHome()
{
}

}} // namespace

#endif // BUILD_SDL2
