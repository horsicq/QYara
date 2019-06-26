INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
INCLUDEPATH += $$PWD/libyara/include
DEPENDPATH += $$PWD/libyara/include

HEADERS += \
    $$PWD/qyara.h 

SOURCES += \
    $$PWD/qyara.cpp 
	
win32-g++ {
    LIBS += $$PWD/libs/win32-g++/libyara.lib
}
win32-msvc* {
    contains(QMAKE_TARGET.arch, x86_64) {
        LIBS += $$PWD/libs/win64-msvc/yara.lib
    } else {
        LIBS += $$PWD/libs/win32-msvc/yara.lib
    }
#    LIBS += Advapi32.lib
}
unix:!macx {
    BITSIZE = $$system(getconf LONG_BIT)
    if (contains(BITSIZE, 64)) {
        LIBS +=  $$PWD/libs/lin64/libyara.a
    }
    if (contains(BITSIZE, 32)) {
        #TODO
    }
}
unix:macx {
    LIBS +=  $$PWD/libs/mac/libyara.a
}

include(../QOpenSSL/openssl.pri)

