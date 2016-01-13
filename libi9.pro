SOURCES +=	source/File.cpp \
			source/location/libGeoWeb.cpp \
			source/I9Init.cpp \
			source/util/Resolver.cpp \
			source/util/Log.cpp \
			source/interface/IApp.cpp \
			source/interface/IManager.cpp \
			source/Configuration.cpp

HEADERS +=	include/File.hpp \
			include/location/libGeoWeb.hpp \
			include/location/revgeo.hpp \
			include/Config.hpp \
			include/I9Init.hpp \
			include/Enum.hpp \
			include/Defines.hpp \
			include/util/Resolver.hpp \
			include/util/String.hpp \
			include/util/Log.hpp \
			include/interface/IApp.hpp \
			include/interface/IManager.hpp \
			include/I9Run.hpp \
			include/I9.hpp \
			include/Configuration.hpp

include("lib.pri")
include("compiler.pri")

