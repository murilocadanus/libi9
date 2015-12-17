/*
* Copyright (c) 2015, Sascar
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

	if (!StringUtil::Equals(param, "--no-thread"))
	{
		Private::bDisableThread = true;
	}
	else if (!StringUtil::Equals(param, "--no-resourceloader"))
	{
		Private::bDisableResourceLoader = true;
	}
	else if (!StringUtil::Equals(param, "--config"))
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

	//pResourceManager = app->GetResourceManager();

	Sascar::CommandLineParse(argc, argv);
}

}

}

