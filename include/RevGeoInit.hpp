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

#ifndef REVGEOINIT_HPP
#define REVGEORUN_HPP

#include "interface/IApp.hpp"

extern "C" {

namespace Sascar {

	/// Set the Application main class.
	/**
	When creating a new project, you must have a class that will use IApp as a base class. This class will be the main
	entrypoint to your app and must be set by usign this function.

	\param app A pointer to your application main class.
	\param argc Command line argument count.
	\param argv A pointer to the command line arguments.
	\param config A pointer to the config file.
	*/
	void SetApp(IApp *app, int argc, char **argv, const char *config = "app.config");

	/// Private states that are maintained, must not be accessed directly.
	namespace Private
	{
		/// A pointer to the IGameApp implementation.
		extern IApp		*pApplication;

		/// Flag indicating that Seed is Initialized or not.
		extern bool		bInitialized;

		/// Command line argument count.
		extern int		iArgc;

		/// Command line command string.
		extern char		**pcArgv;

		extern bool		bDisableSound;
		extern bool		bDisableThread;
		extern bool		bDisableResourceLoader;
		extern String	sConfigFile;

	} // namespace

} // namespace

} // extern C

#endif // REVGEOINIT_HPP
