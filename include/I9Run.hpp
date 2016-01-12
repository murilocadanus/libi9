#ifndef I9RUN_HPP
#define I9RUN_HPP

#include "I9Init.hpp"
#include "interface/IApp.hpp"

template <class T>
int I9Run(int argc, char **argv, const char*config = "app.config")
{
	T app;
	Sascar::SetApp(&app, argc, argv, config);
	Sascar::Initialize();

	app.Initialize();
	//app.Process();
	app.Shutdown();

	Sascar::Shutdown();

	return EXIT_SUCCESS;
}

#endif // I9RUN_HPP
