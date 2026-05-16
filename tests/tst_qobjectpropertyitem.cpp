/*!
 * \file tst_qobjectpropertyitem.cpp
 * \brief Unit tests for QObjectPropertyItem (BUG-01 regression + behaviour).
 * \license SPDX-License-Identifier: MIT
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 */

#include <QtTest>
#include "qpropertymodel.h"
#include "qpropertyitem.h"
#include "qobjectpropertyitem.h"
#include "qobjectclasspropertyitem.h"
#include "testobject.h"
#include "testhelpers.h"

/*!
 * \brief Unit tests for QObjectPropertyItem.
 */
class TstQObjectPropertyItem : public QObject
{
    Q_OBJECT

private slots:

    // ── Construction ──────────────────────────────────────────────────────────

    void testSingleObjectHasChildren()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QObjectPropertyItem *root = dynamic_cast<QObjectPropertyItem*>(model.rootPropertyItem());
        QVERIFY2(root != nullptr, "rootPropertyItem should be QObjectPropertyItem for QObject source");
        QVERIFY(root->hasChildren());
    }

    void testChildrenAreClassPropertyItems()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QObjectPropertyItem *root = dynamic_cast<QObjectPropertyItem*>(model.rootPropertyItem());
        QVERIFY(root != nullptr);
        root->hasChildren();
        QVERIFY(root->rowCount() > 0);
        for (int i = 0; i < root->rowCount(); ++i) {
            QPropertyItem *child = root->childPropertyItem(i);
            QVERIFY2(dynamic_cast<QObjectClassPropertyItem*>(child) != nullptr,
                     "All children of QObjectPropertyItem should be QObjectClassPropertyItem");
        }
    }

    void testQObjectReturnsPrimary()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QObjectPropertyItem *root = dynamic_cast<QObjectPropertyItem*>(model.rootPropertyItem());
        QVERIFY(root != nullptr);
        QCOMPARE(root->qObject(), &obj);
    }

    void testQObjectsReturnsList()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QObjectPropertyItem *root = dynamic_cast<QObjectPropertyItem*>(model.rootPropertyItem());
        QVERIFY(root != nullptr);
        QCOMPARE(root->qObjects().size(), 1);
    }

    void testMultiObjectConstructorCarriesAllObjects()
    {
        TestObject a, b;
        QPropertyModel model(nullptr);
        model.setData(QList<QObject*>{&a, &b});
        QObjectPropertyItem *root = dynamic_cast<QObjectPropertyItem*>(model.rootPropertyItem());
        QVERIFY(root != nullptr);
        QCOMPARE(root->qObjects().size(), 2);
    }

    // ── BUG-01 regression: data() DisplayRole returns class name ─────────────

    void testDataDisplayRoleReturnsClassName()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QObjectPropertyItem *root = dynamic_cast<QObjectPropertyItem*>(model.rootPropertyItem());
        QVERIFY(root != nullptr);

        QVariant v = root->data(QPropertyItem::Value, Qt::DisplayRole);
        // BUG-01: was always returning QVariant() due to dead code
        QVERIFY2(v.isValid(), "QObjectPropertyItem::data(DisplayRole) should not return invalid");
        QCOMPARE(v.toString(), QString("TestObject"));
    }

    // ── showQObjectName ───────────────────────────────────────────────────────

    void testShowQObjectNameFalseHidesQObjectLevel()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);  // showQObjectName = false by default

        // Count class-level items — QObject level should be excluded
        QObjectPropertyItem *root = dynamic_cast<QObjectPropertyItem*>(model.rootPropertyItem());
        QVERIFY(root);
        root->hasChildren();

        bool hasQObjectLevel = false;
        for (int i = 0; i < root->rowCount(); ++i) {
            QObjectClassPropertyItem *ci = dynamic_cast<QObjectClassPropertyItem*>(
                root->childPropertyItem(i));
            if (ci && ci->name() == "QObject")
                hasQObjectLevel = true;
        }
        QVERIFY2(!hasQObjectLevel, "QObject class level should be hidden by default");
    }

    void testShowQObjectNameTrueIncludesQObjectLevel()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        model.setShowQObjectName(true);

        QObjectPropertyItem *root = dynamic_cast<QObjectPropertyItem*>(model.rootPropertyItem());
        QVERIFY(root);
        root->hasChildren();

        bool hasQObjectLevel = false;
        for (int i = 0; i < root->rowCount(); ++i) {
            QObjectClassPropertyItem *ci = dynamic_cast<QObjectClassPropertyItem*>(
                root->childPropertyItem(i));
            if (ci && ci->name() == "QObject")
                hasQObjectLevel = true;
        }
        QVERIFY2(hasQObjectLevel, "QObject class level should be visible when showQObjectName=true");
    }

    // ── setData() ────────────────────────────────────────────────────────────

    void testSetDataEditRoleReturnsFalse()
    {
        // QObjectPropertyItem::setData always returns false (no direct editing of QObject ptr)
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QObjectPropertyItem *root = dynamic_cast<QObjectPropertyItem*>(model.rootPropertyItem());
        QVERIFY(root);
        bool ok = root->setData(QVariant(42), Qt::EditRole);
        QVERIFY(!ok);
    }

    // ── rowCount() lazy init ──────────────────────────────────────────────────

    void testRowCountEqualsHasChildrenResult()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QObjectPropertyItem *root = dynamic_cast<QObjectPropertyItem*>(model.rootPropertyItem());
        QVERIFY(root);
        // Calling rowCount before hasChildren should also trigger lazy init
        int rc = root->rowCount();
        QVERIFY(rc > 0);
    }
};

QTEST_MAIN(TstQObjectPropertyItem)
#include "tst_qobjectpropertyitem.moc"

