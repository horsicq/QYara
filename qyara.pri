INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
INCLUDEPATH += $$PWD/3rdparty/yara/include
DEPENDPATH += $$PWD/3rdparty/yara/include

HEADERS += \
    $$PWD/qyara.h 

SOURCES += \
    $$PWD/qyara.cpp
    
!contains(XCONFIG, yara) {
    XCONFIG += yara
    include($$PWD/3rdparty/yara/yara.pri)
}
