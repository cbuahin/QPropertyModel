#Author Caleb Amoa Buahin
#Email caleb.buahin@gmail.com
#Date 2016
#License GNU General Public License (see <http://www.gnu.org/licenses/> for details).

QT       += core gui widgets

TARGET = QPropertyModelTesting
TEMPLATE = app

CONFIG-=app_bundle

INCLUDEPATH += ./include \
               ./../QPropertyModel/include


SOURCES += src/main.cpp \
           src/qpropertymodeltesting.cpp \
           src/stdafx.cpp \
           src/tempobject.cpp

HEADERS += include/qpropertymodeltesting.h \
           include/stdafx.h \
           include/tempobject.h


FORMS += forms/qpropertymodeltesting.ui

              
CONFIG(debug, debug|release) {
   DESTDIR = ./build/debug
   OBJECTS_DIR = $$DESTDIR/.obj
   MOC_DIR = $$DESTDIR/.moc
   RCC_DIR = $$DESTDIR/.qrc
   UI_DIR = $$DESTDIR/.ui

   macx{
   LIBS += -L$$PWD/../QPropertyModel/build/debug/ -lQPropertyModel.1.0.0
   }

   win32{
      LIBS += -L$$PWD/../QPropertyModel/build/debug/ -lQPropertyModel1
   }
}

CONFIG(release, debug|release) {
    DESTDIR = bin
    RELEASE_EXTRAS = ./build/release 
    OBJECTS_DIR = $$RELEASE_EXTRAS/.obj
    MOC_DIR = $$RELEASE_EXTRAS/.moc
    RCC_DIR = $$RELEASE_EXTRAS/.qrc
    UI_DIR = $$RELEASE_EXTRAS/.ui

    macx{
    LIBS += -L$$PWD/../QPropertyModel/lib -lQPropertyModel.1.0.0
    }

    win32{
    LIBS += -L$$PWD/../QPropertyModel/lib -lQPropertyModel1
    }
}        
