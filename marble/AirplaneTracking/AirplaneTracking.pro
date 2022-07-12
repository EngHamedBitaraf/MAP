QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mymarblewidget.cpp \
    worker.cpp

HEADERS += \
    mainwindow.h \
    mymarblewidget.h \
    worker.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.

unix:!macx:!symbian: LIBS += -L$$PWD/../../../marble/export/lib64/ -lmarblewidget-qt5

INCLUDEPATH += $$PWD/../../../marble/export/include
DEPENDPATH += $$PWD/../../../marble/export/include
