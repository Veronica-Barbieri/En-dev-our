QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS = src/payment-day.ico

SOURCES += \
    main.cpp \
    src/model/cpp/contract.cpp \
    src/model/cpp/director.cpp \
    src/model/cpp/ftemployee.cpp \
    src/model/cpp/level0.cpp \
    src/model/cpp/level1.cpp \
    src/model/cpp/ptemployee.cpp \
    src/model/cpp/worker.cpp \
    src/payroll/payroll.cpp \
    src/view/cpp/qadddialog.cpp \
    src/view/cpp/qdeldialog.cpp \
    src/view/cpp/qemployeeforcalc.cpp \
    src/view/cpp/qemployeelistforcalc.cpp \
    src/view/cpp/qpromodialog.cpp \
    src/view/cpp/qemployee.cpp \
    src/view/cpp/qemployeelist.cpp \
    src/view/cpp/qemployeeinfo.cpp \
    src/view/cpp/qpayrollinfo.cpp \
    src/view/cpp/qsalaries.cpp \
    src/controller/cpp/qtsalariescontroller.cpp

HEADERS += \
    src/model/headers/contract.h \
    src/model/headers/director.h \
    src/model/headers/ftemployee.h \
    src/model/headers/level0.h \
    src/model/headers/level1.h \
    src/model/headers/ptemployee.h \
    src/model/headers/worker.h \
    src/model/headers/container.h \
    src/payroll/payroll.h \
    src/view/headers/qemployeelistforcalc.h \
    src/view/headers/qemployeeforcalc.h \
    src/view/headers/qdeldialog.h \
    src/view/headers/qadddialog.h \
    src/view/headers/qemployeelist.h \
    src/view/headers/qemployee.h \
    src/view/headers/qemployeeinfo.h \
    src/view/headers/qpayrollinfo.h \
    src/view/headers/qpromodialog.h \
    src/view/headers/qsalaries.h \
    src/controller/header/qtsalariescontroller.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
