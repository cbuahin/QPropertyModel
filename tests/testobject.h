/*!
 * \file testobject.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Test QObject covering all built-in property types.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */

#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <QObject>
#include <QColor>
#include <QFont>
#include <QPoint>
#include <QPointF>
#include <QSize>
#include <QSizeF>
#include <QRect>
#include <QRectF>
#include <QLine>
#include <QLineF>
#include <QBrush>
#include <QPen>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QStringList>
#include <QVariantList>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QUrl>

/*!
 * \brief A QObject that exposes all supported property types for unit testing.
 */
class TestObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString     stringProp   READ stringProp   WRITE setStringProp)
    Q_PROPERTY(int         intProp      READ intProp      WRITE setIntProp)
    Q_PROPERTY(double      doubleProp   READ doubleProp   WRITE setDoubleProp)
    Q_PROPERTY(bool        boolProp     READ boolProp     WRITE setBoolProp)
    Q_PROPERTY(QColor      colorProp    READ colorProp    WRITE setColorProp)
    Q_PROPERTY(QFont       fontProp     READ fontProp     WRITE setFontProp)
    Q_PROPERTY(QPoint      pointProp    READ pointProp    WRITE setPointProp)
    Q_PROPERTY(QPointF     pointfProp   READ pointfProp   WRITE setPointfProp)
    Q_PROPERTY(QSize       sizeProp     READ sizeProp     WRITE setSizeProp)
    Q_PROPERTY(QSizeF      sizefProp    READ sizefProp    WRITE setSizefProp)
    Q_PROPERTY(QRect       rectProp     READ rectProp     WRITE setRectProp)
    Q_PROPERTY(QRectF      rectfProp    READ rectfProp    WRITE setRectfProp)
    Q_PROPERTY(QLine       lineProp     READ lineProp     WRITE setLineProp)
    Q_PROPERTY(QLineF      linefProp    READ linefProp    WRITE setLinefProp)
    Q_PROPERTY(QBrush      brushProp    READ brushProp    WRITE setBrushProp)
    Q_PROPERTY(QPen        penProp      READ penProp      WRITE setPenProp)
    Q_PROPERTY(QVector2D   vec2Prop     READ vec2Prop     WRITE setVec2Prop)
    Q_PROPERTY(QVector3D   vec3Prop     READ vec3Prop     WRITE setVec3Prop)
    Q_PROPERTY(QVector4D   vec4Prop     READ vec4Prop     WRITE setVec4Prop)
    Q_PROPERTY(QStringList stringListProp READ stringListProp WRITE setStringListProp)
    Q_PROPERTY(QDate       dateProp     READ dateProp     WRITE setDateProp)
    Q_PROPERTY(QTime       timeProp     READ timeProp     WRITE setTimeProp)
    Q_PROPERTY(QDateTime   dateTimeProp READ dateTimeProp WRITE setDateTimeProp)
    Q_PROPERTY(QUrl        urlProp      READ urlProp      WRITE setUrlProp)
    // Enum property — tests QEnumPropertyItem
    Q_PROPERTY(Qt::PenStyle  penStyleProp  READ penStyleProp  WRITE setPenStyleProp)
    // Read-only property — no WRITE, tests ItemIsEditable suppression
    Q_PROPERTY(QString       readOnlyProp  READ readOnlyProp)
    // Resettable property — tests canReset() / resetData()
    Q_PROPERTY(int resettableProp READ resettableProp WRITE setResettableProp RESET resetResettableProp)

