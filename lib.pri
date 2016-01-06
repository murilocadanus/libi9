TARGET = I9
TEMPLATE = lib
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += include/

unix {
	DEFINES	+= DEBUG BUILD_CONSOLE
	CONFIG += staticlib
	LIBS	+= -lmongoclient -lcurl
	target.path = ./lib
	INSTALLS += target
}
