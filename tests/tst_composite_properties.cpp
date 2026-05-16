/*!
 * \file tst_composite_properties.cpp
 * \brief Tests for composite property items: QBrush, QPen, QFont child interactions.
 * \license SPDX-License-Identifier: MIT
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 */

#include <QtTest>
#include <QBrush>
#include <QPen>
#include <QFont>
#include "qpropertymodel.h"
#include "qpropertyitem.h"
#include "testobject.h"
#include "testhelpers.h"

class TstCompositeProperties : public QObject
{
    Q_OBJECT

private slots:

    // ══ QBrushPropertyItem ═══════════════════════════════════════════════════

    void testBrushPropertyHasChildren()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "brushProp");
        QVERIFY2(item, "brushProp not found");
        QVERIFY(item->hasChildren());
    }

    void testBrushPropertyChildCount()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex nameIdx = findPropertyNameIndex(model, "brushProp");
        QVERIFY(nameIdx.isValid());
        model.hasChildren(nameIdx);
        QCOMPARE(model.rowCount(nameIdx), 3);  // Color, Brush Style, Texture
    }

    void testBrushPropertyChildNames()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex nameIdx = findPropertyNameIndex(model, "brushProp");
        model.hasChildren(nameIdx);
        QStringList names;
        for (int i = 0; i < model.rowCount(nameIdx); ++i)
            names << model.data(model.index(i, 0, nameIdx), Qt::DisplayRole).toString();
        QVERIFY(names.contains("Color"));
        QVERIFY(names.contains("Brush Style"));
        QVERIFY(names.contains("Texture"));
    }

    void testBrushPropertyColorChildUpdatesParent()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);

        QModelIndex colorIdx = findChildValueIndex(model, "brushProp", "Color");
        QVERIFY2(colorIdx.isValid(), "Color child of brushProp not found");
        model.setData(colorIdx, QColor(Qt::red), Qt::EditRole);
        QCOMPARE(obj.brushProp().color(), QColor(Qt::red));
    }

    void testBrushPropertyStyleChildUpdatesParent()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);

        QModelIndex styleIdx = findChildValueIndex(model, "brushProp", "Brush Style");
        QVERIFY2(styleIdx.isValid(), "Brush Style child of brushProp not found");
        model.setData(styleIdx, (int)Qt::Dense1Pattern, Qt::EditRole);
        QCOMPARE(obj.brushProp().style(), Qt::Dense1Pattern);
    }

    void testBrushPropertySetDataRoundTrip()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);

        QBrush newBrush(QColor(0, 128, 0), Qt::SolidPattern);
        QModelIndex idx = findPropertyValueIndex(model, "brushProp");
        QVERIFY(idx.isValid());
        model.setData(idx, QVariant::fromValue(newBrush), Qt::EditRole);

        QCOMPARE(obj.brushProp().color(), QColor(0, 128, 0));
        QCOMPARE(obj.brushProp().style(), Qt::SolidPattern);
    }

    // ══ QPenPropertyItem ═════════════════════════════════════════════════════

    void testPenPropertyHasChildren()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "penProp");
        QVERIFY2(item, "penProp not found");
        QVERIFY(item->hasChildren());
    }

    void testPenPropertyChildCount()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex nameIdx = findPropertyNameIndex(model, "penProp");
        QVERIFY(nameIdx.isValid());
        model.hasChildren(nameIdx);
        QCOMPARE(model.rowCount(nameIdx), 6);  // Width, Dash Offset, Style, Cap Style, Join Style, Brush
    }

    void testPenPropertyChildNames()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex nameIdx = findPropertyNameIndex(model, "penProp");
        model.hasChildren(nameIdx);
        QStringList names;
        for (int i = 0; i < model.rowCount(nameIdx); ++i)
            names << model.data(model.index(i, 0, nameIdx), Qt::DisplayRole).toString();
        QVERIFY(names.contains("Width"));
        QVERIFY(names.contains("Style"));
        QVERIFY(names.contains("Brush"));
    }

    void testPenPropertyWidthChildUpdatesObject()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);

        QModelIndex wIdx = findChildValueIndex(model, "penProp", "Width");
        QVERIFY2(wIdx.isValid(), "Width child of penProp not found");
        model.setData(wIdx, 3.0, Qt::EditRole);
        QVERIFY(qAbs(obj.penProp().widthF() - 3.0) < 0.001);
    }

    void testPenPropertyStyleChildUpdatesObject()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);

        QModelIndex sIdx = findChildValueIndex(model, "penProp", "Style");
        QVERIFY2(sIdx.isValid(), "Style child of penProp not found");
        model.setData(sIdx, (int)Qt::DashLine, Qt::EditRole);
        QCOMPARE(obj.penProp().style(), Qt::DashLine);
    }

    void testPenPropertyBrushChildIsExpandable()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex penNameIdx = findPropertyNameIndex(model, "penProp");
        QVERIFY(penNameIdx.isValid());
        model.hasChildren(penNameIdx);
        int childRows = model.rowCount(penNameIdx);
        bool foundBrush = false;
        for (int i = 0; i < childRows; ++i) {
            QString cname = model.data(model.index(i, 0, penNameIdx), Qt::DisplayRole).toString();
            if (cname == "Brush") {
                foundBrush = true;
                QModelIndex brushNameIdx = model.index(i, 0, penNameIdx);
                QVERIFY(model.hasChildren(brushNameIdx));
            }
        }
        QVERIFY2(foundBrush, "Brush child not found under penProp");
    }

    // ══ QFontPropertyItem ════════════════════════════════════════════════════

    void testFontPropertyHasChildren()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "fontProp");
        QVERIFY2(item, "fontProp not found");
        QVERIFY(item->hasChildren());
    }

    void testFontPropertyChildCount()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex nameIdx = findPropertyNameIndex(model, "fontProp");
        QVERIFY(nameIdx.isValid());
        model.hasChildren(nameIdx);
        // Family, Point Size, Bold, Italic, Underline, Strikeout, Kerning, Style Strategy = 8
        QCOMPARE(model.rowCount(nameIdx), 8);
    }

    void testFontPropertyChildNames()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex nameIdx = findPropertyNameIndex(model, "fontProp");
        model.hasChildren(nameIdx);
        QStringList names;
        for (int i = 0; i < model.rowCount(nameIdx); ++i)
            names << model.data(model.index(i, 0, nameIdx), Qt::DisplayRole).toString();
        QVERIFY(names.contains("Family"));
        QVERIFY(names.contains("Point Size"));
        QVERIFY(names.contains("Bold"));
        QVERIFY(names.contains("Italic"));
    }

    void testFontPropertyDisplayRole()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QVariant d = model.data(findPropertyValueIndex(model, "fontProp"), Qt::DisplayRole);
        QVERIFY(d.isValid());
        QVERIFY(!d.toString().isEmpty());
    }

    void testFontPropertyPointSizeChildUpdatesObject()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);

        QModelIndex psIdx = findChildValueIndex(model, "fontProp", "Point Size");
        QVERIFY2(psIdx.isValid(), "Point Size child of fontProp not found");
        model.setData(psIdx, 18, Qt::EditRole);
        QCOMPARE(obj.fontProp().pointSize(), 18);
    }
};

QTEST_MAIN(TstCompositeProperties)
#include "tst_composite_properties.moc"

