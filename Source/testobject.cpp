/****************************************************************************
**
**  Copyright (C) 2014 Caleb Amoa Buahin
**  Contact: calebgh@gmail.com
** 
**  This file is part of QPropertGrid.exe and QPropertGrid.dll
**
**  QPropertGrid.exe and QPropertGrid.dll and its associated files is free software; you can redistribute it and/or modify
**  it under the terms of the Lesser GNU General Public License as published by
**  the Free Software Foundation; either version 3 of the License, or
**  (at your option) any later version.
**
**  QPropertGrid.exe and QPropertGrid.dll and its associated files is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  Lesser GNU General Public License for more details.
**
**  You should have received a copy of the Lesser GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>
**
****************************************************************************/

#include "stdafx.h"
#include "TestObject.h"

TestObject::TestObject(QObject *parent)
	: QObject(parent), date(QDate::currentDate()), dateTime(QDateTime::currentDateTime()), name("Test")
{

	qobject = new QGraphicsItemAnimation(this);
	qwidget = new QTreeView();
	testEnum = TestEnum::TestA;
	flags = TestA | TestC;
}

TestObject::~TestObject()
{
	delete qobject;
	delete qwidget;
}

void TestObject::setName(const QString &name)
{
	this->name = name;
}

QString TestObject::getName() const
{
	return name;
}

void TestObject::setDate(const QDate& date)
{
	this->date = date;
}

QDate TestObject::getDate() const
{
	return date;
}
void TestObject::setDateTime(const QDateTime& dateTime)
{
	this->dateTime = dateTime;
}

QDateTime TestObject::getDateTime() const
{
	return this->dateTime;
}


void TestObject::setByteArray(const QByteArray& byteArray)
{
	this->byteArray = byteArray;
}

QByteArray TestObject::getByteArray() const
{
	return this->byteArray;
}

void TestObject::setUrl(const QUrl& url)
{
	this->url = url;
}

QUrl TestObject::getUrl() const
{
	return this->url;
}

void TestObject::setUint(const uint &uint)
{
	this->uintb = uint;
}

uint TestObject::getUint() const
{
	return uintb;
}

void TestObject::setBool(const bool &boolv)
{
	this->boolv = boolv;
}

bool TestObject::getBool() const
{
	return boolv	;
}

void TestObject::setQChar(const QChar &qchar)
{
	this->qchar = qchar;
}

QChar TestObject::getQChar() const
{
	return qchar;
}

void TestObject::setChar(const char &ochar)
{
	this->ochar = ochar;
}

char TestObject::getChar() const
{
	return ochar;
}

void TestObject::setQObject(QObject * const &qobject)
{
	this->qobject = qobject;
}

QObject *TestObject::getQObject() const
{
	return qobject;
}

void TestObject::setQWidget(QWidget * const &qwidget)
{
	this->qwidget = qwidget;
}

QWidget *TestObject::getQWidget() const
{
	return qwidget;
}

void TestObject::setCursor(const QCursor &cursor)
{
	this->cursor = cursor;
}

QCursor TestObject::getCursor() const
{
	return cursor;
}

void TestObject::setSize(const QSize &size)
{
	this->size = size;
}

QSize TestObject::getSize() const
{
	return size;
}

void TestObject::setList(const QList<QVariant> &list)
{
	this->list = list;
}

QList<QVariant> TestObject::getList() const
{
	return list;
}

void TestObject::setPolygon(const QPolygon &polygon)
{
	this->polygon = polygon;
}

QPolygon TestObject::getPolygon() const
{
	return polygon;
}

void TestObject::setColor(const QColor &color)
{
	this->color = color;
}

QColor TestObject::getColor() const
{
	return color;
}

void TestObject::setSizeF(const QSizeF &sizef)
{
	this->sizef = sizef;
}

QSizeF TestObject::getSizeF() const
{
	return sizef;
}

void TestObject::setQRectF(const QRectF &rectf)
{
	this->rectf = rectf;
}

QRectF TestObject::getQRectF() const
{
	return rectf;
}

void TestObject::setQLine(const QLine &line)
{
	this->line = line;
}

QLine TestObject::getQLine() const
{
	return line;
}

void TestObject::setQStringList(const QStringList &stringList)
{
	this->stringList = stringList;
}

QStringList TestObject::getQStringList() const
{
	return stringList;
}

void TestObject::setQVariantMap(const QVariantMap &variantMap)
{
	this->variantMap = variantMap;
}

QVariantMap TestObject::getQVariantMap() const
{
	return variantMap;
}

void TestObject::setQVariantHash(const QVariantHash &variantHash)
{
	this->variantHash = variantHash;
}

