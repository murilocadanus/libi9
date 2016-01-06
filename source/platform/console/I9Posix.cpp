
#include "platform/console/Platform.hpp"

#if defined(__linux__) || defined(__APPLE_CC__) || defined(__FLASHPLAYER) || defined(EMSCRIPTEN)

#include "util/Log.hpp"

#include <wchar.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <string>
#include <locale>
#include <iostream>
#include <sstream>

#include "I9Init.hpp"

#define TAG	"[Platform] "

#if I9_PATH_WIDE == 1
std::wstring widen(const std::string &str)
{
	using namespace std;

	wostringstream wstm;
	const ctype<wchar_t> &ctfacet = use_facet< ctype<wchar_t> >(wstm.getloc());
	for (size_t i = 0; i < str.size(); ++i)
		wstm << ctfacet.widen(str[i]);

	return wstm.str();
}

std::string narrow(const std::wstring &str)
{
	using namespace std;

	ostringstream stm;
	const ctype<char> &ctfacet = use_facet< ctype<char> >(stm.getloc());
	for (size_t i = 0 ; i < str.size(); ++i)
		stm << ctfacet.narrow(str[i], 0);

	return stm.str();
}
#endif

bool create_directory(const char *path)
{
	bool ret = false;
	int err = mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	if (err == -1)
	{
		switch (errno)
		{
			case EACCES:
			{
				Info(TAG "Permission denied to create '%s'.", path);
			}
			break;

			case EEXIST:
			{
				Info(TAG "Path '%s' already exists.", path);
			}
			break;

			case ENAMETOOLONG:
			{
				Info(TAG "Path name too long: '%s'", path);
			}
			break;

			case ENOENT:
			{
				Info(TAG "Path '%s' does not name an existing entry.", path);
			}
			break;

			case ENOSPC:
			{
				Info(TAG "Not enought space to create '%s'.", path);
			}
			break;

			case ENOTDIR:
			{
				Info(TAG "A component of the path '%s' is not a directory.", path);
			}
			break;

			case EROFS:
			{
				Info(TAG "Read-only filesystem, could not create '%s'.", path);
			}
			break;

			default:
			{
				Info(TAG "An error '%d' ocurred trying to create '%s'.", err, path);
			}
			break;
		}
	}
	else
	{
		ret = true;
	}

	return ret;
}

const char *get_user_name()
{
	const char *name = (char *)getenv("LOGNAME");
	if (!name)
		name = (const char *)"Noname";
	return name;
}

const char *get_user_appdata_folder()
{
	return get_user_home_folder();
}

const char *get_user_home_folder()
{
	const char *chome = getenv("HOME");
	const char *home = (char *)chome;
	if (!home)
		home = (const char *)"./";

	return home;
}

void get_current_directory(char *buff, int size)
{
#if defined(BUILD_IOS)
	memset(buff, '\0', size);
	memcpy(buff, iosGetRootPath(), size);
#elif defined(__APPLE_CC__)
	Sascar::Private::iArgc = 1;
	int len = (int)strlen(Sascar::Private::pcArgv[0]);
	memcpy(pcBundle, Sascar::Private::pcArgv[0], len);
	while (pcBundle[len] != '/') len--;
	len -= (u32)strlen("MacOS");
	memset(&pcBundle[len], '\0', sizeof(pcBundle) - len);
	strcpy(&pcBundle[len], "Resources");

	memcpy(buff, pcBundle, size);
#else
	char *b = (char *)static_cast<void *>(buff);
	char *out = getcwd(b, size);
	UNUSED(out);
#endif
}

bool change_directory(const char *to)
{
	bool ret = false;
	const char *path = (const char *)to;
	int err = chdir(path);

	if (err == -1)
	{
		switch (errno)
		{
			case EACCES:
			{
				Info(TAG "Permission denied to create '%s'.", path);
			}
			break;

			case EEXIST:
			{
				Info(TAG "Path '%s' already exists.", path);
			}
			break;

			case ENAMETOOLONG:
			{
				Info(TAG "Path name too long: '%s'", path);
			}
			break;

			case ENOENT:
			{
				Info(TAG "Path '%s' does not name an existing entry.", path);
			}
			break;

			case ENOSPC:
			{
				Info(TAG "Not enought space to create '%s'.", path);
			}
			break;

			case ENOTDIR:
			{
				Info(TAG "A component of the path '%s' is not a directory.", path);
			}
			break;

			case EROFS:
			{
				Info(TAG "Read-only filesystem, could not create '%s'.", path);
			}
			break;

			default:
			{
				Info(TAG "An error '%d' ocurred trying to create '%s'.", err, path);
			}
			break;
		}
	}
	else
	{
		ret = true;
	}

	return ret;
}

void print_system_info()
{
	Log(TAG "print_system_info not implemented for posix.");
	WARNING(TODO - Must implement function print_system_info)
}

bool system_check_multiple_instance()
{
	Log(TAG "system_check_multiple_instance not implemented for posix");
	WARNING(TODO - Must implement function system_check_multiple_instance)
	return true;
}

#endif
