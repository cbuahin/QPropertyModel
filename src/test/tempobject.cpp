#include "stdafx.h"
#include "tempobject.h"

TempObject::TempObject(QObject *parent)
   : QObject(parent), date(QDate::currentDate()), dateTime(QDateTime::currentDateTime()), name("Test")
{

   qobject = new QGraphicsItemAnimation(this);
   color = Qt::red;
   qwidget = new QTreeView();
   testEnum = TestEnum::TestA;



   flags = flags | TestEnum::TestA | TestEnum::TestC;

   stringList << "TestA" << "TestB" << "TestC" << "TestD" << "TestE" << "TestF" << "TestG" << "TestH";
   variantMap["One"] = QVariant::fromValue(qwidget);
   variantMap["Two"] = "Knock the Door";
   variantMap["Three"] = "Buckle My Shoe";

   variantHash["One"] = QVariant::fromValue(qwidget);
   variantHash["Two"] = QVariant::fromValue(this);
   variantHash["Three"] = QString("Buckle My Shoe");

   variantList << QFont() <<  QFont() ;

   for (int i = 0; i < 10; i++)
   {
      list.append(new QWidget());
      tempObjects.append(new QGraphicsScene(this));
   }
}

TempObject::~TempObject()
{
   qDeleteAll(list);
   list.clear();

//   qDeleteAll(tempObjects);
//   tempObjects.clear();

   delete qobject;
   delete qwidget;
}

void TempObject::setName(const QString &name)
{
   this->name = name;
}

QString TempObject::getName() const
{
   return name;
}

void TempObject::setDate(const QDate& date)
{
   this->date = date;
}

QDate TempObject::getDate() const
{
   return date;
}

void TempObject::setTime(const QTime& time)
{
   this->time = time;
}

QTime TempObject::getTime() const
{
   return time;
}

void TempObject::setDateTime(const QDateTime& dateTime)
{
   this->dateTime = dateTime;
}

QDateTime TempObject::getDateTime() const
{
   return this->dateTime;
}


void TempObject::setByteArray(const QByteArray& byteArray)
{
   this->byteArray = byteArray;
}

QByteArray TempObject::getByteArray() const
{
   return this->byteArray;
}

void TempObject::setUrl(const QUrl& url)
{
   this->url = url;
}

QUrl TempObject::getUrl() const
{
   return this->url;
}

void TempObject::setUint(const uint &uint)
{
   this->uintb = uint;
}

uint TempObject::getUint() const
{
   return uintb;
}

void TempObject::setBool(const bool &boolv)
{
   this->boolv = boolv;
}

bool TempObject::getBool() const
{
   return boolv;
}

void TempObject::setQChar(const QChar &qchar)
{
   this->qchar = qchar;
}

QChar TempObject::getQChar() const
{
   return qchar;
}

void TempObject::setChar(const char &ochar)
{
   this->ochar = ochar;
}

char TempObject::getChar() const
{
   return ochar;
}

void TempObject::setQObject(QObject * const &qobject)
{
   this->qobject = qobject;
}

QObject *TempObject::getQObject() const
{
   return qobject;
}

void TempObject::setQWidget(QWidget * const &qwidget)
{
   this->qwidget = qwidget;
}

QWidget *TempObject::getQWidget() const
{
   return qwidget;
}

void TempObject::setCursor(const QCursor &cursor)
{
   this->cursor = cursor;
}

QCursor TempObject::getCursor() const
{
   return cursor;
}

void TempObject::setSize(const QSize &size)
{
   this->size = size;
}

QSize TempObject::getSize() const
{
   return size;
}


QList<QObject*> TempObject::getList() const
{
   return list;
}

void TempObject::setList(const QList<QObject *> &values)
{

}

void TempObject::setPolygon(const QPolygon &polygon)
{
   this->polygon = polygon;
}

QPolygon TempObject::getPolygon() const
{
   return polygon;
}

void TempObject::setColor(const QColor &color)
{
   this->color = color;
}

QColor TempObject::getColor() const
{
   return color;
}

void TempObject::setSizeF(const QSizeF &sizef)
{
   this->sizef = sizef;
}

QSizeF TempObject::getSizeF() const
{
   return sizef;
}

void TempObject::setQRectF(const QRectF &rectf)
{
   this->rectf = rectf;
}

QRectF TempObject::getQRectF() const
{
   return rectf;
}

void TempObject::setQLine(const QLine &line)
{
   this->line = line;
}

QLine TempObject::getQLine() const
{
   return line;
}

void TempObject::setQStringList(const QStringList &stringList)
{
   this->stringList = stringList;
}

QStringList TempObject::getQStringList() const
{
   return stringList;
}

void TempObject::setQVariantList(const  QVariantList & variantList)
{
   this->variantList = variantList;
}
QVariantList TempObject::getQVariantList() const
{
   return variantList;
}
void TempObject::setQVariantMap(const QVariantMap &variantMap)
{
   this->variantMap = variantMap;
}

QVariantMap TempObject::getQVariantMap() const
{
   return variantMap;
}

void TempObject::setQVariantHash(const QVariantHash &variantHash)
{
   this->variantHash = variantHash;
}

QVariantHash TempObject::getQVariantHash() const
{
   return variantHash;
}

void TempObject::setQIcon(const QIcon &icon)
{
   this->icon = icon;
}

QIcon TempObject::getQIcon() const
{
   return icon;
}

void TempObject::setQLineF(const QLineF &linef)
{
   this->linef = linef;
}

