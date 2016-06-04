#-------------------------------------------------
#
# Project created by QtCreator 2016-05-19T17:33:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoPoker
TEMPLATE = app


SOURCES += main.cpp\
        Controller/mainview.cpp \
    Model/videopokergame.cpp \
    Model/Hand.cpp \
    Model/Card.cpp \
    Model/Deck.cpp \


HEADERS  += Controller/mainview.h \
    Model/videopokergame.h \
    Model/Hand.h \
    Model/Deck.h \
    Model/Card.h

FORMS    += View/mainview.ui

RESOURCES += \
    Media/resources.qrc
