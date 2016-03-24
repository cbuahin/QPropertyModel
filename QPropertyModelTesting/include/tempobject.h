#ifndef TEMPOBJECT_H
#define TEMPOBJECT_H

#include <QObject>
#include <QTime>
#include <QUrl>
#include <QIcon>
#include <QTextLength>
#include <QMap>
#include <QMatrix4x4>
#include <QVector2D>
#include <QBitmap>
#include <QGraphicsView>
#include <QGraphicsItemAnimation>
#include <QTreeView>
#include "qobjectpropertyitem.h"
#include "qobjectlistpropertyitem.h"

class TempObject : public QObject
{
      Q_OBJECT
      Q_ENUMS(TestEnum)
      Q_FLAGS(TestEnums)
      Q_PROPERTY(QString QtString READ getName WRITE setName RESET reset)
      Q_PROPERTY(QTime QtTime READ getTime WRITE setTime RESET reset)
      Q_PROPERTY(QDate QtDate READ getDate WRITE setDate RESET reset)
      Q_PROPERTY(QDateTime QtDateTime READ getDateTime WRITE setDateTime RESET reset)
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
      Q_PROPERTY(QSizeF  QtSizeF READ getSizeF WRITE setSizeF)
      Q_PROPERTY(QList<QObject*>  QtList READ getList)
      Q_PROPERTY(QPolygon  QtPolygon READ getPolygon  WRITE setPolygon)
      Q_PROPERTY(QColor  QtColor READ getColor WRITE setColor)
      Q_PROPERTY(QRect  QtRect READ getQRect WRITE setQRect)
      Q_PROPERTY(QRectF  QtRectF READ getQRectF WRITE setQRectF)
      Q_PROPERTY(QStringList  QtStringList READ getQStringList)
      Q_PROPERTY(QVariantList QtVariantList READ getQVariantList WRITE setQVariantList)
      Q_PROPERTY(QVariantMap  QtVariantMap READ getQVariantMap WRITE setQVariantMap)
      Q_PROPERTY(QVariantHash  QtVariantHash READ getQVariantHash WRITE setQVariantHash)
      Q_PROPERTY(QIcon  QtQIcon READ getQIcon WRITE setQIcon)
      Q_PROPERTY(QLine  QtLine READ getQLine WRITE setQLine)
      Q_PROPERTY(QLineF  QtLineF READ getQLineF WRITE setQLineF)
      Q_PROPERTY(QPoint  QtPoint READ getQPoint WRITE setQPoint)
      Q_PROPERTY(QRegExp  QtRegExp READ getQRegExp WRITE setQRegExp)
      Q_PROPERTY(QPointF  QtPointF READ getQPointf WRITE setQPointf)
      Q_PROPERTY(QPalette  QtPalette READ getQPalette WRITE setQPalette)
      Q_PROPERTY(QPen  QtPen READ getQPen WRITE setQPen)
      Q_PROPERTY(QFont  QtFont READ getQFont WRITE setQFont)
      Q_PROPERTY(QBrush  QtBrush READ getQBrush WRITE setQBrush)
      Q_PROPERTY(QSizePolicy  QtSizePolicy READ getQSizePolicy WRITE setQSizePolicy)
      Q_PROPERTY(QMatrix  QtMatrix READ getQMatrix WRITE setQMatrix)
      Q_PROPERTY(QTransform  QtTransform READ getQTransform WRITE setQTransform)
      Q_PROPERTY(QMatrix4x4  QtMatrix4x4 READ getQMatrix4x4 WRITE setQMatrix4x4)
      Q_PROPERTY(QVector2D  QtVector2D READ getQVector2D WRITE setQVector2D)
      Q_PROPERTY(QVector3D  QtVector3D READ getQVector3D WRITE setQVector3D)
      Q_PROPERTY(QVector4D  QtVector4D READ getQVector4D WRITE setQVector4D)
      Q_PROPERTY(QKeySequence  QtKeySequence READ getKeySequence WRITE setKeySequence)
      Q_PROPERTY(TestEnum  QtTestEnum READ getTestEnum WRITE setTestEnum)
      Q_PROPERTY(TestEnums  QtTestEnumFlags READ getTestEnumFlags WRITE setTestEnumFlags)
      Q_PROPERTY(QPixmap  QtPixmap READ getQPixmap WRITE setQPixmap)
      Q_PROPERTY(QImage  QtImage READ getQImage WRITE setQImage)
      Q_PROPERTY(QBitmap  QtBitmap READ getQBitmap WRITE setQBitmap)
      Q_PROPERTY(QBrush  QtBrushTest READ getQBrushTest WRITE setQBrushTest)
      Q_PROPERTY(QList<QGraphicsScene*> TempObjects READ tempObjectList)