QLineF TempObject::getQLineF() const
{
   return linef;
}

void TempObject::setQRect(const  QRect & rect)
{
   this->rect = rect;
}
QRect TempObject::getQRect() const
{
   return rect;
}

void TempObject::setQPoint(const  QPoint & point)
{
   this->point = point;
}
QPoint TempObject::getQPoint() const
{
   return point;
}

void TempObject::setQRegExp(const  QRegExp & qRegex)
{
   this->qRegex = qRegex;
}
QRegExp TempObject::getQRegExp() const
{
   return qRegex;
}

void TempObject::setQPointf(const  QPointF & pointf)
{
   this->pointf = pointf;
}
QPointF TempObject::getQPointf() const
{
   return pointf;
}

void TempObject::setQPalette(const  QPalette & palette)
{
   this->palette = palette;
}
QPalette TempObject::getQPalette() const
{
   return palette;
}

void TempObject::setQFont(const  QFont & font)
{
   this->font = font;
}
QFont TempObject::getQFont() const
{
   return font;
}

void TempObject::setQBrush(const  QBrush & brush)
{
   this->brush = brush;
}

QBrush TempObject::getQBrush() const
{
   return brush;
}

void TempObject::setQBrushTest(const  QBrush & brushtest)
{
   this->brushtest = brushtest;
}

QBrush TempObject::getQBrushTest() const
{
   return this->brushtest;
}


void TempObject::setQPen(const  QPen & pen)
{
   this->pen = pen;
}

QPen TempObject::getQPen() const
{
   return this->pen;
}


void TempObject::setQSizePolicy(const  QSizePolicy & sizepolicy)
{
   this->sizepolicy = sizepolicy;
}

QSizePolicy TempObject::getQSizePolicy() const
{
   return sizepolicy;
}

void TempObject::setQMatrix(const  QMatrix & matrix)
{
   this->matrix = matrix;
}

QMatrix TempObject::getQMatrix() const
{
   return this->matrix;
}

void TempObject::setQTransform(const  QTransform & transform)
{
   this->transform = transform;
}

QTransform TempObject::getQTransform() const
{
   return transform;
}

void TempObject::setQMatrix4x4(const  QMatrix4x4 & matrix4x4)
{
   this->matrix4x4 = matrix4x4;
}

QMatrix4x4 TempObject::getQMatrix4x4() const
{
   return matrix4x4;
}

void TempObject::setQVector2D(const  QVector2D & vector2D)
{
   this->vector2D = vector2D;
}

QVector2D TempObject::getQVector2D() const
{
   return vector2D;
}

void TempObject::setQVector3D(const  QVector3D & vector3D)
{
   this->vector3D = vector3D;
}

QVector3D TempObject::getQVector3D() const
{
   return vector3D;
}

void TempObject::setQVector4D(const  QVector4D & vector4D)
{
   this->vector4D = vector4D;
}

QVector4D TempObject::getQVector4D() const
{
   return vector4D;
}

void TempObject::setTestEnum(TestEnum testEnum)
{
   this->testEnum = testEnum;
}

TempObject::TestEnum TempObject::getTestEnum() const
{
   return testEnum;
}

void TempObject::setTestEnumFlags(TestEnums flags)
{
   this->flags = flags;
}

TempObject::TestEnums TempObject::getTestEnumFlags() const
{
   return this->flags;
}

void TempObject::setKeySequence(const QKeySequence& sequence)
{
   this->sequence = sequence;
}

QKeySequence TempObject::getKeySequence() const
{
   return sequence;
}

void TempObject::setQPixmap(const QPixmap& pixmap)
{
   this->pixmap = pixmap;
}

QPixmap TempObject::getQPixmap() const
{
   return pixmap;
}

void TempObject::setQImage(const QImage& image)
{
   this->image = image;
}

QImage TempObject::getQImage() const
{
   return image;
}

void TempObject::setQBitmap(const QBitmap& bitmap)
{
   this->bitmap = bitmap;
}

QBitmap TempObject::getQBitmap() const
{
   return bitmap;
}

QList<QGraphicsScene*> TempObject::tempObjectList() const
{
   return tempObjects;
}


void TempObject::reset()
{
   name = "resetName";
   date = QDate::currentDate();
   dateTime = QDateTime::currentDateTime();
   url = QUrl("http://www.gthsansa.com");
   boolv = false;
}

template<typename T>
QList<QObject*> convertToQObjectList(const QVariant& value)
{
   QList<T> values = qvariant_cast< QList<T> >(value);

   QList<QObject*> retValues;

   for(int i = 0 ; i < values.length() ; i++)
   {
      QObject* tmv = dynamic_cast<QObject*>(values[i]);
      retValues.append(tmv);
   }

   return retValues;
}


TempObjectPropertyItem::TempObjectPropertyItem(const QVariant& value , const QMetaProperty& prop, QPropertyItem * parent)
   : QObjectPropertyItem( dynamic_cast<QObject*>(qvariant_cast<TempObject*>(value)) , prop , parent)
{

}

TempObjectListPropertyItem::TempObjectListPropertyItem(const QVariant& value , const QMetaProperty& prop, QObjectClassPropertyItem * parent)
   : QObjectListPropertyItem
     (
        QVariant::fromValue( convertToQObjectList<QGraphicsScene*>(value)), prop , parent
     )
{
     setQVariantToQObjectListConverter( & convertToQObjectList<QGraphicsScene*>);
}
