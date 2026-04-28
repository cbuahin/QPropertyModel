/*!
 * \file tempobject.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * TempObject — a comprehensive QObject for manual UI testing of QPropertyModel.
 * Exposes every built-in Qt property type recognised by the model, plus a
 * custom enum/flags pair, nested QObject* pointers, and list properties.
 * Also declares TempObjectPropertyItem and TempObjectListPropertyItem as
 * custom QPropertyItem subclasses that can be registered with QPropertyModel.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */

#ifndef TEMPOBJECT_H
#define TEMPOBJECT_H

#include <QObject>
#include <QDate>
#include <QDateTime>
#include <QTime>
#include <QUrl>
#include <QColor>
#include <QFont>
#include <QBrush>
#include <QPen>
#include <QPalette>
#include <QSizePolicy>
#include <QTransform>
#include <QMatrix4x4>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QSize>
#include <QSizeF>
#include <QRect>
#include <QRectF>
#include <QLine>
#include <QLineF>
#include <QPoint>
#include <QPointF>
#include <QPolygon>
#include <QKeySequence>
#include <QPixmap>
#include <QImage>
#include <QBitmap>
#include <QIcon>
#include <QCursor>
#include <QByteArray>
#include <QStringList>
#include <QVariantList>
#include <QVariantMap>
#include <QVariantHash>
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsItemAnimation>
#include <QTreeView>
#include <QWidget>

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#  include <QMatrix>
#  include <QRegExp>
#endif

#include "qobjectpropertyitem.h"
#include "qobjectclasspropertyitem.h"
#include "qobjectlistpropertyitem.h"

// ──────────────────────────────────────────────────────────────────────────────
// TempObject
// ──────────────────────────────────────────────────────────────────────────────

/*!
 * \brief Test QObject that exposes every property type supported by QPropertyModel.
 *
 * Register TempObjectPropertyItem for \c TempObject* and
 * TempObjectListPropertyItem for \c QList<QGraphicsScene*> to exercise all
 * code paths of the custom-type registration API.
 */
class TempObject : public QObject
{
   Q_OBJECT

public:
   enum TestEnum { TestA = 1, TestB = 2, TestC = 4, TestD = 8 };
   Q_ENUM(TestEnum)

   Q_DECLARE_FLAGS(TestEnums, TestEnum)
   Q_FLAG(TestEnums)

   // ── Basic scalar properties ──────────────────────────────────────────────
   Q_PROPERTY(QString      name         READ getName         WRITE setName)
   Q_PROPERTY(bool         boolProp     READ getBool         WRITE setBool)
   Q_PROPERTY(uint         uintProp     READ getUint         WRITE setUint)
   Q_PROPERTY(char         charProp     READ getChar         WRITE setChar)
   Q_PROPERTY(QChar        qcharProp    READ getQChar        WRITE setQChar)

   // ── Date / time properties ───────────────────────────────────────────────
   Q_PROPERTY(QDate     date      READ getDate      WRITE setDate)
   Q_PROPERTY(QTime     time      READ getTime      WRITE setTime)
   Q_PROPERTY(QDateTime dateTime  READ getDateTime  WRITE setDateTime)
   Q_PROPERTY(QUrl      url       READ getUrl       WRITE setUrl)

   // ── Appearance properties ────────────────────────────────────────────────
   Q_PROPERTY(QColor       color        READ getColor        WRITE setColor)
   Q_PROPERTY(QFont        font         READ getQFont        WRITE setQFont)
   Q_PROPERTY(QBrush       brush        READ getQBrush       WRITE setQBrush)
   Q_PROPERTY(QBrush       brushTest    READ getQBrushTest   WRITE setQBrushTest)
   Q_PROPERTY(QPen         pen          READ getQPen         WRITE setQPen)
   Q_PROPERTY(QPalette     palette      READ getQPalette     WRITE setQPalette)
   Q_PROPERTY(QCursor      cursor       READ getCursor       WRITE setCursor)
   Q_PROPERTY(QIcon        icon         READ getQIcon        WRITE setQIcon)

   // ── Geometry properties ──────────────────────────────────────────────────
   Q_PROPERTY(QSize     size     READ getSize     WRITE setSize)
   Q_PROPERTY(QSizeF    sizeF    READ getSizeF    WRITE setSizeF)
   Q_PROPERTY(QRect     rect     READ getQRect    WRITE setQRect)
   Q_PROPERTY(QRectF    rectF    READ getQRectF   WRITE setQRectF)
   Q_PROPERTY(QLine     line     READ getQLine    WRITE setQLine)
   Q_PROPERTY(QLineF    lineF    READ getQLineF   WRITE setQLineF)
   Q_PROPERTY(QPoint    point    READ getQPoint   WRITE setQPoint)
   Q_PROPERTY(QPointF   pointF   READ getQPointf  WRITE setQPointf)
   Q_PROPERTY(QPolygon  polygon  READ getPolygon  WRITE setPolygon)
   Q_PROPERTY(QSizePolicy sizePolicy READ getQSizePolicy WRITE setQSizePolicy)

