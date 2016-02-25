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

#include "interface/IApp.hpp"

#define TAG "[App] "

#define ANSI_COLOR_RED		"\x1b[31m"
#define ANSI_COLOR_GREEN	"\x1b[32m"
#define ANSI_COLOR_YELLOW	"\x1b[33m"
#define ANSI_COLOR_BLUE		"\x1b[34m"
#define ANSI_COLOR_MAGENTA	"\x1b[35m"
#define ANSI_COLOR_CYAN		"\x1b[36m"
#define ANSI_COLOR_RESET	"\x1b[0m"

namespace Sascar {

IApp::IApp()
	: bIsFinished(false)
{
}

IApp::~IApp()
{
}

bool IApp::Shutdown()
{
	Log(TAG "Shutting down...");

	return true;
}

void IApp::WriteOut(const char *msg)
{
	fprintf(stdout, "[" ANSI_COLOR_CYAN "LOG" ANSI_COLOR_RESET "]\t%s\n", msg);
}

void IApp::WriteInfo(const char *msg)
{
	fprintf(stdout, "[" ANSI_COLOR_GREEN "INFO" ANSI_COLOR_RESET "]\t%s\n", msg);
}

void IApp::WriteErr(const char *msg)
{
	fprintf(stderr, "[" ANSI_COLOR_RED "ERROR" ANSI_COLOR_RESET "]\t%s\n", msg);
}

void IApp::WriteDbg(const char *msg)
{
	fprintf(stdout, "[" ANSI_COLOR_YELLOW "DEBUG" ANSI_COLOR_RESET "]\t%s\n", msg);
}

} // namespace

