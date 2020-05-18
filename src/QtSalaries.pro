TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        model/cpp/contract.cpp \
        model/cpp/director.cpp \
        model/cpp/ftemployee.cpp \
        model/cpp/level0.cpp \
        model/cpp/level1.cpp \
        model/cpp/main.cpp \
        model/cpp/ptemployee.cpp \
        model/cpp/worker.cpp

HEADERS += \
    model/headers/container.h \
    model/headers/contract.h \
    model/headers/director.h \
    model/headers/ftemployee.h \
    model/headers/level0.h \
    model/headers/level1.h \
    model/headers/ptemployee.h \
    model/headers/worker.h
