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

#ifndef CONSOLE_SYSTEM_HPP
#define CONSOLE_SYSTEM_HPP

#if defined(BUILD_CONSOLE)

#include "interface/ISystem.hpp"
#include "Singleton.hpp"

#define SYSTEM_RETRACE_HISTORY_MAX	64

namespace Sascar { namespace Console {

/// SDL System Module
class System : public ISystem
{
	I9_DECLARE_SINGLETON(System)
	I9_DECLARE_MANAGER(System)

	public:
		// ISystem
		virtual void GoToMenu() override;
		virtual void Sleep() override;
		virtual void OnHomeCalled();
		virtual void WaitForRetrace() override;
		virtual void HangUp() override;
		virtual void GoToDataManager() override;

		virtual bool IsShuttingDown() const override;
		virtual bool IsResetting() const override;
		virtual bool IsSleeping() const override;

		virtual void DisableHome() override;
		virtual void EnableHome() override;
		virtual bool IsHomeEnabled() const override;
		virtual bool IsHomeRunning() const override;
		virtual bool InitializeHome() override;

		virtual const char *GetUsername() const override;
		virtual const char *GetHomeFolder() const override;
		virtual const char *GetApplicationDataFolder() const override;

		// IModule
		virtual bool Initialize() override;
		virtual bool Shutdown() override;
		virtual bool Reset() override;

		// IUpdatable
		virtual bool Update(f32 dt) override;

	private:
		u64		iLastFrameTime;
		u64		iFpsTime;
		f32		fElapsedTime;
		u32		iRetraceCount;
		u32		iFrameRate;
		u32		iRetraceIndex;
		u32		arRetraceCount[SYSTEM_RETRACE_HISTORY_MAX];
		bool	bShutdown;
		bool	bSleeping;
};

#define pSystem Sascar::Console::System::GetInstance()

}} // namespace

#else // BUILD_CONSOLE
	#error "Include 'System.h' instead 'platform/console/ConsoleSystem.h' directly."
#endif // BUILD_CONSOLE
#endif // CONSOLE_SYSTEM_HPP
