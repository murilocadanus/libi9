SOURCES +=	\
			source/I9Init.cpp \
			source/Manager.cpp \
			source/File.cpp \
			source/FileSystem.cpp \
			source/Configuration.cpp \
			source/Job.cpp \
			source/Thread.cpp \
			source/ThreadManager.cpp \
			source/Memory.cpp \
			source/Reader.cpp \
			source/EventSystem.cpp \
			source/ResourceLoader.cpp \
			source/ResourceGroup.cpp \
			source/EventResourceLoader.cpp \
			source/JobManager.cpp \
			source/Updater.cpp \
			source/Profiler.cpp \
			source/util/Log.cpp \
			source/ResourceManager.cpp \
			source/api/net/Address.cpp \
			source/api/net/UDPSocket.cpp \
			source/api/yajl/JsonReader.cpp \
			#source/api/yajl/JsonWriter.cpp \
			source/interface/IApp.cpp \
			source/interface/IManager.cpp \
			source/interface/IReader.cpp \
			source/interface/ISystem.cpp \
			source/interface/IResource.cpp \
			source/location/libGeoWeb.cpp \
			source/platform/console/ConsoleSystem.cpp \
			source/platform/console/I9Posix.cpp

HEADERS +=	include/Config.hpp \
			include/I9Init.hpp \
			include/Enum.hpp \
			include/Timer.hpp \
			include/Defines.hpp \
			include/Container.hpp \
			include/Singleton.hpp \
			include/File.hpp \
			include/FileSystem.hpp \
			include/Configuration.hpp \
			include/Manager.hpp \
			include/System.hpp \
			include/Job.hpp \
			include/Thread.hpp \
			include/ThreadManager.hpp \
			include/Memory.hpp \
			include/System.hpp \
			include/Reader.hpp \
			include/ResourceManager.hpp \
			include/EventSystem.hpp \
			include/ResourceLoader.hpp \
			include/ResourceGroup.hpp \
			include/EventResourceLoader.hpp \
			include/JobManager.hpp \
			include/Updater.hpp \
			include/Profiler.hpp \
			include/util/String.hpp \
			include/util/Log.hpp \
			include/api/net/Address.hpp \
			include/api/net/UDPSocket.hpp \
			include/api/yajl/JsonReader.hpp \
			#include/api/yajl/JsonWriter.hpp \
			include/interface/IApp.hpp \
			include/interface/IManager.hpp \
			include/interface/IObject.hpp \
			include/interface/IReader.hpp \
			include/interface/ISystem.hpp \
			include/interface/IUpdatable.hpp \
			include/interface/IEvent.hpp \
			include/interface/IEventListener.hpp \
			include/interface/IEventSystemListener.hpp \
			include/interface/IEvent.hpp \
			include/interface/IResource.hpp \
			include/interface/IEventResourceLoaderListener.hpp \
			include/location/libGeoWeb.hpp \
			include/location/revgeo.hpp \
			include/platform/console/ConsoleSystem.hpp \
			include/platform/console/Platform.hpp \
			include/I9Run.hpp \
			include/I9.hpp

include("lib.pri")
include("compiler.pri")
