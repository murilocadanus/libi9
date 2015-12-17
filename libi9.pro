SOURCES +=	source/main.cpp \
			source/I9Init.cpp \
			source/util/Resolver.cpp \
			source/util/Log.cpp \
			source/interface/IApp.cpp \
			source/interface/IManager.cpp

HEADERS +=	include/Config.hpp \
			include/I9Init.hpp \
			include/Enum.hpp \
			include/Defines.hpp \
			include/util/Resolver.hpp \
			include/util/String.hpp \
			include/util/Log.hpp \
			include/interface/IApp.hpp \
			include/interface/IManager.hpp \
			include/I9Run.hpp \
			include/I9.hpp

include("lib.pri")
include("compiler.pri")

