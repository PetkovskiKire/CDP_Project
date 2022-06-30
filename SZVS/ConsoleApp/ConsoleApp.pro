TYPE = application
PROJECTNAME = ConsoleApp

DEPS += externalcontrolio szvslib

HEADERS += Libraries.h
SOURCES += CDPMain.cpp

DISTFILES += \
    $$files(*.xml, true) \
    $$files(*.lic, true) \
    $$files(Application/www/*.*, true)

load(cdp)

ID = 213597737352533 # do not change
