TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    render.cpp \
    cyclicbuffer.cpp \
    average.cpp \
    filter.cpp \
    lowfilterbutterworth.cpp \
    freqdecoder.cpp

HEADERS += \
    cyclicbuffer.h \
    settings.h \
    average.h \
    filter.h \
    appparameters.h \
    lowfilterbutterworth.h \
    freqdecoder.h \
    peakdata.h

