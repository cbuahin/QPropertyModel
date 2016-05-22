#Author Caleb Amoa Buahin
#Email caleb.buahin@gmail.com
#Date 2016
#License GNU General Public License (see <http://www.gnu.org/licenses/> for details).

QT       += core widgets

TARGET = QPropertyModel
TEMPLATE = lib
VERSION = 1.0.0

DEFINES += QPROPERTYMODEL_LIBRARY

INCLUDEPATH += ./include

SOURCES +=  src/qbasepropertyitemeditor.cpp \
            src/qboolpropertyitem.cpp \
            src/qbrushpropertyitem.cpp \
            src/qchildboolpropertyitem.cpp \
            src/qchildbrushpropertyitem.cpp \
            src/qchildenumpropertyitem.cpp \
            src/qchildiconpropertyitem.cpp \
            src/qchildimagepropertyitem.cpp \
            src/qchildpointfpropertyitem.cpp \
            src/qchildpointpropertyitem.cpp \
            src/qcolorpropertyitemeditor.cpp \
            src/qenumpropertyitem.cpp \
            src/qflagspropertyitem.cpp \
            src/qfontfamilypropertyitem.cpp \
            src/qfontpropertyitem.cpp \
            src/qfontpropertyitemeditor.cpp \
            src/qiconpropertyitem.cpp \
            src/qimagepropertyitem.cpp \
            src/qimagepropertyitemeditor.cpp \
            src/qlinefpropertyitem.cpp \
            src/qlinepropertyitem.cpp \
            src/qobjectclasspropertyitem.cpp \
            src/qobjectpropertyitem.cpp \
            src/qpenpropertyitem.cpp \
            src/qpointfpropertyitem.cpp \
            src/qpointpropertyitem.cpp \
            src/qpopuppropertyitemeditor.cpp \
            src/qpropertyitem.cpp \
            src/qpropertyitemdelegate.cpp \
            src/qpropertymodel.cpp \
            src/qrectfpropertyitem.cpp \
            src/qrectpropertyitem.cpp \
            src/qselectfromlistpropertyitemeditor.cpp \
            src/qsizefpropertyitem.cpp \
            src/qsizepropertyitem.cpp \
            src/qstringlistpropertyitem.cpp \
            src/qvariantholderhelper.cpp \
            src/qvariantlistpropertyItem.cpp \
            src/qvariantpropertyitem.cpp \
            src/qvector2dpropertyitem.cpp \
            src/qvector3dpropertyitem.cpp \
            src/qvector4dpropertyitem.cpp \
            src/stdafx.cpp \
            src/qcustomeditors.cpp \
            src/qstringlistpropertyitemeditor.cpp \
            src/qvariantlistpropertyitemeditor.cpp \
            src/qobjectlistpropertyitem.cpp \
            src/qobjectlistpropertyitemeditor.cpp

HEADERS += \
            include/qbrushpropertyitem.h \
            include/qenumpropertyitem.h \
            include/qflagspropertyitem.h \
            include/qfontfamilypropertyitem.h \
            include/qfontpropertyitem.h \
            include/qiconpropertyitem.h \
            include/qimagepropertyitem.h \
            include/qlinefpropertyitem.h \
            include/qlinepropertyitem.h \
            include/qobjectclasspropertyitem.h \
            include/qobjectpropertyitem.h \
            include/qpenpropertyitem.h \
            include/qpointfpropertyitem.h \
            include/qpointpropertyitem.h \
            include/qpropertyitem.h \
            include/qpropertyitemdelegate.h \
            include/qpropertymodel_global.h \
            include/qpropertymodel.h \
            include/qrectfpropertyitem.h \
            include/qrectpropertyitem.h \
            include/qsizefpropertyitem.h \
            include/qsizepropertyitem.h \
            include/qstringlistpropertyitem.h \
            include/qvariantholderhelper.h \
            include/qvariantlistpropertyitem.h \
            include/qvariantpropertyItem.h \
            include/qvector2dpropertyitem.h \
            include/qvector3dpropertyitem.h \
            include/qvector4dpropertyitem.h \
            include/resource.h \
            include/stdafx.h \
            include/qcustomeditors.h \
            include/qchildpropertyitems.h \
            include/qboolpropertyitem.h \
            include/qobjectlistpropertyitem.h

PRECOMPILED_HEADER += include/stdafx.h

RESOURCES += ./resources/qpropertymodel.qrc

RC_FILE = ./resources/QPropertyModel.rc

FORMS += ./forms/qstringlistpropertyitemeditor.ui \
         ./forms/qcustomobjectlistpropertyitemeditor.ui
       
CONFIG(debug, debug|release) {
   DESTDIR = ./build/debug
   OBJECTS_DIR = $$DESTDIR/.obj
   MOC_DIR = $$DESTDIR/.moc
   RCC_DIR = $$DESTDIR/.qrc
   UI_DIR = $$DESTDIR/.ui
}

CONFIG(release, debug|release) {
    DESTDIR = lib
    RELEASE_EXTRAS = ./build/release 
    OBJECTS_DIR = $$RELEASE_EXTRAS/.obj
    MOC_DIR = $$RELEASE_EXTRAS/.moc
    RCC_DIR = $$RELEASE_EXTRAS/.qrc
    UI_DIR = $$RELEASE_EXTRAS/.ui
}        

