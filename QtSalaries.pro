TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        contract.cpp \
        director.cpp \
        ftemployee.cpp \
        level0.cpp \
        level1.cpp \
        main.cpp \
        ptemployee.cpp \
        worker.cpp

HEADERS += \
    Container.h \
    contract.h \
    director.h \
    ftemployee.h \
    level0.h \
    level1.h \
    ptemployee.h \
    worker.h
