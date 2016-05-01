#-------------------------------------------------
#
# Project created by QtCreator 2016-04-30T15:54:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IHMo
TEMPLATE = app


SOURCES += main.cpp\
        ihmo.cpp \
    annonce.cpp \
    recherche.cpp \
    Models/modelannonce.cpp

HEADERS  += ihmo.h \
    annonce.h \
    recherche.h \
    Models/modelannonce.h

FORMS    += ihmo.ui \
    annonce.ui \
    recherche.ui
