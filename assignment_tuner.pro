TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    render.cpp \
    cyclicbuffer.cpp \
    average.cpp \
    filter.cpp \
    filterbutterworth.cpp

HEADERS += \
    cyclicbuffer.h \
    settings.h \
    average.h \
    filter.h \
    filterbutterworth.h \
    appparameters.h

