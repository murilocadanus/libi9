TARGET = I9
TEMPLATE = lib
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += include/

unix {
	DEFINES	+= DEBUG I9_USE_JSON
	CONFIG += staticlib
	#LIBS	+= -lcurl
	target.path = ./lib
	INSTALLS += target
}
