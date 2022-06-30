CDPVERSION = 4.10
TYPE = system
load(cdp)

DISTFILES += $$files(*.xml, false)

SUBDIRS +=     \
    ConsoleApp \
    DataBase \
    GUIApp
