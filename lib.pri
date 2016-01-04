TARGET = I9
TEMPLATE = lib
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += include/

unix {
	DEFINES	+= DEBUG
	CONFIG += staticlib
	#LIBS	+= -lcurl
	target.path = ./build
	INSTALLS += target
}
