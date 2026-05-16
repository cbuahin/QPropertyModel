/*!
 * \file tst_typed_properties.cpp
 * \brief Unit tests for leaf typed property items: bool, point, size, rect, vectors.
 * \license SPDX-License-Identifier: MIT
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 */

#include <QtTest>
#include "qpropertymodel.h"
#include "qpropertyitem.h"
#include "qboolpropertyitem.h"
#include "qpointpropertyitem.h"
#include "qpointfpropertyitem.h"
#include "qsizepropertyitem.h"
#include "qsizefpropertyitem.h"
#include "qrectpropertyitem.h"
#include "qrectfpropertyitem.h"
#include "qvector2dpropertyitem.h"
#include "qvector3dpropertyitem.h"
#include "qvector4dpropertyitem.h"
#include "testobject.h"
#include "testhelpers.h"

class TstTypedProperties : public QObject
{
    Q_OBJECT

private slots:

    // ══ QBoolPropertyItem ════════════════════════════════════════════════════

    void testBoolPropertyCheckStateChecked()
    {
        TestObject obj;
        obj.setBoolProp(true);
        QPropertyModel model(&obj, nullptr);

        QPropertyItem *item = findPropertyItem(model, "boolProp");
        QVERIFY2(item, "boolProp not found");
        QVariant cs = item->data(QPropertyItem::Value, Qt::CheckStateRole);
        QCOMPARE(cs.toInt(), (int)Qt::Checked);
    }

    void testBoolPropertyCheckStateUnchecked()
    {
        TestObject obj;
        obj.setBoolProp(false);
        QPropertyModel model(&obj, nullptr);

        QPropertyItem *item = findPropertyItem(model, "boolProp");
        QVERIFY(item);
        QVariant cs = item->data(QPropertyItem::Value, Qt::CheckStateRole);
        QCOMPARE(cs.toInt(), (int)Qt::Unchecked);
    }