   // ── Transform / matrix properties ────────────────────────────────────────
   Q_PROPERTY(QTransform  transform  READ getQTransform  WRITE setQTransform)
   Q_PROPERTY(QMatrix4x4  matrix4x4  READ getQMatrix4x4  WRITE setQMatrix4x4)
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
   Q_PROPERTY(QMatrix     matrix     READ getQMatrix     WRITE setQMatrix)
#endif

   // ── Vector properties ─────────────────────────────────────────────────────
   Q_PROPERTY(QVector2D vector2D READ getQVector2D WRITE setQVector2D)
   Q_PROPERTY(QVector3D vector3D READ getQVector3D WRITE setQVector3D)
   Q_PROPERTY(QVector4D vector4D READ getQVector4D WRITE setQVector4D)

   // ── Image / graphic properties ────────────────────────────────────────────
   Q_PROPERTY(QPixmap pixmap READ getQPixmap WRITE setQPixmap)
   Q_PROPERTY(QImage  image  READ getQImage  WRITE setQImage)
   Q_PROPERTY(QBitmap bitmap READ getQBitmap WRITE setQBitmap)

   // ── String / byte array properties ───────────────────────────────────────
   Q_PROPERTY(QStringList  stringList  READ getQStringList  WRITE setQStringList)
   Q_PROPERTY(QByteArray   byteArray   READ getByteArray    WRITE setByteArray)
   Q_PROPERTY(QKeySequence keySequence READ getKeySequence  WRITE setKeySequence)
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
   Q_PROPERTY(QRegExp regExp READ getQRegExp WRITE setQRegExp)
#endif

   // ── Variant collection properties ────────────────────────────────────────
   Q_PROPERTY(QVariantList variantList READ getQVariantList WRITE setQVariantList)
   Q_PROPERTY(QVariantMap  variantMap  READ getQVariantMap  WRITE setQVariantMap)
   Q_PROPERTY(QVariantHash variantHash READ getQVariantHash WRITE setQVariantHash)

   // ── QObject pointer properties ────────────────────────────────────────────
   Q_PROPERTY(QObject* qobject READ getQObject WRITE setQObject)
   Q_PROPERTY(QWidget* qwidget READ getQWidget WRITE setQWidget)

   // ── List properties ───────────────────────────────────────────────────────
   Q_PROPERTY(QList<QObject*>        list        READ getList        WRITE setList)
   Q_PROPERTY(QList<QGraphicsScene*> tempObjects READ tempObjectList)

   // ── Enum / flags properties ───────────────────────────────────────────────
   Q_PROPERTY(TestEnum  testEnum  READ getTestEnum      WRITE setTestEnum)
   Q_PROPERTY(TestEnums flags     READ getTestEnumFlags WRITE setTestEnumFlags)

public:
   explicit TempObject(QObject* parent = nullptr);
   ~TempObject();

   // ── Accessors ────────────────────────────────────────────────────────────
   void    setName(const QString& name);
   QString getName() const;

   void  setBool(const bool& boolv);
   bool  getBool() const;

   void setUint(const uint& u);
   uint getUint() const;

   void  setChar(const char& c);
   char  getChar() const;

   void  setQChar(const QChar& qchar);
   QChar getQChar() const;

   void setDate(const QDate& date);
   QDate getDate() const;

   void  setTime(const QTime& time);
   QTime getTime() const;

   void      setDateTime(const QDateTime& dt);
   QDateTime getDateTime() const;

   void setUrl(const QUrl& url);
   QUrl getUrl() const;

   void   setColor(const QColor& color);
   QColor getColor() const;

   void  setQFont(const QFont& font);
   QFont getQFont() const;

   void   setQBrush(const QBrush& brush);
   QBrush getQBrush() const;

   void   setQBrushTest(const QBrush& brush);
   QBrush getQBrushTest() const;

   void setQPen(const QPen& pen);
   QPen  getQPen() const;

   void     setQPalette(const QPalette& palette);
   QPalette getQPalette() const;

   void    setCursor(const QCursor& cursor);
   QCursor getCursor() const;

   void  setQIcon(const QIcon& icon);
   QIcon getQIcon() const;

   void  setSize(const QSize& size);
   QSize getSize() const;

   void   setSizeF(const QSizeF& sizef);
   QSizeF getSizeF() const;

   void  setQRect(const QRect& rect);
   QRect getQRect() const;

   void   setQRectF(const QRectF& rectf);
   QRectF getQRectF() const;

   void  setQLine(const QLine& line);
   QLine getQLine() const;

   void   setQLineF(const QLineF& linef);
   QLineF getQLineF() const;

   void   setQPoint(const QPoint& point);
   QPoint getQPoint() const;

   void    setQPointf(const QPointF& pointf);
   QPointF getQPointf() const;

   void     setPolygon(const QPolygon& polygon);
   QPolygon getPolygon() const;

   void        setQSizePolicy(const QSizePolicy& sp);
   QSizePolicy getQSizePolicy() const;

