CDPVERSION = 4.10
TYPE = library
PROJECTNAME = SZVSlib

DEPS += \

HEADERS += \
    Buttons.h \
    Copy.h \
    DataBase.h \
    Queue.h \
    szvslib.h \
    SZVSlibBuilder.h

SOURCES += \
    Buttons.cpp \
    Copy.cpp \
    DataBase.cpp \
    Queue.cpp \
    SZVSlibBuilder.cpp

DISTFILES += $$files(*.xml, true) \
    Templates/Models/SZVSlib.Buttons.xml \
    Templates/Models/SZVSlib.Copy.xml \
    Templates/Models/SZVSlib.DataBase.xml \
    Templates/Models/SZVSlib.Queue.xml

load(cdp)
