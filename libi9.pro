SOURCES +=	source/File.cpp \
			source/Reader.cpp \
			source/I9Init.cpp \
			source/util/Resolver.cpp \
			source/util/Log.cpp \
			source/interface/IApp.cpp \
			source/interface/IManager.cpp \
			source/interface/IReader.cpp \
			source/api/yajl/JsonReader.cpp \
			source/api/curl/CurlWrapper.cpp \
			source/api/mysql/MySQLConnector.cpp \
			source/api/net/Address.cpp \
			source/api/net/UDPSocket.cpp \
			source/Configuration.cpp \
			source/interface/IEventFileSystem.cpp \
			source/Manager.cpp \
			source/FileSystem.cpp \
			source/EventFileSystem.cpp \
			source/Updater.cpp \
			source/interface/ISystem.cpp \
			source/System.cpp \
			source/MessageQueue.cpp \
			source/interface/IEventMessageQueue.cpp \
			source/EventMessageQueue.cpp \
			source/api/net/TCPSocket.cpp

HEADERS +=	include/File.hpp \
			include/Reader.hpp \
			include/Config.hpp \
			include/I9Init.hpp \
			include/Enum.hpp \
			include/Defines.hpp \
			include/util/Resolver.hpp \
			include/util/String.hpp \
			include/util/Log.hpp \
			include/interface/IApp.hpp \
			include/interface/IEvent.hpp \
			include/interface/IManager.hpp \
			include/interface/IReader.hpp \
			include/api/yajl/JsonReader.hpp \
			include/api/curl/CurlWrapper.hpp \
			include/api/mysql/MySQLConnector.hpp \
			include/api/net/Address.hpp \
			include/api/net/UDPSocket.hpp \
			include/I9Run.hpp \
			include/I9.hpp \
			include/Configuration.hpp \
			include/interface/IEventFileSystemListener.hpp \
			include/interface/IEventListener.hpp \
			include/interface/IEventFileSystem.hpp \
			include/Container.hpp \
			include/Updater.hpp \
			include/interface/IUpdatable.hpp \
			include/Manager.hpp \
			include/FileSystem.hpp \
			include/EventFileSystem.hpp \
			include/Timer.hpp \
			include/interface/ISystem.hpp \
			include/System.hpp \
			include/EventQueue.hpp \
			include/interface/IEventMessageQueue.hpp \
			include/interface/IEventMessageQueueListener.hpp \
			include/MessageQueue.hpp \
			include/api/net/TCPSocket.hpp

include("lib.pri")
include("compiler.pri")
