#ifndef I9RUN_HPP
#define I9RUN_HPP

#include "I9Init.hpp"
#include "interface/IApp.hpp"

template <class T>
int I9Run(int argc, char **argv, const char*config = "app.config")
{
	T app;

	// Load resources
	Sascar::SetApp(&app, argc, argv, config);

	// Init lib modules
	Sascar::Initialize();

	// Init app
	app.Initialize();

	// Process until not is finished
	while(!app.bIsFinished)
	{
		// Verify if don't has erros to keep processing
		if(app.Process()) app.bIsFinished = true;
	}

	// Shutdown app
	app.Shutdown();

	// Shutdown lib modules
	Sascar::Shutdown();

	return EXIT_SUCCESS;
}

#endif // I9RUN_HPP
