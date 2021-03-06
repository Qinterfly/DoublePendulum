#-------------------------------------------------
#
# Project created by QtCreator 2019-02-14T18:36:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DoublePendulum
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS QCUSTOMPLOT_USE_LIBRARY
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        gui/main.cpp \
        gui/MainWindow.cpp \
    core/DifferentialEquations.cpp \
    test/Tests.cpp \
    core/PushBackSolution.cpp \
    core/SolutionOptions.cpp \
    gui/SetMethods.cpp \
    gui/InitializeMethods.cpp \
    gui/Calculation.cpp \
    gui/Plotting.cpp \
    gui/UpdateMethods.cpp \
    gui/ClearMethods.cpp

HEADERS += \
        gui/MainWindow.h \
    core/DifferentialEquations.h \
    core/Macroses.h \
    test/Tests.h \
    core/PushBackSolution.h \
    core/SolutionOptions.h

FORMS += \
        gui/MainWindow.ui

RESOURCES += \
    gui/resource.qrc

win32:RC_ICONS += $$PWD/gui/icons/app-icon.ico # Иконка к проекту

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Библиотека QCustomPlot
    # Windows
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lqcustomplot2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lqcustomplotd2
    # Unix
unix:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lqcustomplot
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lqcustomplotd

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

# Библиотека Boost
win32:INCLUDEPATH += C:/boost/boost_mingw_730_64/include/boost-1_69
win32:DEPENDPATH += C:/boost/boost_mingw_730_64/include/boost-1_69


