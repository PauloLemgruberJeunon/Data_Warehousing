TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
DESTDIR = bin

# Optimization flags
QMAKE_CXXFLAGS  -= -O -O1
QMAKE_CXXFLAGS  += -O2 -ansi

# Warnings
QMAKE_CXXFLAGS  += -Wall -Wconversion

# Temporary dirs
OBJECTS_DIR = tmp/obj
MOC_DIR = tmp/moc
UI_DIR = tmp/moc
RCC_DIR = tmp/rc

SOURCES += \
    src/main.c \
    src/graph/graph.c \
    src/menu/menu.c \
    src/menu/utils.c

HEADERS += \
    src/graph/graph.h \
    src/menu/menu.h \
    src/utils.h \
    src/consts/bool.h \
    src/consts/printColors.h \
    src/menu/utils.h
