INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
INCLUDEPATH += $$PWD/3rdparty/yara/include
DEPENDPATH += $$PWD/3rdparty/yara/include

HEADERS += \
    $$PWD/qyara.h 

SOURCES += \
    $$PWD/qyara.cpp 
	
win32-g++ {
    LIBS += $$PWD/3rdparty/yara/win32-g++/libyara.lib
}
win32-msvc* {
    contains(QMAKE_TARGET.arch, x86_64) {
        LIBS += $$PWD/3rdparty/yara/libs/win64-msvc/yara.lib
    } else {
        LIBS += $$PWD/3rdparty/yara/libs/win32-msvc/yara.lib
    }
#
#    LIBS += Advapi32.lib
}

unix:!macx {
    BITSIZE = $$system(getconf LONG_BIT)
    if (contains(BITSIZE, 64)) {
        LIBS +=  $$PWD/3rdparty/yara/libs/lin64/libyara.a
    }
    if (contains(BITSIZE, 32)) {
        #TODO
    }
}
unix:macx {
    LIBS +=  $$PWD/3rdparty/yara/libs/mac/libyara.a
}

include(../QOpenSSL/openssl.pri)