   public:
      enum TestEnum
      {
         TestA = 1,
         TestB = 2,
         TestC = 4,
         TestD = 8,
         TestE = 16,
         TestF = 32,
      };

      Q_DECLARE_FLAGS(TestEnums, TestEnum)

      TempObject(QObject *parent);
      ~TempObject();


      void setName(const  QString & name);
      QString getName() const;

      void setTime(const QTime& time);
      QTime getTime() const;

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

      QList<QObject*> getList() const;
      void setList(const QList<QObject*>& values);

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

      void setQVariantList(const  QVariantList & variantList);
      QVariantList getQVariantList() const;

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

      void setQBrushTest(const  QBrush & brushtest);
      QBrush getQBrushTest() const;

      void setQPen(const  QPen & pen);
      QPen getQPen() const;

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

      void setTestEnum(TestEnum testEnum);
      TestEnum getTestEnum() const;

      void setTestEnumFlags(TestEnums flags);
      TestEnums getTestEnumFlags() const;

      void setKeySequence(const QKeySequence& sequence);
      QKeySequence getKeySequence() const;

      void setQPixmap(const QPixmap& pixmap);
      QPixmap getQPixmap() const;

      void setQImage(const  QImage & image);
      QImage getQImage() const;

      void setQBitmap(const QBitmap& bitmap);
      QBitmap getQBitmap() const;

      QList<QGraphicsScene*> tempObjectList() const;

      void reset();

   private:
      QTime time;
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
      QList<QObject*> list;
      QPolygon polygon;
      QColor color;
      QSizeF sizef;
      QRectF rectf;
      QLine line;
      QLineF linef;
      QTextLength textLength;
      QStringList stringList;
      QVariantMap variantMap;
      QVariantHash variantHash;
      QIcon icon;
      QRect rect;
      QPoint point;
      QRegExp qRegex;
      QPointF pointf;
      QPalette palette;
      QFont font;
      QBrush brush, brushtest;
      QImage image;
      QSizePolicy sizepolicy;
      QMatrix matrix;
      QTransform transform;
      QMatrix4x4 matrix4x4;
      QVector2D vector2D;
      QVector3D vector3D;
      QVector4D vector4D;
      uint uintb;
      TestEnum testEnum;
      QKeySequence sequence;
      QLine qline;
      QLineF qlinef;
      QPixmap pixmap;
      QBitmap bitmap;
      TestEnums flags;
      QPen pen;
      QVariantList variantList;
      QList<QGraphicsScene*> tempObjects;
};

template<typename T>
QList<QObject*> convertToQObjectList(const QVariant& values);

class TempObjectPropertyItem : public QObjectPropertyItem
{
      Q_OBJECT
   public:
      Q_INVOKABLE TempObjectPropertyItem(const QVariant& value , const QMetaProperty& prop, QPropertyItem * parent);
};

class TempObjectListPropertyItem : public QObjectListPropertyItem
{
      Q_OBJECT
   public:
      Q_INVOKABLE TempObjectListPropertyItem(const QVariant& value , const QMetaProperty& prop, QObjectClassPropertyItem * parent);
};


Q_DECLARE_METATYPE(QList<QGraphicsScene*>)
Q_DECLARE_METATYPE(TempObject*)

#endif // TEMPOBJECT_H
