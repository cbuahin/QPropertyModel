#-------------------------------------------------
#
# Project created by QtCreator 2016-02-17T23:40:14
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = QPropertyModelTesting
TEMPLATE = app

INCLUDEPATH += ./include \
               ./../QPropertyModel/include \
               $$PWD/../QPropertyModel/bin/debug \
               $$PWD/../QPropertyModel/bin/release

SOURCES += src/main.cpp \
           src/qpropertymodeltesting.cpp \
           src/stdafx.cpp \
           src/tempobject.cpp

HEADERS += include/qpropertymodeltesting.h \
           include/stdafx.h \
           include/tempobject.h


FORMS += forms/qpropertymodeltesting.ui

LIBS += -L$$PWD/../QPropertyModel/bin/debug/ -lQPropertyModel.1.0.0

DEPENDPATH += $$PWD/../QPropertyModel/bin/debug \
              $$PWD/../QPropertyModel/bin/release
