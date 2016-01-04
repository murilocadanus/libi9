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

#ifndef I9INIT_HPP
#define I9INIT_HPP

#include "interface/IApp.hpp"

typedef unsigned long long int 	u64;
typedef unsigned int 			u32;
typedef unsigned short int 		u16;
typedef unsigned char 			u8;
typedef signed long long int	s64;
typedef signed int 				s32;
typedef signed short int 		s16;
typedef signed char 			s8;
typedef float 					f32;

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

	/// Displays a output message by using IApp::WriteOut implementation.
	/**
	This method is a channeling point to all output messages that Seed will use. If you do not override IApp::WriteOut, it
	will use the default stdout output pipe.

	\param msg Pointer to a string to be displayed.
	*/
	void WriteOut(const char *msg);

	/// Displays a error message by using IApp::WriteErr implementation.
	/**
	This method is a channeling point to all error messages that I9 will use. If you do not override IApp::WriteErr, it
	will use the default stderr output pipe.
	*/
	void WriteErr(const char *msg);

	/// Initialize I9
	/**
	This will initialize all I9 states and subsystems and must be called before anything and after Sascar::SetApp.
	*/
	bool Initialize();

	/// Update I9
	/**
	Will update all I9 states and subsystems and will be called once per tick until a shutdown or error happens.
	*/
	void Update();

	/// Shutdown I9
	/**
	Will reset all Seed states and shutdown all subsystems. Nothing more from I9 can be used until a new Initialize happens.
	*/
	void Shutdown();

	/// Get the version of the linked I9 lib
	/**
	Get the linked library version number, you can pass null to ignore any parameter.
	*/
	void GetVersion(u32 *major, u32 *middle, u32 *minor);

	int CommandLineParameter(char **argv, int pos);
	void CommandLineParse(int argc, char **argv);

	/// Private states that are maintained, must not be accessed directly.
	namespace Private
	{
		/// A pointer to the IApp implementation.
		extern IApp		*pApplication;

		/// Flag indicating that Seed is Initialized or not.
		extern bool		bInitialized;

		/// Command line argument count.
		extern int		iArgc;

		/// Command line command string.
		extern char		**pcArgv;

		extern bool		bDisableThread;
		extern bool		bDisableResourceLoader;
		extern String	sConfigFile;

	} // namespace

} // namespace

} // extern C

#endif // I9INIT_HPP
