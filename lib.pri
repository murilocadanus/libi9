TARGET = I9
TEMPLATE = lib
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += include/

CONFIG(debug, debug|release) {
	TARGET = $${TARGET}_d
	DEFINES += DEBUG
}

CONFIG(release, debug|release) {
	TARGET = $${TARGET}
}

unix {
	DEFINES	+= DEBUG
	DEFINES	+= I9_USE_JSON
	CONFIG += staticlib
	#LIBS	+= -lcurl
	target.path = ./lib
	INSTALLS += target
}
