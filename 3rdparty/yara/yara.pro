QT       -= core gui

TARGET = yara
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
INCLUDEPATH += $$PWD/src/
DEPENDPATH += $$PWD/src/
INCLUDEPATH += $$PWD/src/include
DEPENDPATH += $$PWD/src/include

include(../../build.pri)

CONFIG(debug, debug|release) {
    TARGET = yarad
} else {
    TARGET = yara
}

DEFINES += "OPENSSL_NO_DEPRECATED_3_0"

TARGETLIB_PATH = $$PWD

win32-g++ {
    contains(QT_ARCH, i386) {
        DESTDIR=$${TARGETLIB_PATH}/libs/win32-g++
    } else {
        DESTDIR=$${TARGETLIB_PATH}/libs/win64-g++
    }
}
win32-msvc* {
    contains(QMAKE_TARGET.arch, x86_64) {
        DESTDIR=$${TARGETLIB_PATH}/libs/win64-msvc
    } else {
        DESTDIR=$${TARGETLIB_PATH}/libs/win32-msvc
    }
}
unix:!macx {
    BITSIZE = $$system(getconf LONG_BIT)
    if (contains(BITSIZE, 64)) {
        DESTDIR=$${TARGETLIB_PATH}/libs/lin64
    }
    if (contains(BITSIZE, 32)) {
        DESTDIR=$${TARGETLIB_PATH}/libs/lin32
    }
}
unix:macx {
    DESTDIR=$${TARGETLIB_PATH}/libs/mac
}

SOURCES += \
    crypto.c \
    src/arena.c \
    src/compiler.c \
    src/hash.c \
    src/libyara.c \
    src/mem.c \
    src/modules.c \
    src/modules/dex/dex.c \
    src/modules/dotnet/dotnet.c \
    src/modules/elf/elf.c \
    src/modules/hash/hash.c \
    src/modules/macho/macho.c \
    src/modules/math/math.c \
    src/modules/pe/pe.c \
    src/modules/pe/pe_utils.c \
    src/proc/none.c


