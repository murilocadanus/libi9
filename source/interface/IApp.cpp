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

#include "interface/IApp.hpp"

#define TAG "[App] "

namespace Sascar {

IApp::IApp()
	//: cResourceManager("IApp")
{
}

IApp::~IApp()
{
}

bool IApp::Shutdown()
{
	Log(TAG "Shutting down...");

	//cResourceManager.Print();
	//cResourceManager.Reset();

	return true;
}

void IApp::WriteOut(const char *msg)
{
	fprintf(stdout, "%s\n", msg);
	//Log(msg);
}

void IApp::WriteErr(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	//Error(msg);
}

void IApp::WriteDbg(const char *msg)
{
	fprintf(stdout, "%s\n", msg);
	//Dbg(msg);
}

/*ResourceManager *IApp::GetResourceManager()
{
	return &cResourceManager;
}*/

} // namespace