   void       setQTransform(const QTransform& t);
   QTransform getQTransform() const;

   void      setQMatrix4x4(const QMatrix4x4& m);
   QMatrix4x4 getQMatrix4x4() const;

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
   void    setQMatrix(const QMatrix& m);
   QMatrix getQMatrix() const;
#endif

   void      setQVector2D(const QVector2D& v);
   QVector2D getQVector2D() const;

   void      setQVector3D(const QVector3D& v);
   QVector3D getQVector3D() const;

   void      setQVector4D(const QVector4D& v);
   QVector4D getQVector4D() const;

   void    setQPixmap(const QPixmap& pixmap);
   QPixmap getQPixmap() const;

   void   setQImage(const QImage& image);
   QImage getQImage() const;

   void    setQBitmap(const QBitmap& bitmap);
   QBitmap getQBitmap() const;

   void        setQStringList(const QStringList& sl);
   QStringList getQStringList() const;

   void       setByteArray(const QByteArray& ba);
   QByteArray getByteArray() const;

   void         setKeySequence(const QKeySequence& ks);
   QKeySequence getKeySequence() const;

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
   void    setQRegExp(const QRegExp& re);
   QRegExp getQRegExp() const;
#endif

   void         setQVariantList(const QVariantList& vl);
   QVariantList getQVariantList() const;

   void        setQVariantMap(const QVariantMap& vm);
   QVariantMap getQVariantMap() const;

   void         setQVariantHash(const QVariantHash& vh);
   QVariantHash getQVariantHash() const;

   void     setQObject(QObject* const& obj);
   QObject* getQObject() const;

   void     setQWidget(QWidget* const& w);
   QWidget* getQWidget() const;

   void                setList(const QList<QObject*>& values);
   QList<QObject*>     getList() const;

   QList<QGraphicsScene*> tempObjectList() const;

   void      setTestEnum(TestEnum e);
   TestEnum  getTestEnum() const;

   void       setTestEnumFlags(TestEnums f);
   TestEnums  getTestEnumFlags() const;

public slots:
   void reset();

private:
   QString    name;
   bool       boolv       { false };
   uint       uintb       { 0 };
   char       ochar       { '\0' };
   QChar      qchar;

   QDate     date;
   QTime     time;
   QDateTime dateTime;
   QUrl      url;

   QColor       color;
   QFont        font;
   QBrush       brush;
   QBrush       brushtest;
   QPen         pen;
   QPalette     palette;
   QCursor      cursor;
   QIcon        icon;

   QSize        size;
   QSizeF       sizef;
   QRect        rect;
   QRectF       rectf;
   QLine        line;
   QLineF       linef;
   QPoint       point;
   QPointF      pointf;
   QPolygon     polygon;
   QSizePolicy  sizepolicy;

   QTransform   transform;
   QMatrix4x4   matrix4x4;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
   QMatrix      matrix;
#endif

   QVector2D    vector2D;
   QVector3D    vector3D;
   QVector4D    vector4D;

   QPixmap      pixmap;
   QImage       image;
   QBitmap      bitmap;

   QStringList  stringList;
   QByteArray   byteArray;
   QKeySequence sequence;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
   QRegExp      qRegex;
#endif

   QVariantList variantList;
   QVariantMap  variantMap;
   QVariantHash variantHash;

   QObject*                qobject   { nullptr };
   QWidget*                qwidget   { nullptr };
   QList<QObject*>         list;
   QList<QGraphicsScene*>  tempObjects;

   TestEnum   testEnum;
   TestEnums  flags;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(TempObject::TestEnums)
Q_DECLARE_METATYPE(TempObject*)

// ──────────────────────────────────────────────────────────────────────────────
// TempObjectPropertyItem
// Custom QPropertyItem for TempObject* nested properties.
// ──────────────────────────────────────────────────────────────────────────────

/*!
 * \brief Custom property item for \c TempObject* properties inside another object.
 *
 * Inherits QObjectPropertyItem so that a TempObject* valued property of a
 * parent object is listed and expandable in the tree.
 */
class TempObjectPropertyItem : public QObjectPropertyItem
{
   Q_OBJECT

public:
   Q_INVOKABLE TempObjectPropertyItem(const QVariant& value,
                                      const QMetaProperty& prop,
                                      QPropertyItem* parent);
};

// ──────────────────────────────────────────────────────────────────────────────
// TempObjectListPropertyItem
// Custom QPropertyItem for QList<QGraphicsScene*> properties.
// ──────────────────────────────────────────────────────────────────────────────

/*!
 * \brief Custom property item for \c QList<QGraphicsScene*> properties.
 *
 * Inherits QObjectListPropertyItem and installs a converter that casts
 * each \c QGraphicsScene* to \c QObject* for generic list display.
 */
class TempObjectListPropertyItem : public QObjectListPropertyItem
{
   Q_OBJECT

public:
   Q_INVOKABLE TempObjectListPropertyItem(const QVariant& value,
                                          const QMetaProperty& prop,
                                          QObjectClassPropertyItem* parent);
};

#endif // TEMPOBJECT_H
