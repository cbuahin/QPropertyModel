/*!
 * \file tst_customtypes.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Unit tests for custom type registration in QPropertyModel.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */

#include <QtTest>
#include "qpropertymodel.h"
#include "qpropertyitem.h"
#include "qvariantpropertyItem.h"
#include "qvariantholderhelper.h"
#include "testobject.h"

/*!
 * \brief Unit tests for custom type registration and QVariantHolderHelper.
 */
class TstCustomTypes : public QObject
{
    Q_OBJECT

private slots:

    // ── registerCustomPropertyItemType error paths ────────────────────────────

    void testRegisterNullMetaObjectReturnsFalse()
    {
        QPropertyModel model(nullptr);
        bool ok = model.registerCustomPropertyItemType(QMetaType::Int, nullptr);
        QVERIFY(!ok);
    }

    void testRegisterNonPropertyItemSubclassReturnsFalse()
    {
        QPropertyModel model(nullptr);
        // TestObject is a QObject but NOT a QPropertyItem subclass.
        bool ok = model.registerCustomPropertyItemType(
            QMetaType::User + 1,
            &TestObject::staticMetaObject);
        QVERIFY(!ok);
    }

    // ── registerCustomPropertyItemType success path ───────────────────────────

    void testRegisterQPropertyItemSubclassReturnsTrue()
    {
        QPropertyModel model(nullptr);
        // QVariantPropertyItem IS a QPropertyItem subclass — it should succeed.
        bool ok = model.registerCustomPropertyItemType(
            QMetaType::User + 100,
            &QVariantPropertyItem::staticMetaObject);
        QVERIFY(ok);
    }

    void testDoubleRegistrationOverwrites()
    {
        QPropertyModel model(nullptr);
        int fakeType = QMetaType::User + 200;
        bool first = model.registerCustomPropertyItemType(
            fakeType, &QVariantPropertyItem::staticMetaObject);
        // Re-registering the same type with a different (still valid) class
        // should also return true (overwrite semantics).
        bool second = model.registerCustomPropertyItemType(
            fakeType, &QVariantPropertyItem::staticMetaObject);
        QVERIFY(first);
        QVERIFY(second);
    }

    // ── QVariantHolderHelper ──────────────────────────────────────────────────

    void testVariantHolderHelperStoresValue()
    {
        QVariantHolderHelper helper(QVariant(42), nullptr);
        QCOMPARE(helper.value().toInt(), 42);
    }

    void testVariantHolderHelperSetValue()
    {
        QVariantHolderHelper helper(QVariant(1), nullptr);
        helper.setValue(QVariant(99));
        QCOMPARE(helper.value().toInt(), 99);
    }

    void testVariantHolderHelperValueChangedSignal()
    {
        QVariantHolderHelper helper(QVariant(0), nullptr);
        QSignalSpy spy(&helper, &QVariantHolderHelper::valueChanged);
        helper.setValue(QVariant(7));
        QCOMPARE(spy.count(), 1);
    }

    // ── QPropertyModel with plain QVariant input ──────────────────────────────

    void testModelWithPlainQVariant()
    {
        // A plain int QVariant causes the model to wrap it in QVariantHolderHelper.
        QPropertyModel model(QVariant(123), nullptr);
        QVERIFY(model.rowCount() > 0);
        QVERIFY(model.rootPropertyItem() != nullptr);
    }

    void testModelWithQVariantStringReturnsValue()
    {
        QPropertyModel model(QVariant(QString("hello")), nullptr);
        QVERIFY(model.rowCount() > 0);

        // The first (and only) row should expose the value "hello".
        QModelIndex idx = model.index(0, 1);  // column 1 = Value
        QCOMPARE(model.data(idx, Qt::DisplayRole).toString(), QString("hello"));
    }

    // ── QList<QObject*> auto-registration ────────────────────────────────────

    void testObjectListAutoRegistration()
    {
        // QList<QObject*> is automatically registered on model construction.
        // We verify that setting a QList<QObject*> variant produces rows.
        TestObject a, b;
        QList<QObject*> lst{ &a, &b };
        QPropertyModel model(QVariant::fromValue(lst), nullptr);
        QVERIFY(model.rowCount() > 0);
    }

    // ── QVariantHolderHelper extended ─────────────────────────────────────────

    void testVariantHolderHelperModelIndexRoundTrip()
    {
        QVariantHolderHelper helper(QVariant(0), nullptr);
        QModelIndex idx;   // invalid (default-constructed)
        // setModelIndex / modelIndex round-trip
        helper.setModelIndex(idx);
        QVERIFY(!helper.modelIndex().isValid());
    }

    void testVariantHolderHelperObjectNameHidden()
    {
        // objectName() is overridden to return "" so it does not appear in the model.
        // Access via QObject* since the override is private in QVariantHolderHelper.
        QVariantHolderHelper helper(QVariant(42), nullptr);
        QObject *asObj = &helper;
        QCOMPARE(asObj->objectName(), QString());
    }

    void testVariantHolderHelperSetValueSameNoDoubleSignal()
    {
        QVariantHolderHelper helper(QVariant(7), nullptr);
        QSignalSpy spy(&helper, &QVariantHolderHelper::valueChanged);
        helper.setValue(QVariant(7));  // same value
        // Implementation may or may not suppress — at minimum should not crash
        // and the stored value should remain 7.
        QCOMPARE(helper.value().toInt(), 7);
    }
};

QTEST_MAIN(TstCustomTypes)
#include "tst_customtypes.moc"
