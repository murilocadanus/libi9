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

#include "I9Init.hpp"
#include "Defines.hpp"
#include "Configuration.hpp"
#include "FileSystem.hpp"
#include "Updater.hpp"
#include "Manager.hpp"

extern "C" {

namespace Sascar {

namespace Private
{
	IApp	*pApplication;
	bool	bInitialized;
	int		iArgc;
	char	**pcArgv;
	bool	bDisableThread;
	bool	bDisableResourceLoader;
	String	sConfigFile;
}

//ResourceManager *pResourceManager = nullptr;

int CommandLineParameter(char **argv, int pos)
{
	const char *param = argv[pos];
	int consume = 1;

	if (StringUtil::Equals(param, "--no-thread"))
	{
		Private::bDisableThread = true;
	}
	else if (StringUtil::Equals(param, "--no-resourceloader"))
	{
		Private::bDisableResourceLoader = true;
	}
	else if (StringUtil::Equals(param, "--config"))
	{
		Private::sConfigFile = argv[pos + 1];
		consume++;
	}

	return consume;
}

void CommandLineParse(int argc, char **argv)
{
	int i = 0;
	while (i < argc)
	{
		i += Sascar::CommandLineParameter(argv, i);
	}
}

void SetApp(IApp *app, int argc, char **argv, const char *config)
{
	Private::iArgc = argc;
	Private::pcArgv = argv;
	Private::pApplication = app;
	Private::sConfigFile = config;

	Private::bDisableThread = false;
	Private::bDisableResourceLoader = false;

	Sascar::CommandLineParse(argc, argv);
}

void WriteOut(const char *msg)
{
	if (Private::pApplication)
		Private::pApplication->WriteOut(msg);
}

void WriteErr(const char *msg)
{
	if (Private::pApplication)
		Private::pApplication->WriteErr(msg);
}

void GetVersion(u32 *major, u32 *middle, u32 *minor)
{
	if (major)
		*major = I9_VERSION_MAJOR;

	if (middle)
		*middle = I9_VERSION_MAJOR;

	if (minor)
		*minor = I9_VERSION_MAJOR;
}

bool Initialize()
{
	if (!Private::pApplication)
	{
		fprintf(stderr, "ERROR: You should set a App by calling SetApp(IApp *app, int argc, char **argv)!\n");
		HALT;
	}

	Info(I9_BANNER, I9_VERSION_MAJOR, I9_VERSION_MIDDLE, I9_VERSION_MINOR);

	Info("");
	Info(I9_TAG "Build Configuration:");

	Info(I9_TAG "\tThreading: %s", I9_USE_THREAD ? "Yes" : "No");
	Info(I9_TAG "\tSingleton: %s", I9_SINGLETON_HEAP ? "Heap" : "Stack");
	Info(I9_TAG "\tReader: %s", I9_USE_JSON ? "JSON" : "Binary");
	Info(I9_TAG "Initializing...");

	bool ret = true;

	pConfiguration->Load(Private::sConfigFile);
	pFileSystem->SetPath(pConfiguration->GetAppListeningPath());

	ret = ret && pManager->Add(pFileSystem);
	ret = ret && pManager->Add(Private::pApplication);

	pUpdater->Add(pFileSystem);
	pUpdater->Add(Private::pApplication);

	Private::bInitialized = true;

	return ret;
}

void Update()
{
	if (!Private::bInitialized)
		return;

	Seconds dt				= 1;//Private::fCurrentTime;

	pUpdater->Run(dt);
}

void Shutdown()
{
	if (!Private::bInitialized)
		return;

	Info(I9_TAG "Shutting down subsystems...");

	pManager->Shutdown();
	pFileSystem->DestroyInstance();

	Private::bInitialized = false;
	Private::pApplication = nullptr;
}

} // namespace

} // extern C

