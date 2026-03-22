/*!
 * \file tst_qpropertymodel.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Unit tests for QPropertyModel.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */

#include <QtTest>
#include <QAbstractItemModelTester>

#include "qpropertymodel.h"
#include "qpropertyitem.h"
#include "testobject.h"

/*!
 * \brief Unit tests for the QPropertyModel class.
 */
class TstQPropertyModel : public QObject
{
    Q_OBJECT

private slots:

    // ── Construction ──────────────────────────────────────────────────────────

    void testDefaultConstructor()
    {
        QPropertyModel model(nullptr);
        QCOMPARE(model.columnCount(), 2);
        QCOMPARE(model.rowCount(), 0);
        QVERIFY(model.rootPropertyItem() == nullptr);
    }

    void testConstructWithQObject()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QCOMPARE(model.columnCount(), 2);
        QVERIFY(model.rowCount() > 0);
        QVERIFY(model.rootPropertyItem() != nullptr);
    }

    void testConstructWithQVariant()
    {
        QPropertyModel model(QVariant(42), nullptr);
        QVERIFY(model.rowCount() > 0);
    }

    // ── QAbstractItemModel conformance ────────────────────────────────────────

    void testModelConformance()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        // QAbstractItemModelTester verifies that the model's index(), parent(),
        // rowCount(), columnCount(), and data() behave correctly.
        QAbstractItemModelTester tester(&model,
            QAbstractItemModelTester::FailureReportingMode::Fatal, this);
        Q_UNUSED(tester)
    }

    // ── setData(QVariant) ─────────────────────────────────────────────────────

    void testSetDataClearsAndReloads()
    {
        QPropertyModel model(nullptr);
        QCOMPARE(model.rowCount(), 0);

        TestObject obj;
        model.setData(QVariant::fromValue(&obj));
        int rowsAfter = model.rowCount();
        QVERIFY(rowsAfter > 0);

        model.setData(QVariant());
        QCOMPARE(model.rowCount(), 0);
    }

    void testSetDataEmitsResetSignals()
    {
        TestObject obj;
        QPropertyModel model(nullptr);

        QSignalSpy spy(&model, &QAbstractItemModel::modelReset);
        model.setData(QVariant::fromValue(&obj));
        QCOMPARE(spy.count(), 1);
    }

    // ── clear() ───────────────────────────────────────────────────────────────

    void testClear()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QVERIFY(model.rowCount() > 0);

        QSignalSpy spy(&model, &QAbstractItemModel::modelReset);
        model.clear();

        QCOMPARE(model.rowCount(), 0);
        QVERIFY(model.rootPropertyItem() == nullptr);
        QCOMPARE(spy.count(), 1);
    }

    // ── registerCustomPropertyItemType() ─────────────────────────────────────

    void testRegisterNullMetaObjectReturnsFalse()
    {
        QPropertyModel model(nullptr);
        QVERIFY(!model.registerCustomPropertyItemType(QMetaType::User, nullptr));
    }

    // ── columnCount / headerData ──────────────────────────────────────────────

    void testColumnCount()
    {
        QPropertyModel model(nullptr);
        QCOMPARE(model.columnCount(), 2);
    }

    void testHeaderData()
    {
        QPropertyModel model(nullptr);
        QVariant prop = model.headerData(0, Qt::Horizontal, Qt::DisplayRole);
        QVariant val  = model.headerData(1, Qt::Horizontal, Qt::DisplayRole);
        QVERIFY(prop.isValid());
        QVERIFY(val.isValid());
    }

    // ── data() ────────────────────────────────────────────────────────────────

    void testDataForStringProperty()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);

        // Properties are nested under class-level items, so search recursively
        bool found = false;
        int topRows = model.rowCount();
        for (int r = 0; r < topRows && !found; ++r)
        {
            QModelIndex classIdx = model.index(r, 0);
            int childRows = model.rowCount(classIdx);
            for (int c = 0; c < childRows; ++c)
            {
                QModelIndex nameIdx  = model.index(c, 0, classIdx);
                QModelIndex valueIdx = model.index(c, 1, classIdx);
                if (model.data(nameIdx, Qt::DisplayRole).toString() == "stringProp")
                {
                    found = true;
                    QCOMPARE(model.data(valueIdx, Qt::DisplayRole).toString(),
                             obj.stringProp());
                    break;
                }
            }
        }
        QVERIFY2(found, "stringProp not found in model");
    }

    // ── setData(QModelIndex) ──────────────────────────────────────────────────

    void testSetDataUpdatesQObject()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);

        // Properties are nested under class-level items, so search recursively
        int topRows = model.rowCount();
        for (int r = 0; r < topRows; ++r)
        {
            QModelIndex classIdx = model.index(r, 0);
            int childRows = model.rowCount(classIdx);
            for (int c = 0; c < childRows; ++c)
            {
                QModelIndex nameIdx  = model.index(c, 0, classIdx);
                QModelIndex valueIdx = model.index(c, 1, classIdx);
                if (model.data(nameIdx, Qt::DisplayRole).toString() == "intProp")
                {
                    model.setData(valueIdx, 99, Qt::EditRole);
                    QCOMPARE(obj.intProp(), 99);
                    return;
                }
            }
        }
        QFAIL("intProp not found");
    }

    // ── hasChildren / flags ────────────────────────────────────────────────────

    void testHasChildrenForRootIsTrue()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QVERIFY(model.hasChildren());
    }
};

QTEST_MAIN(TstQPropertyModel)
#include "tst_qpropertymodel.moc"
