TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    render.cpp \
    cyclicbuffer.cpp \
    filter.cpp \
    lowfilterbutterworth.cpp \
    freqdecoder.cpp \
    filterfactory.cpp

HEADERS += \
    cyclicbuffer.h \
    settings.h \
    filter.h \
    appparameters.h \
    lowfilterbutterworth.h \
    freqdecoder.h \
    peakdata.h \
    filterfactory.h

