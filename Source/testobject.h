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

#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <QObject>

class TestObject : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString QtString READ getName WRITE setName RESET reset)
	Q_PROPERTY(QDate QtDate READ getDate WRITE setDate RESET reset)
	Q_PROPERTY(QDateTime QtDateTime READ getDateTime WRITE setDateTime RESET reset)
	Q_PROPERTY(QStringList QtStringList READ getQStringList WRITE setQStringList)
	Q_PROPERTY(QByteArray ByteArray READ getByteArray WRITE setByteArray)
	Q_PROPERTY(QUrl QtUrl READ getUrl WRITE setUrl RESET reset)
	Q_PROPERTY(uint Uint READ getUint WRITE setUint RESET reset)
	Q_PROPERTY(bool Boolean READ getBool WRITE setBool RESET reset)
	Q_PROPERTY(QChar QtChar READ getQChar WRITE setQChar RESET reset)
	Q_PROPERTY(char OChar READ getChar WRITE setChar)
	Q_PROPERTY(QObject*  QtObject READ getQObject WRITE setQObject)
	Q_PROPERTY(QWidget*  QtWidget READ getQWidget WRITE setQWidget)
	Q_PROPERTY(QCursor  QtCursor READ getCursor WRITE setCursor)
	Q_PROPERTY(QSize  QtSize READ getSize WRITE setSize)
	Q_PROPERTY(QList<QVariant>  QtList READ getList WRITE setList)
	Q_PROPERTY(QPolygon  QtPolygon READ getPolygon  WRITE setPolygon )
	Q_PROPERTY(QColor  QtColor READ getColor WRITE setColor)
	Q_PROPERTY(QSizeF  QtSizeF READ getSizeF WRITE setSizeF)
	Q_PROPERTY(QRectF  QtRectF READ getQRectF WRITE setQRectF)
    Q_PROPERTY(QStringList  QtStringList READ getQStringList WRITE setQStringList)
	Q_PROPERTY(QVariantMap  QtVariantMap READ getQVariantMap WRITE setQVariantMap)
	Q_PROPERTY(QVariantHash  QtVariantHash READ getQVariantHash WRITE setQVariantHash)
	Q_PROPERTY(QIcon  QtQIcon READ getQIcon WRITE setQIcon)
	Q_PROPERTY(QLineF  QtLineF READ getQLineF WRITE setQLineF)
	Q_PROPERTY(QRect  QtRect READ getQRect WRITE setQRect)
	Q_PROPERTY(QPoint  QtPoint READ getQPoint WRITE setQPoint)
	Q_PROPERTY(QRegExp  QtRegExp READ getQRegExp WRITE setQRegExp)
	Q_PROPERTY(QPointF  QtPointF READ getQPointf WRITE setQPointf)
	Q_PROPERTY(QPalette  QtPalette READ getQPalette WRITE setQPalette)
	Q_PROPERTY(QFont  QtFont READ getQFont WRITE setQFont)
	Q_PROPERTY(QBrush  QtBrush READ getQBrush WRITE setQBrush)
	Q_PROPERTY(QImage  QtImage READ getQImage WRITE setQImage)
	Q_PROPERTY(QSizePolicy  QtSizePolicy READ getQSizePolicy WRITE setQSizePolicy)
	Q_PROPERTY(QMatrix  QtMatrix READ getQMatrix WRITE setQMatrix)
	Q_PROPERTY(QTransform  QtTransform READ getQTransform WRITE setQTransform)
	Q_PROPERTY(QMatrix4x4  QtMatrix4x4 READ getQMatrix4x4 WRITE setQMatrix4x4)
	Q_PROPERTY(QVector2D  QtVector2D READ getQVector2D WRITE setQVector2D)
	Q_PROPERTY(QVector3D  QtVector3D READ getQVector3D WRITE setQVector3D)
	Q_PROPERTY(QVector4D  QtVector4D READ getQVector4D WRITE setQVector4D)

