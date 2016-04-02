TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    render.cpp \
    cyclicbuffer.cpp

HEADERS += \
    cyclicbuffer.h \
    settings.h

