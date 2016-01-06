#include "interface/IApp.hpp"

#define TAG "[App] "

namespace Sascar {

IApp::IApp()
	: cResourceManager("IApp")
{
}

IApp::~IApp()
{
}

bool IApp::Shutdown()
{
	Log(TAG "Shutting down...");

	cResourceManager.Print();
	cResourceManager.Reset();

	return true;
}

void IApp::WriteOut(const char *msg)
{
	fprintf(stdout, "%s\n", msg);
	LEAF(Log(msg));
}

void IApp::WriteErr(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	LEAF(Error(msg));
}

void IApp::WriteDbg(const char *msg)
{
	fprintf(stdout, "%s\n", msg);
	LEAF(Dbg(msg));
}

ResourceManager *IApp::GetResourceManager()
{
	return &cResourceManager;
}

} // namespace

