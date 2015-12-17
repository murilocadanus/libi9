SOURCES += source/main.cpp
SOURCES += source/RevGeoInit.cpp
SOURCES += source/util/Resolver.cpp
SOURCES += source/util/Log.cpp
SOURCES += source/interface/IApp.cpp
SOURCES += source/interface/IManager.cpp

HEADERS += include/Config.hpp
HEADERS += include/Enum.hpp
HEADERS += include/Defines.hpp
HEADERS += include/RevGeoRun.hpp
HEADERS += include/RevGeoInit.hpp
HEADERS += include/util/Resolver.hpp
HEADERS += include/util/String.hpp
HEADERS += include/util/Log.hpp
HEADERS += include/interface/IApp.hpp
HEADERS += include/interface/IManager.hpp

OTHER_FILES += resources/configs/sascloud.config

include("app.pri")
include("compiler.pri")