public:
    explicit TestObject(QObject *parent = nullptr);

    QString     stringProp()   const { return m_string; }
    int         intProp()      const { return m_int; }
    double      doubleProp()   const { return m_double; }
    bool        boolProp()     const { return m_bool; }
    QColor      colorProp()    const { return m_color; }
    QFont       fontProp()     const { return m_font; }
    QPoint      pointProp()    const { return m_point; }
    QPointF     pointfProp()   const { return m_pointf; }
    QSize       sizeProp()     const { return m_size; }
    QSizeF      sizefProp()    const { return m_sizef; }
    QRect       rectProp()     const { return m_rect; }
    QRectF      rectfProp()    const { return m_rectf; }
    QLine       lineProp()     const { return m_line; }
    QLineF      linefProp()    const { return m_linef; }
    QBrush      brushProp()    const { return m_brush; }
    QPen        penProp()      const { return m_pen; }
    QVector2D   vec2Prop()     const { return m_vec2; }
    QVector3D   vec3Prop()     const { return m_vec3; }
    QVector4D   vec4Prop()     const { return m_vec4; }
    QStringList stringListProp() const { return m_stringList; }
    QDate       dateProp()     const { return m_date; }
    QTime       timeProp()     const { return m_time; }
    QDateTime   dateTimeProp() const { return m_dateTime; }
    QUrl        urlProp()      const { return m_url; }
    Qt::PenStyle penStyleProp() const { return m_penStyle; }
    QString     readOnlyProp()  const { return m_readOnly; }
    int         resettableProp() const { return m_resettable; }

    // ...existing setters...
    void setStringProp(const QString &v)       { m_string = v; }
    void setIntProp(int v)                     { m_int = v; }
    void setDoubleProp(double v)               { m_double = v; }
    void setBoolProp(bool v)                   { m_bool = v; }
    void setColorProp(const QColor &v)         { m_color = v; }
    void setFontProp(const QFont &v)           { m_font = v; }
    void setPointProp(const QPoint &v)         { m_point = v; }
    void setPointfProp(const QPointF &v)       { m_pointf = v; }
    void setSizeProp(const QSize &v)           { m_size = v; }
    void setSizefProp(const QSizeF &v)         { m_sizef = v; }
    void setRectProp(const QRect &v)           { m_rect = v; }
    void setRectfProp(const QRectF &v)         { m_rectf = v; }
    void setLineProp(const QLine &v)           { m_line = v; }
    void setLinefProp(const QLineF &v)         { m_linef = v; }
    void setBrushProp(const QBrush &v)         { m_brush = v; }
    void setPenProp(const QPen &v)             { m_pen = v; }
    void setVec2Prop(const QVector2D &v)       { m_vec2 = v; }
    void setVec3Prop(const QVector3D &v)       { m_vec3 = v; }
    void setVec4Prop(const QVector4D &v)       { m_vec4 = v; }
    void setStringListProp(const QStringList &v) { m_stringList = v; }
    void setDateProp(const QDate &v)           { m_date = v; }
    void setTimeProp(const QTime &v)           { m_time = v; }
    void setDateTimeProp(const QDateTime &v)   { m_dateTime = v; }
    void setUrlProp(const QUrl &v)             { m_url = v; }
    void setPenStyleProp(Qt::PenStyle v)       { m_penStyle = v; }
    void setResettableProp(int v)              { m_resettable = v; }
    void resetResettableProp()                 { m_resettable = 0; }

private:
    QString     m_string    {"Hello QPropertyModel"};
    int         m_int       {42};
    double      m_double    {3.14159};
    bool        m_bool      {true};
    QColor      m_color     {Qt::blue};
    QFont       m_font;
    QPoint      m_point     {10, 20};
    QPointF     m_pointf    {1.5, 2.5};
    QSize       m_size      {640, 480};
    QSizeF      m_sizef     {1920.0, 1080.0};
    QRect       m_rect      {0, 0, 100, 100};
    QRectF      m_rectf     {0.0, 0.0, 1.0, 1.0};
    QLine       m_line      {0, 0, 100, 0};
    QLineF      m_linef     {0.0, 0.0, 1.0, 0.0};
    QBrush      m_brush     {Qt::SolidPattern};
    QPen        m_pen;
    QVector2D   m_vec2      {1.0f, 2.0f};
    QVector3D   m_vec3      {1.0f, 2.0f, 3.0f};
    QVector4D   m_vec4      {1.0f, 2.0f, 3.0f, 4.0f};
    QStringList m_stringList{"Alpha", "Beta", "Gamma"};
    QDate       m_date      {QDate::currentDate()};
    QTime       m_time      {QTime::currentTime()};
    QDateTime   m_dateTime  {QDateTime::currentDateTime()};
    QUrl        m_url       {"https://github.com/cbuahin/QPropertyModel"};
    Qt::PenStyle m_penStyle {Qt::SolidLine};
    QString     m_readOnly  {"read-only value"};
    int         m_resettable{42};
};

// ---------------------------------------------------------------------------
// ClassInfoTestObject — used to test Q_CLASSINFO display label resolution
// ---------------------------------------------------------------------------
class ClassInfoTestObject : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("myProp", "My Pretty Name")
    Q_PROPERTY(int myProp READ myProp WRITE setMyProp)
public:
    explicit ClassInfoTestObject(QObject *parent = nullptr) : QObject(parent) {}
    int  myProp() const     { return m_val; }
    void setMyProp(int v)   { m_val = v; }
private:
    int m_val {0};
};

// ---------------------------------------------------------------------------
// DisplayLabelTestObject — used to test Q_INVOKABLE displayLabelFor() label resolution
// ---------------------------------------------------------------------------
class DisplayLabelTestObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int myProp READ myProp WRITE setMyProp)
public:
    explicit DisplayLabelTestObject(QObject *parent = nullptr) : QObject(parent) {}
    Q_INVOKABLE QString displayLabelFor(const QString &name) const
    {
        if (name == "myProp") return "My Pretty Name";
        return {};
    }
    int  myProp() const     { return m_val; }
    void setMyProp(int v)   { m_val = v; }
signals:
    void displayLabelsChanged();
private:
    int m_val {0};
};

#endif // TESTOBJECT_H
