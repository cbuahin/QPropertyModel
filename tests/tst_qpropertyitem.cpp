/*!
 * \file tst_qpropertyitem.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Unit tests for QPropertyItem.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */

#include <QtTest>
#include "qpropertyitem.h"
#include "qpropertymodel.h"

/*!
 * \brief Unit tests for the QPropertyItem base class.
 */
class TstQPropertyItem : public QObject
{
    Q_OBJECT

private slots:

    void testConstructionDefaults()
    {
        // Construct as orphan (no parent QPropertyItem -> model is nullptr)
        QPropertyItem item(QVariant(42), "testProp", nullptr);

        QCOMPARE(item.name(), QString("testProp"));
        QCOMPARE(item.data().toInt(), 42);
        QVERIFY(item.model() == nullptr);
        QVERIFY(item.parent() == nullptr);
        QCOMPARE(item.rowCount(), 0);
        QVERIFY(!item.hasChildren());
        QVERIFY(!item.canReset());
    }

    void testFlags()
    {
        QPropertyItem item(QVariant(), "test", nullptr);

        // Defaults: enabled + editable + selectable
        Qt::ItemFlags f = item.flags();
        QVERIFY(f.testFlag(Qt::ItemIsEnabled));
        QVERIFY(f.testFlag(Qt::ItemIsEditable));
        QVERIFY(f.testFlag(Qt::ItemIsSelectable));
        QVERIFY(!f.testFlag(Qt::ItemIsUserCheckable));
    }

    void testSetFlagsRoundTrip()
    {
        QPropertyItem item(QVariant(), "test", nullptr);
        Qt::ItemFlags newFlags = Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
        item.setFlags(newFlags);
        Qt::ItemFlags got = item.flags();
        QVERIFY(got.testFlag(Qt::ItemIsEnabled));
        QVERIFY(got.testFlag(Qt::ItemIsUserCheckable));
        QVERIFY(!got.testFlag(Qt::ItemIsEditable));
        QVERIFY(!got.testFlag(Qt::ItemIsSelectable));
    }

    void testSetDataEditRole()
    {
        QPropertyItem item(QVariant(1), "v", nullptr);
        bool ok = item.setData(QVariant(99), Qt::EditRole);
        QVERIFY(ok);
        QCOMPARE(item.data().toInt(), 99);
    }

    void testSetDataOtherRoleIgnored()
    {
        QPropertyItem item(QVariant(1), "v", nullptr);
        bool ok = item.setData(QVariant(99), Qt::DisplayRole);
        QVERIFY(!ok);
        QCOMPARE(item.data().toInt(), 1); // unchanged
    }

    void testValueChangedSignal()
    {
        QPropertyItem item(QVariant(0), "prop", nullptr);
        QSignalSpy spy(&item, &QPropertyItem::valueChanged);
        item.setData(QVariant(7), Qt::EditRole);
        QCOMPARE(spy.count(), 1);
        QCOMPARE(spy.at(0).at(0).toString(), QString("prop"));
        QCOMPARE(spy.at(0).at(1).toInt(), 7);
    }

    void testChildPropertyItemBoundsCheck()
    {
        QPropertyItem item(QVariant(), "test", nullptr);
        // Should return nullptr, not crash
        QVERIFY(item.childPropertyItem(-1) == nullptr);
        QVERIFY(item.childPropertyItem(0)  == nullptr);
        QVERIFY(item.childPropertyItem(100) == nullptr);
    }

    void testDataColumnProperty()
    {
        QPropertyItem item(QVariant("hello"), "myProp", nullptr);
        QVariant nameData = item.data(QPropertyItem::Property, Qt::DisplayRole);
        QCOMPARE(nameData.toString(), QString("myProp"));
    }

    void testDataColumnValue()
    {
        QPropertyItem item(QVariant("world"), "p", nullptr);
        QVariant valData = item.data(QPropertyItem::Value, Qt::DisplayRole);
        QCOMPARE(valData.toString(), QString("world"));
    }

    void testType()
    {
        QPropertyItem intItem(QVariant(42), "n", nullptr);
        QCOMPARE((int)intItem.type(), (int)QMetaType::Int);

        QPropertyItem strItem(QVariant(QString("x")), "s", nullptr);
        QCOMPARE((int)strItem.type(), (int)QMetaType::QString);
    }

    void testChildPropertyItemsEmptyList()
    {
        QPropertyItem item(QVariant(1), "x", nullptr);
        QVERIFY(item.childPropertyItems().isEmpty());
    }

    void testFlagsTristate()
    {
        QPropertyItem item(QVariant(), "t", nullptr);
        item.setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserTristate);
        QVERIFY(item.flags().testFlag(Qt::ItemIsUserTristate));
        QVERIFY(item.isTristate());
    }

    void testFlagsCheckable()
    {
        QPropertyItem item(QVariant(), "c", nullptr);
        item.setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
        QVERIFY(item.flags().testFlag(Qt::ItemIsUserCheckable));
        QVERIFY(item.isCheckable());
    }

    void testIsEditable()
    {
        QPropertyItem item(QVariant(), "e", nullptr);
        // Default = editable
        QVERIFY(item.isEditable());
        item.setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);  // no editable
        QVERIFY(!item.isEditable());
    }

    void testIsEnabled()
    {
        QPropertyItem item(QVariant(), "en", nullptr);
        QVERIFY(item.isEnabled());
    }

    void testIsSelectable()
    {
        QPropertyItem item(QVariant(), "s", nullptr);
        QVERIFY(item.isSelectable());
    }

    void testCanResetTrueAfterModelAttach()
    {
        // canReset() is false on plain QPropertyItem (no QMetaProperty.isResettable).
        // This is tested through the model for QVariantPropertyItem which sets m_canReset.
        QPropertyItem item(QVariant(0), "v", nullptr);
        QVERIFY(!item.canReset());
    }

    void testDataToolTipRole()
    {
        QPropertyItem item(QVariant("ttip"), "p", nullptr);
        QVariant tt = item.data(QPropertyItem::Value, Qt::ToolTipRole);
        QCOMPARE(tt.toString(), QString("ttip"));
    }

    void testDataStatusTipRole()
    {
        QPropertyItem item(QVariant("stip"), "p", nullptr);
        QVariant st = item.data(QPropertyItem::Value, Qt::StatusTipRole);
        QCOMPARE(st.toString(), QString("stip"));
    }

    void testDataInvalidColumn()
    {
        QPropertyItem item(QVariant(1), "x", nullptr);
        // Column 2 is out of range - should return invalid QVariant
        QVariant d = item.data(2, Qt::DisplayRole);
        QVERIFY(!d.isValid());
    }

    void testValueChangedSignalContent()
    {
        QPropertyItem item(QVariant(0), "myName", nullptr);
        QSignalSpy spy(&item, &QPropertyItem::valueChanged);
        item.setData(QVariant(55), Qt::EditRole);
        QCOMPARE(spy.count(), 1);
        // First argument is the property name
        QCOMPARE(spy.at(0).at(0).toString(), QString("myName"));
        // Second argument is the new value
        QCOMPARE(spy.at(0).at(1).toInt(), 55);
    }
};

QTEST_MAIN(TstQPropertyItem)
#include "tst_qpropertyitem.moc"
