#ifndef I9RUN_HPP
#define I9RUN_HPP

#include "I9Init.hpp"
#include "System.hpp"

template <class T>
int I9Run(int argc, char **argv, const char*config = "app.config")
{
	T app;
	//Sascar::SetApp(&app, argc, argv, config);
	/*if(Sascar::Initialize())
	{
		while (!pSystem->IsShuttingDown())
		{
			Sascar::Update();
		}
	}
	Sascar::Shutdown();*/

	return EXIT_SUCCESS;
}

#endif // I9RUN_HPP