public:
	TestObject(QObject *parent);
	~TestObject();


	void setName(const  QString & name);
    QString getName() const;

	void setDate(const QDate& date);
	QDate getDate() const;

	void setDateTime(const QDateTime& dateTime);
	QDateTime getDateTime() const;

	void setByteArray(const QByteArray& byteArray);
	QByteArray getByteArray() const;

	void setUrl(const QUrl& url);
	QUrl getUrl() const;

	void setUint(const uint& uint);
	uint getUint() const;

	void setBool(const bool& boolv);
	bool getBool() const;

	void setQChar(const QChar& qchar);
	QChar getQChar() const;

    void setChar(const char& ochar);
	char getChar() const;

	void setQObject(QObject* const & qobject);
    QObject *getQObject() const;

	void setQWidget(QWidget* const & qwidget);
	QWidget* getQWidget() const;


	void setCursor(const  QCursor & cursor);
	QCursor getCursor() const;

	void setSize(const  QSize & size);
	QSize getSize() const;

	void setList(const  QList<QVariant> & list);
	QList<QVariant> getList() const;

	void setPolygon(const  QPolygon & polygon);
	QPolygon getPolygon() const;

	void setColor(const  QColor & color);
	QColor getColor() const;

	void setSizeF(const  QSizeF & sizef);
	QSizeF getSizeF() const;

	void setQRectF(const  QRectF & rectf);
	QRectF getQRectF() const;

	void setQLine(const  QLine & line);
	QLine getQLine() const;

	void setQStringList(const  QStringList & stringList);
	QStringList getQStringList() const;

	void setQVariantMap(const  QVariantMap & variantMap);
    QVariantMap getQVariantMap() const;

	void setQVariantHash(const  QVariantHash & variantHash);
	QVariantHash getQVariantHash() const;

	void setQIcon(const  QIcon & icon);
	QIcon getQIcon() const;

	void setQLineF(const  QLineF & linef);
	QLineF getQLineF() const;

	void setQRect(const  QRect & rect);
	QRect getQRect() const;

	void setQPoint(const  QPoint & point);
	QPoint getQPoint() const;

	void setQRegExp(const  QRegExp & qRegex);
	QRegExp getQRegExp() const;

	void setQPointf(const  QPointF & pointf);
	QPointF getQPointf() const;

	void setQPalette(const  QPalette & palette);
	QPalette getQPalette() const;

	void setQFont(const  QFont & font);
	QFont getQFont() const;

	void setQBrush(const  QBrush & brush);
	QBrush getQBrush() const;

	void setQImage(const  QImage & image);
	QImage getQImage() const;
	
	void setQSizePolicy(const  QSizePolicy & sizepolicy);
	QSizePolicy getQSizePolicy() const;

	void setQMatrix(const  QMatrix & matrix);
	QMatrix getQMatrix() const;

	void setQTransform(const  QTransform & transform);
	QTransform getQTransform() const;

	void setQMatrix4x4(const  QMatrix4x4 & matrix4x4);
	QMatrix4x4 getQMatrix4x4() const;

	void setQVector2D(const  QVector2D & vector2D);
	QVector2D getQVector2D() const;

	void setQVector3D(const  QVector3D & vector3D);
	QVector3D getQVector3D() const;

	void setQVector4D(const  QVector4D & vector4D);
	QVector4D getQVector4D() const;

	void reset();

private:
    QString name;
	QDate date;
	QDateTime dateTime;
	QByteArray byteArray;
	QUrl url;
	bool boolv;
	QChar qchar;
	char ochar;
	QObject* qobject;
	QWidget* qwidget;
	QCursor cursor;
	QSize size;
	QList<QVariant> list;
	QPolygon polygon;
	QColor color;
	QSizeF sizef;
	QRectF rectf;
	QLine line;
	QTextLength textLength;
	QStringList stringList;
	QVariantMap variantMap;
	QVariantHash variantHash;
	QIcon icon;
	QLineF linef;
	QRect rect;
	QPoint point;
	QRegExp qRegex;
	QPointF pointf;
	QPalette palette;
	QFont font;
	QBrush brush;
	QImage image;
	QSizePolicy sizepolicy;
	QMatrix matrix;
	QTransform transform;
	QMatrix4x4 matrix4x4;
	QVector2D vector2D;
	QVector3D vector3D;
	QVector4D vector4D;
	uint uintb;
};
Q_DECLARE_METATYPE(QTreeView*)
Q_DECLARE_METATYPE(TestObject*)


#endif // TESTOBJECT_H
