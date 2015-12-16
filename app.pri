TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

unix {
	DEFINES	+= DEBUG
	#LIBS	+= -lcurl

	#Configs
	APP_CONFIG_FILES.files = $$files($${PWD}/resources/configs/*.*)
	APP_CONFIG_FILES.path = $${OUT_PWD}/$${DESTDIR}/configs
	APP_CONFIG_FILES.commands += test -d $${APP_CONFIG_FILES.path} || mkdir -p $${APP_CONFIG_FILES.path} &&
	APP_CONFIG_FILES.commands += ${COPY_FILE} $$APP_CONFIG_FILES.files $${APP_CONFIG_FILES.path}

	QMAKE_EXTRA_TARGETS += APP_CONFIG_FILES
	POST_TARGETDEPS += APP_CONFIG_FILES
}
