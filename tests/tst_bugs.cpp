/*!
 * \file tst_bugs.cpp
 * \brief Regression tests for verified bugs BUG-01 and BUG-02.
 * \license SPDX-License-Identifier: MIT
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 */

#include <QtTest>
#include "qpropertymodel.h"
#include "qpropertyitem.h"
#include "qobjectpropertyitem.h"
#include "qpenpropertyitem.h"
#include "testobject.h"
#include "testhelpers.h"

/*!
 * \brief Regression tests for BUG-01 and BUG-02.
 */
class TstBugs : public QObject
{
    Q_OBJECT

private slots:

    // ── BUG-01: QObjectPropertyItem::data() displayed class name was dead code ──

    void testBug01_QObjectPropertyItemDisplayRoleShowsClassName()
    {
        // Create a QObject that itself has a QObject* property by using a
        // model built around an object whose root item is QObjectPropertyItem.
        TestObject obj;
        QPropertyModel model(&obj, nullptr);

        // The rootPropertyItem is the QObjectPropertyItem wrapping the TestObject.
        QObjectPropertyItem *root = dynamic_cast<QObjectPropertyItem*>(model.rootPropertyItem());
        QVERIFY2(root != nullptr, "rootPropertyItem should be QObjectPropertyItem");

        // data(col=1, DisplayRole) should return the class name, NOT QVariant()
        QVariant displayData = root->data(QPropertyItem::Value, Qt::DisplayRole);
        QVERIFY2(displayData.isValid(), "BUG-01 regression: DisplayRole data from QObjectPropertyItem should not be invalid");
        QVERIFY2(!displayData.toString().isEmpty(), "BUG-01 regression: class name string should not be empty");
        QCOMPARE(displayData.toString(), QString("TestObject"));
    }

    // ── BUG-02: QPenPropertyItem::flags() duplicate m_isEnabled, suppressed ItemIsEditable ──

    void testBug02_PenItemFlagsIncludeEditableWhenWritable()
    {
        // penProp in TestObject is writable, so its QPropertyItem should be editable.
        TestObject obj;
        QPropertyModel model(&obj, nullptr);

        QPropertyItem *item = findPropertyItem(model, "penProp");
        QVERIFY2(item != nullptr, "penProp should be found in the model");

        Qt::ItemFlags flags = item->flags();
        QVERIFY2(flags.testFlag(Qt::ItemIsEditable),
                 "BUG-02 regression: writable QPen property should have ItemIsEditable");
    }

    void testBug02_PenItemFlagsNoDuplicateEnabled()
    {
        // Verify that ItemIsEnabled is set exactly once (not duplicated).
        // We test this indirectly: flags() should be consistent and not set
        // bits that aren't expected.
        TestObject obj;
        QPropertyModel model(&obj, nullptr);

        QPropertyItem *item = findPropertyItem(model, "penProp");
        QVERIFY(item != nullptr);

        Qt::ItemFlags flags = item->flags();
        // ItemIsEnabled should be set
        QVERIFY(flags.testFlag(Qt::ItemIsEnabled));
        // ItemIsSelectable should be set
        QVERIFY(flags.testFlag(Qt::ItemIsSelectable));
        // ItemIsEditable should be set (writable property) — BUG-02 regression
        QVERIFY(flags.testFlag(Qt::ItemIsEditable));
        // ItemIsUserCheckable should NOT be set (not a bool)
        QVERIFY(!flags.testFlag(Qt::ItemIsUserCheckable));
    }

    void testBug02_CompositeItemFlagsEditable_Point()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "pointProp");
        QVERIFY(item != nullptr);
        QVERIFY2(item->flags().testFlag(Qt::ItemIsEditable),
                 "Writable QPoint property should have ItemIsEditable after BUG-02 fix");
    }

    void testBug02_CompositeItemFlagsEditable_Size()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "sizeProp");
        QVERIFY(item != nullptr);
        QVERIFY(item->flags().testFlag(Qt::ItemIsEditable));
    }

    void testBug02_CompositeItemFlagsEditable_Rect()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "rectProp");
        QVERIFY(item != nullptr);
        QVERIFY(item->flags().testFlag(Qt::ItemIsEditable));
    }

    void testBug02_CompositeItemFlagsEditable_Vec2()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "vec2Prop");
        QVERIFY(item != nullptr);
        QVERIFY(item->flags().testFlag(Qt::ItemIsEditable));
    }
};

QTEST_MAIN(TstBugs)
#include "tst_bugs.moc"

