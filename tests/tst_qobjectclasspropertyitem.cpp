/*!
 * \file tst_qobjectclasspropertyitem.cpp
 * \brief Unit tests for QObjectClassPropertyItem.
 * \license SPDX-License-Identifier: MIT
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 */

#include <QtTest>
#include "qpropertymodel.h"
#include "qpropertyitem.h"
#include "qobjectclasspropertyitem.h"
#include "qobjectpropertyitem.h"
#include "testobject.h"
#include "testhelpers.h"

/*!
 * \brief Unit tests for QObjectClassPropertyItem.
 */
class TstQObjectClassPropertyItem : public QObject
{
    Q_OBJECT

    // Helper: get the first QObjectClassPropertyItem from a model built on obj
    static QObjectClassPropertyItem *firstClassItem(QPropertyModel &model)
    {
        QPropertyItem *root = model.rootPropertyItem();
        if (!root) return nullptr;
        if (root->rowCount() == 0) root->hasChildren();
        if (root->rowCount() == 0) return nullptr;
        return dynamic_cast<QObjectClassPropertyItem*>(root->childPropertyItem(root->rowCount() - 1));
    }

private slots:

    // ── Construction / data ───────────────────────────────────────────────────

    void testDataDisplayRoleReturnsClassName()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QObjectClassPropertyItem *ci = firstClassItem(model);
        QVERIFY2(ci != nullptr, "First class item should be QObjectClassPropertyItem");
        QVariant name = ci->data(QPropertyItem::Property, Qt::DisplayRole);
        QCOMPARE(name.toString(), QString("TestObject"));
    }

    void testDataBackgroundRoleReturns()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QObjectClassPropertyItem *ci = firstClassItem(model);
        QVERIFY(ci != nullptr);
        QVariant bg = ci->data(QPropertyItem::Property, Qt::BackgroundRole);
        QVERIFY(bg.isValid());
        QVERIFY(bg.canConvert<QColor>());
    }

    void testDataForegroundRoleReturns()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QObjectClassPropertyItem *ci = firstClassItem(model);
        QVERIFY(ci != nullptr);
        QVariant fg = ci->data(QPropertyItem::Property, Qt::ForegroundRole);
        QVERIFY(fg.isValid());
    }

    void testSetDataIsNoOp()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QObjectClassPropertyItem *ci = firstClassItem(model);
        QVERIFY(ci != nullptr);
        bool ok = ci->setData(QVariant(999), Qt::EditRole);
        QVERIFY(!ok);
    }

    // ── hasChildren / rowCount ────────────────────────────────────────────────

    void testHasChildrenEnumeratesOwnProperties()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QObjectClassPropertyItem *ci = firstClassItem(model);
        QVERIFY(ci != nullptr);
        // TestObject declares many own properties
        QVERIFY(ci->hasChildren());
        QVERIFY(ci->rowCount() > 0);
    }

    void testChildCountMatchesOwnPropertyCount()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QObjectClassPropertyItem *ci = firstClassItem(model);
        QVERIFY(ci != nullptr);

        // Own properties = total - superClass.propertyCount()
        const QMetaObject *mo = obj.metaObject();
        const QMetaObject *base = mo->superClass();
        int expected = mo->propertyCount() - (base ? base->propertyCount() : 0);
        QCOMPARE(ci->rowCount(), expected);
    }

    // ── qObject / qObjects / isMultiObject ────────────────────────────────────

    void testQObjectReturnsPrimary()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QObjectClassPropertyItem *ci = firstClassItem(model);
        QVERIFY(ci != nullptr);
        QCOMPARE(ci->qObject(), &obj);
    }

    void testQObjectsReturnsList()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QObjectClassPropertyItem *ci = firstClassItem(model);
        QVERIFY(ci != nullptr);
        QCOMPARE(ci->qObjects().size(), 1);
        QCOMPARE(ci->qObjects().first(), &obj);
    }

    void testIsMultiObjectFalseForSingle()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QObjectClassPropertyItem *ci = firstClassItem(model);
        QVERIFY(ci != nullptr);
        QVERIFY(!ci->isMultiObject());
    }

    void testIsMultiObjectTrueForTwo()
    {
        TestObject a, b;
        QPropertyModel model(nullptr);
        model.setData(QList<QObject*>{&a, &b});

        QPropertyItem *root = model.rootPropertyItem();
        QVERIFY(root != nullptr);
        if (root->rowCount() == 0) root->hasChildren();
        QObjectClassPropertyItem *ci = dynamic_cast<QObjectClassPropertyItem*>(
            root->childPropertyItem(root->rowCount() - 1));
        QVERIFY(ci != nullptr);
        QVERIFY(ci->isMultiObject());
    }

    // ── hasUniformValue / writePropertyToAll ──────────────────────────────────

    void testHasUniformValueSingleAlwaysTrue()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QObjectClassPropertyItem *ci = firstClassItem(model);
        QVERIFY(ci != nullptr);

        const QMetaObject *mo = obj.metaObject();
        const QMetaObject *base = mo->superClass();
        int start = base ? base->propertyCount() : 0;
        QMetaProperty prop = mo->property(start);  // first own property

        QVERIFY(ci->hasUniformValue(prop));
    }

    void testHasUniformValueSameValues()
    {
        TestObject a, b;
        a.setIntProp(10);
        b.setIntProp(10);
        QPropertyModel model(nullptr);
        model.setData(QList<QObject*>{&a, &b});

        QPropertyItem *root = model.rootPropertyItem();
        if (root) root->hasChildren();
        QObjectClassPropertyItem *ci = dynamic_cast<QObjectClassPropertyItem*>(
            root ? root->childPropertyItem(root->rowCount() - 1) : nullptr);
        QVERIFY(ci != nullptr);

        int idx = a.metaObject()->indexOfProperty("intProp");
        QVERIFY(idx >= 0);
        QMetaProperty prop = a.metaObject()->property(idx);
        QVERIFY(ci->hasUniformValue(prop));
    }

    void testHasUniformValueDifferentValues()
    {
        TestObject a, b;
        a.setIntProp(1);
        b.setIntProp(2);
        QPropertyModel model(nullptr);
        model.setData(QList<QObject*>{&a, &b});

        QPropertyItem *root = model.rootPropertyItem();
        if (root) root->hasChildren();
        QObjectClassPropertyItem *ci = dynamic_cast<QObjectClassPropertyItem*>(
            root ? root->childPropertyItem(root->rowCount() - 1) : nullptr);
        QVERIFY(ci != nullptr);

        int idx = a.metaObject()->indexOfProperty("intProp");
        QVERIFY(idx >= 0);
        QMetaProperty prop = a.metaObject()->property(idx);
        QVERIFY(!ci->hasUniformValue(prop));
    }

    void testWritePropertyToAllWritesBoth()
    {
        TestObject a, b;
        QPropertyModel model(nullptr);
        model.setData(QList<QObject*>{&a, &b});

        QPropertyItem *root = model.rootPropertyItem();
        if (root) root->hasChildren();
        QObjectClassPropertyItem *ci = dynamic_cast<QObjectClassPropertyItem*>(
            root ? root->childPropertyItem(root->rowCount() - 1) : nullptr);
        QVERIFY(ci != nullptr);

        int idx = a.metaObject()->indexOfProperty("intProp");
        QVERIFY(idx >= 0);
        QMetaProperty prop = a.metaObject()->property(idx);
        bool ok = ci->writePropertyToAll(prop, 55);
        QVERIFY(ok);
        QCOMPARE(a.intProp(), 55);
        QCOMPARE(b.intProp(), 55);
    }

    // ── resolveDisplayLabel ───────────────────────────────────────────────────

    void testResolveDisplayLabelFallbackToPropertyName()
    {
        // TestObject has no Q_CLASSINFO and no displayLabelFor → raw name used.
        TestObject obj;
        QPropertyModel model(&obj, nullptr);

        // The child named "intProp" should still be named "intProp"
        QPropertyItem *item = findPropertyItem(model, "intProp");
        QVERIFY2(item != nullptr, "intProp should appear in model");
        QCOMPARE(item->name(), QString("intProp"));
    }

    void testResolveDisplayLabelUsesClassInfo()
    {
        // ClassInfoTestObject has Q_CLASSINFO("myProp", "My Pretty Name")
        ClassInfoTestObject obj;
        QPropertyModel model(&obj, nullptr);

        // The property should be shown with the classinfo label
        QPropertyItem *item = findPropertyItem(model, "My Pretty Name");
        QVERIFY2(item != nullptr, "Q_CLASSINFO label 'My Pretty Name' not found in model");
    }

    void testResolveDisplayLabelUsesDisplayLabelFor()
    {
        // DisplayLabelTestObject has Q_INVOKABLE displayLabelFor("myProp") -> "My Pretty Name"
        DisplayLabelTestObject obj;
        QPropertyModel model(&obj, nullptr);

        QPropertyItem *item = findPropertyItem(model, "My Pretty Name");
        QVERIFY2(item != nullptr, "displayLabelFor() label 'My Pretty Name' not found in model");
    }

    // ── refreshDisplayLabels ──────────────────────────────────────────────────

    void testRefreshDisplayLabelsUpdatesChildNames()
    {
        // Emit displayLabelsChanged() and verify the label updates.
        DisplayLabelTestObject obj;
        QPropertyModel model(&obj, nullptr);

        // Ensure labels are built
        QPropertyItem *item = findPropertyItem(model, "My Pretty Name");
        QVERIFY(item != nullptr);

        // After refreshDisplayLabels, the same label should still be applied
        // (no other mechanism needed; this just verifies no crash and stability)
        emit obj.displayLabelsChanged();
        item = findPropertyItem(model, "My Pretty Name");
        QVERIFY(item != nullptr);
    }
};

QTEST_MAIN(TstQObjectClassPropertyItem)
#include "tst_qobjectclasspropertyitem.moc"