QVariantHash TestObject::getQVariantHash() const
{
	return variantHash;
}

void TestObject::setQIcon(const QIcon &icon)
{
	this->icon = icon;
}

QIcon TestObject::getQIcon() const
{
	return icon;
}

void TestObject::setQLineF(const QLineF &linef)
{
	this->linef = linef;
}

QLineF TestObject::getQLineF() const
{
	return linef;
}

void TestObject::setQRect(const  QRect & rect)
{
	this->rect = rect;
}
QRect TestObject::getQRect() const
{
	return rect;
}

void TestObject::setQPoint(const  QPoint & point)
{
	this->point = point;
}
QPoint TestObject::getQPoint() const
{
	return point;
}

void TestObject::setQRegExp(const  QRegExp & qRegex)
{
	this->qRegex = qRegex;
}
QRegExp TestObject::getQRegExp() const
{
	return qRegex;
}

void TestObject::setQPointf(const  QPointF & pointf)
{
	this->pointf = pointf;
}
QPointF TestObject::getQPointf() const
{
	return pointf;
}

void TestObject::setQPalette(const  QPalette & palette)
{
	this->palette = palette;
}
QPalette TestObject::getQPalette() const
{
	return palette;
}

void TestObject::setQFont(const  QFont & font)
{
	this->font = font;
}
QFont TestObject::getQFont() const
{
	return font;
}

void TestObject::setQBrush(const  QBrush & brush)
{
	this->brush = brush;
}

QBrush TestObject::getQBrush() const
{
	return brush;
}

void TestObject::setQBrushTest(const  QBrush & brushtest)
{
	this->brushtest = brushtest;
}

QBrush TestObject::getQBrushTest() const
{
	return this->brushtest;
}


void TestObject::setQPen(const  QPen & pen)
{
	this->pen = pen;
}

QPen TestObject::getQPen() const
{
	return this->pen;
}


void TestObject::setQSizePolicy(const  QSizePolicy & sizepolicy)
{
	this->sizepolicy = sizepolicy;
}

QSizePolicy TestObject::getQSizePolicy() const
{
	return sizepolicy;
}

void TestObject::setQMatrix(const  QMatrix & matrix)
{
	this->matrix = matrix;
}

QMatrix TestObject::getQMatrix() const
{
	return this->matrix;
}

void TestObject::setQTransform(const  QTransform & transform)
{
	this->transform = transform;
}

QTransform TestObject::getQTransform() const
{
	return transform;
}

void TestObject::setQMatrix4x4(const  QMatrix4x4 & matrix4x4)
{
	this->matrix4x4 = matrix4x4;
}

QMatrix4x4 TestObject::getQMatrix4x4() const
{
	return matrix4x4;
}

void TestObject::setQVector2D(const  QVector2D & vector2D)
{
	this->vector2D = vector2D;
}

QVector2D TestObject::getQVector2D() const
{
	return vector2D;
}

void TestObject::setQVector3D(const  QVector3D & vector3D)
{
	this->vector3D = vector3D;
}

QVector3D TestObject::getQVector3D() const
{
	return vector3D;
}

void TestObject::setQVector4D(const  QVector4D & vector4D)
{
	this->vector4D = vector4D;
}

QVector4D TestObject::getQVector4D() const
{
	return vector4D;
}

void TestObject::setTestEnum(TestEnum testEnum)
{
	this->testEnum = testEnum;
}

TestObject::TestEnum TestObject::getTestEnum() const
{
	return testEnum;
}

void TestObject::setTestEnumFlags(TestEnums flags)
{
	this->flags = flags;
}

TestObject::TestEnums TestObject::getTestEnumFlags() const
{
	return this->flags;
}

void TestObject::setKeySequence(const QKeySequence& sequence)
{
	this->sequence =  sequence;
}

QKeySequence TestObject::getKeySequence() const
{
	return sequence;
}

void TestObject::setQPixmap(const QPixmap& pixmap)
{
	this->pixmap = pixmap;
}

QPixmap TestObject::getQPixmap() const
{
	return pixmap;
}

void TestObject::setQImage(const QImage& image)
{
	this->image = image;
}

QImage TestObject::getQImage() const
{
	return image;
}

void TestObject::setQBitmap(const QBitmap& bitmap)
{
	this->bitmap = bitmap;
}

QBitmap TestObject::getQBitmap() const
{
	return bitmap;
}

void TestObject::reset()
{
	name ="resetName";
	date = QDate::currentDate();
	dateTime = QDateTime::currentDateTime();
	url = QUrl("http://www.gthsansa.com");
	boolv = false;
}