    void testBoolPropertyDisplayRoleEmpty()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "boolProp");
        QVERIFY(item);
        // Bool items show checkbox only; DisplayRole should be empty
        QVariant d = item->data(QPropertyItem::Value, Qt::DisplayRole);
        QVERIFY(!d.isValid() || d.toString().isEmpty());
    }

    void testBoolPropertySetDataCheckState()
    {
        TestObject obj;
        obj.setBoolProp(false);
        QPropertyModel model(&obj, nullptr);

        QModelIndex idx = findPropertyValueIndex(model, "boolProp");
        QVERIFY(idx.isValid());
        model.setData(idx, (int)Qt::Checked, Qt::CheckStateRole);
        QCOMPARE(obj.boolProp(), true);
    }

    void testBoolPropertySetDataUnchecked()
    {
        TestObject obj;
        obj.setBoolProp(true);
        QPropertyModel model(&obj, nullptr);

        QModelIndex idx = findPropertyValueIndex(model, "boolProp");
        QVERIFY(idx.isValid());
        model.setData(idx, (int)Qt::Unchecked, Qt::CheckStateRole);
        QCOMPARE(obj.boolProp(), false);
    }

    void testBoolPropertyIsCheckable()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "boolProp");
        QVERIFY(item);
        QVERIFY(item->isCheckable());
    }

    void testBoolPropertyIsNotEditable()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "boolProp");
        QVERIFY(item);
        QVERIFY(!item->isEditable());
    }

    // ══ QPointPropertyItem ═══════════════════════════════════════════════════

    void testPointPropertyHasChildren()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "pointProp");
        QVERIFY2(item, "pointProp not found");
        QVERIFY(item->hasChildren());
    }

    void testPointPropertyChildCount()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex nameIdx = findPropertyNameIndex(model, "pointProp");
        QVERIFY(nameIdx.isValid());
        model.hasChildren(nameIdx);  // trigger lazy child creation
        QCOMPARE(model.rowCount(nameIdx), 2);
    }

    void testPointPropertyChildNames()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex nameIdx = findPropertyNameIndex(model, "pointProp");
        QVERIFY(nameIdx.isValid());
        model.hasChildren(nameIdx);
        QStringList names;
        for (int i = 0; i < model.rowCount(nameIdx); ++i)
            names << model.data(model.index(i, 0, nameIdx), Qt::DisplayRole).toString();
        QVERIFY(names.contains("X"));
        QVERIFY(names.contains("Y"));
    }

    void testPointPropertyDisplayRole()
    {
        TestObject obj;  // default pointProp = (10, 20)
        QPropertyModel model(&obj, nullptr);
        QModelIndex idx = findPropertyValueIndex(model, "pointProp");
        QVERIFY(idx.isValid());
        QString display = model.data(idx, Qt::DisplayRole).toString();
        QVERIFY2(display.contains("10") && display.contains("20"),
                 qPrintable("Expected '10' and '20' in display: " + display));
    }

    void testPointPropertyEditingXUpdatesObject()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex xIdx = findChildValueIndex(model, "pointProp", "X");
        QVERIFY2(xIdx.isValid(), "X child of pointProp not found");
        model.setData(xIdx, 99, Qt::EditRole);
        QCOMPARE(obj.pointProp().x(), 99);
    }

    void testPointPropertyEditingYUpdatesObject()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex yIdx = findChildValueIndex(model, "pointProp", "Y");
        QVERIFY2(yIdx.isValid(), "Y child of pointProp not found");
        model.setData(yIdx, 77, Qt::EditRole);
        QCOMPARE(obj.pointProp().y(), 77);
    }

    // ══ QPointFPropertyItem ══════════════════════════════════════════════════

    void testPointFPropertyHasChildren()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "pointfProp");
        QVERIFY2(item, "pointfProp not found");
        QVERIFY(item->hasChildren());
    }

    void testPointFPropertyChildCount()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex nameIdx = findPropertyNameIndex(model, "pointfProp");
        QVERIFY(nameIdx.isValid());
        model.hasChildren(nameIdx);
        QCOMPARE(model.rowCount(nameIdx), 2);
    }

    void testPointFPropertyEditingXUpdatesObject()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex xIdx = findChildValueIndex(model, "pointfProp", "X");
        QVERIFY2(xIdx.isValid(), "X child of pointfProp not found");
        model.setData(xIdx, 3.14, Qt::EditRole);
        QVERIFY(qAbs(obj.pointfProp().x() - 3.14) < 0.001);
    }

    // ══ QSizePropertyItem ════════════════════════════════════════════════════

    void testSizePropertyHasChildren()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "sizeProp");
        QVERIFY2(item, "sizeProp not found");
        QVERIFY(item->hasChildren());
    }

    void testSizePropertyChildCount()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex nameIdx = findPropertyNameIndex(model, "sizeProp");
        QVERIFY(nameIdx.isValid());
        model.hasChildren(nameIdx);
        QCOMPARE(model.rowCount(nameIdx), 2);
    }

    void testSizePropertyChildNames()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex nameIdx = findPropertyNameIndex(model, "sizeProp");
        model.hasChildren(nameIdx);
        QStringList names;
        for (int i = 0; i < model.rowCount(nameIdx); ++i)
            names << model.data(model.index(i, 0, nameIdx), Qt::DisplayRole).toString();
        QVERIFY(names.contains("Width"));
        QVERIFY(names.contains("Height"));
    }

    void testSizePropertyDisplayRole()
    {
        TestObject obj;  // default sizeProp = 640 x 480
        QPropertyModel model(&obj, nullptr);
        QString display = model.data(findPropertyValueIndex(model, "sizeProp"), Qt::DisplayRole).toString();
        QVERIFY(display.contains("640") && display.contains("480"));
    }

    void testSizePropertyEditingWidthUpdatesObject()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex wIdx = findChildValueIndex(model, "sizeProp", "Width");
        QVERIFY2(wIdx.isValid(), "Width child not found");
        model.setData(wIdx, 800, Qt::EditRole);
        QCOMPARE(obj.sizeProp().width(), 800);
    }

    void testSizePropertyEditingHeightUpdatesObject()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex hIdx = findChildValueIndex(model, "sizeProp", "Height");
        QVERIFY2(hIdx.isValid(), "Height child not found");
        model.setData(hIdx, 600, Qt::EditRole);
        QCOMPARE(obj.sizeProp().height(), 600);
    }

    // ══ QRectPropertyItem ════════════════════════════════════════════════════

    void testRectPropertyHasChildren()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "rectProp");
        QVERIFY2(item, "rectProp not found");
        QVERIFY(item->hasChildren());
    }

    void testRectPropertyChildCount()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex nameIdx = findPropertyNameIndex(model, "rectProp");
        QVERIFY(nameIdx.isValid());
        model.hasChildren(nameIdx);
        QCOMPARE(model.rowCount(nameIdx), 4);  // X, Y, Width, Height
    }

    void testRectPropertyDisplayRole()
    {
        TestObject obj;  // default rectProp = (0,0,100,100)
        QPropertyModel model(&obj, nullptr);
        QString display = model.data(findPropertyValueIndex(model, "rectProp"), Qt::DisplayRole).toString();
        QVERIFY(display.contains("0") && display.contains("100"));
    }

    void testRectPropertyEditingXUpdatesObject()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex xIdx = findChildValueIndex(model, "rectProp", "X");
        QVERIFY2(xIdx.isValid(), "X child of rectProp not found");
        model.setData(xIdx, 5, Qt::EditRole);
        QCOMPARE(obj.rectProp().x(), 5);
    }

    void testRectPropertyEditingWidthUpdatesObject()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex wIdx = findChildValueIndex(model, "rectProp", "Width");
        QVERIFY2(wIdx.isValid(), "Width child of rectProp not found");
        model.setData(wIdx, 200, Qt::EditRole);
        QCOMPARE(obj.rectProp().width(), 200);
    }

    // ══ QVector2DPropertyItem ════════════════════════════════════════════════

    void testVec2PropertyHasChildren()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "vec2Prop");
        QVERIFY2(item, "vec2Prop not found");
        QVERIFY(item->hasChildren());
    }

    void testVec2PropertyChildCount()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex nameIdx = findPropertyNameIndex(model, "vec2Prop");
        QVERIFY(nameIdx.isValid());
        model.hasChildren(nameIdx);
        QCOMPARE(model.rowCount(nameIdx), 2);  // X, Y
    }

    void testVec2PropertyEditingXUpdatesObject()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex xIdx = findChildValueIndex(model, "vec2Prop", "X");
        QVERIFY2(xIdx.isValid(), "X child of vec2Prop not found");
        model.setData(xIdx, 9.0, Qt::EditRole);
        QVERIFY(qAbs(obj.vec2Prop().x() - 9.0f) < 0.001f);
    }

    // ══ QVector3DPropertyItem ════════════════════════════════════════════════

    void testVec3PropertyChildCount()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex nameIdx = findPropertyNameIndex(model, "vec3Prop");
        QVERIFY(nameIdx.isValid());
        model.hasChildren(nameIdx);
        QCOMPARE(model.rowCount(nameIdx), 3);  // X, Y, Z
    }

    void testVec3PropertyChildNames()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex nameIdx = findPropertyNameIndex(model, "vec3Prop");
        model.hasChildren(nameIdx);
        QStringList names;
        for (int i = 0; i < model.rowCount(nameIdx); ++i)
            names << model.data(model.index(i, 0, nameIdx), Qt::DisplayRole).toString();
        QVERIFY(names.contains("X"));
        QVERIFY(names.contains("Y"));
        QVERIFY(names.contains("Z"));
    }

    // ══ QVector4DPropertyItem ════════════════════════════════════════════════

    void testVec4PropertyChildCount()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex nameIdx = findPropertyNameIndex(model, "vec4Prop");
        QVERIFY(nameIdx.isValid());
        model.hasChildren(nameIdx);
        QCOMPARE(model.rowCount(nameIdx), 4);  // X, Y, Z, W
    }

    void testVec4PropertyChildNames()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex nameIdx = findPropertyNameIndex(model, "vec4Prop");
        model.hasChildren(nameIdx);
        QStringList names;
        for (int i = 0; i < model.rowCount(nameIdx); ++i)
            names << model.data(model.index(i, 0, nameIdx), Qt::DisplayRole).toString();
        QVERIFY(names.contains("W"));
    }
};

QTEST_MAIN(TstTypedProperties)
#include "tst_typed_properties.moc"

