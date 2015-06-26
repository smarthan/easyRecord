#-------------------------------------------------
#
# Project created by QtCreator 2015-05-19T10:50:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Beginner
TEMPLATE = app


SOURCES += main.cpp\
    Beginner.cpp \
    CustomWidget.cpp \
    CommunicationThread.cpp \
    Ui_SerPorSet.cpp \
    Ui_Widget.cpp

HEADERS  += \
    Beginner.h \
    CustomWidget.h \
    CommunicationThread.h \
    Ui_SerPorSet.h \
    Ui_Widget.h

RESOURCES += \
    Beginner.qrc

QT       += serialport

TRANSLATIONS += zh_CN.ts
TRANSLATIONS += en_US.ts
TRANSLATIONS += ja_JP.ts
