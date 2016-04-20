TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    render.cpp \
    filter.cpp \
    lowfilterbutterworth.cpp \
    freqdecoder.cpp \
    filterfactory.cpp \
    buffer.cpp

HEADERS += \
    settings.h \
    filter.h \
    appparameters.h \
    lowfilterbutterworth.h \
    freqdecoder.h \
    peakdata.h \
    filterfactory.h \
    buffer.h

