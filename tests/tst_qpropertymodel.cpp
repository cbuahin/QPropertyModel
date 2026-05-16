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
#include <QSignalSpy>

#include "qpropertymodel.h"
#include "qpropertyitem.h"
#include "testobject.h"
#include "testhelpers.h"

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

    // ── flags() ───────────────────────────────────────────────────────────────

    void testFlagsInvalidIndexDropEnabled()
    {
        QPropertyModel model(nullptr);
        Qt::ItemFlags f = model.flags(QModelIndex());
        QVERIFY(f.testFlag(Qt::ItemIsDropEnabled));
    }

    void testFlagsColumn0EnabledSelectable()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex col0 = model.index(0, 0);
        Qt::ItemFlags f = model.flags(col0);
        QVERIFY(f.testFlag(Qt::ItemIsEnabled));
        QVERIFY(f.testFlag(Qt::ItemIsSelectable));
        QVERIFY(!f.testFlag(Qt::ItemIsEditable));
    }

    void testFlagsColumn1WritableIsEditable()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex valueIdx = findPropertyValueIndex(model, "intProp");
        QVERIFY(valueIdx.isValid());
        Qt::ItemFlags f = model.flags(valueIdx);
        QVERIFY(f.testFlag(Qt::ItemIsEditable));
    }

    void testFlagsColumn1ReadOnlyNotEditable()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex valueIdx = findPropertyValueIndex(model, "readOnlyProp");
        QVERIFY(valueIdx.isValid());
        Qt::ItemFlags f = model.flags(valueIdx);
        QVERIFY(!f.testFlag(Qt::ItemIsEditable));
    }

    // ── headerData() ──────────────────────────────────────────────────────────

    void testHeaderDataSection0IsProperty()
    {
        QPropertyModel model(nullptr);
        QVariant h = model.headerData(0, Qt::Horizontal, Qt::DisplayRole);
        QCOMPARE(h.toString(), QString("Property"));
    }

    void testHeaderDataSection1IsValue()
    {
        QPropertyModel model(nullptr);
        QVariant h = model.headerData(1, Qt::Horizontal, Qt::DisplayRole);
        QCOMPARE(h.toString(), QString("Value"));
    }

    void testHeaderDataVerticalReturnsInvalid()
    {
        QPropertyModel model(nullptr);
        QVariant h = model.headerData(0, Qt::Vertical, Qt::DisplayRole);
        QVERIFY(!h.isValid());
    }

    void testHeaderDataOutOfRangeSectionReturnsInvalid()
    {
        QPropertyModel model(nullptr);
        QVERIFY(!model.headerData(99, Qt::Horizontal, Qt::DisplayRole).isValid());
    }

    // ── rowCount() / hasChildren() Qt model convention ────────────────────────

    void testRowCountForColumn1IsZero()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        // A column-1 index: Qt model contract — only column 0 can have children
        QModelIndex col1 = model.index(0, 1);
        QCOMPARE(model.rowCount(col1), 0);
    }

    void testHasChildrenForColumn1IsFalse()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex col1 = model.index(0, 1);
        QVERIFY(!model.hasChildren(col1));
    }

    // ── parent() ──────────────────────────────────────────────────────────────

    void testParentOfTopLevelIsInvalid()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex top = model.index(0, 0);
        QVERIFY(!model.parent(top).isValid());
    }

    void testParentOfChildIsTopLevel()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex classIdx = model.index(0, 0);
        QModelIndex childIdx = model.index(0, 0, classIdx);
        QVERIFY(childIdx.isValid());
        QCOMPARE(model.parent(childIdx), classIdx);
    }

    // ── index() out of range ──────────────────────────────────────────────────

    void testIndexOutOfRangeRow()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QVERIFY(!model.index(-1, 0).isValid());
        QVERIFY(!model.index(9999, 0).isValid());
    }

    // ── rootQVariantItem() ────────────────────────────────────────────────────

    void testRootQVariantItemAfterQVariantSetData()
    {
        QPropertyModel model(QVariant(99), nullptr);
        QVariant rv = model.rootQVariantItem();
        QVERIFY(rv.isValid());
        QCOMPARE(rv.toInt(), 99);
    }

    void testRootQVariantItemAfterClear()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        model.clear();
        // After clear with QObject source, rootQVariantItem is invalid
        // (no wrapper used)
        QVERIFY(model.rootPropertyItem() == nullptr);
    }

    // ── refreshValues() ────────────────────────────────────────────────────────

    void testRefreshValuesEmitsDataChanged()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);

        QSignalSpy spy(&model, &QAbstractItemModel::dataChanged);
        model.refreshValues();
        // At least one dataChanged should be emitted (for the value column rows)
        QVERIFY(spy.count() > 0);
    }

    void testRefreshValuesDoesNotEmitModelReset()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QSignalSpy spy(&model, &QAbstractItemModel::modelReset);
        model.refreshValues();
        QCOMPARE(spy.count(), 0);
    }

    void testRefreshValuesWithEmptyModel()
    {
        QPropertyModel model(nullptr);
        // Should not crash
        model.refreshValues();
    }

    // ── showQObjectName ────────────────────────────────────────────────────────

    void testShowQObjectNameDefaultFalse()
    {
        QPropertyModel model(nullptr);
        QVERIFY(!model.showQObjectName());
    }

    void testSetShowQObjectNameTriggersReset()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QSignalSpy spy(&model, &QAbstractItemModel::modelReset);
        model.setShowQObjectName(true);
        QCOMPARE(spy.count(), 1);
    }

    void testSetShowQObjectNameSameValueNoReset()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QVERIFY(!model.showQObjectName());  // default false
        QSignalSpy spy(&model, &QAbstractItemModel::modelReset);
        model.setShowQObjectName(false);    // same value
        QCOMPARE(spy.count(), 0);
    }

    // ── multi-object setData() ─────────────────────────────────────────────────

    void testSetDataObjectListMultiObject()
    {
        TestObject a, b;
        QPropertyModel model(nullptr);
        model.setData(QList<QObject*>{&a, &b});
        QVERIFY(model.rowCount() > 0);
        QVERIFY(model.rootPropertyItem() != nullptr);
    }

    void testSetDataObjectListEmptyClears()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QVERIFY(model.rowCount() > 0);
        model.setData(QList<QObject*>{});
        QCOMPARE(model.rowCount(), 0);
    }

    void testSetDataObjectListWithNullsFiltered()
    {
        TestObject a;
        // List with one valid and one null — should still produce rows for 'a'
        QPropertyModel model(nullptr);
        model.setData(QList<QObject*>{nullptr, &a});
        QVERIFY(model.rowCount() > 0);
    }

    void testMultiObjectModelConformance()
    {
        TestObject a, b;
        QPropertyModel model(nullptr);
        model.setData(QList<QObject*>{&a, &b});
        QAbstractItemModelTester tester(&model,
            QAbstractItemModelTester::FailureReportingMode::Fatal, this);
        Q_UNUSED(tester)
    }

    void testMultiObjectWriteToAll()
    {
        TestObject a, b;
        QPropertyModel model(nullptr);
        model.setData(QList<QObject*>{&a, &b});

        QModelIndex idx = findPropertyValueIndex(model, "intProp");
        QVERIFY(idx.isValid());
        model.setData(idx, 77, Qt::EditRole);
        QCOMPARE(a.intProp(), 77);
        QCOMPARE(b.intProp(), 77);
    }

    void testMultiObjectMixedValueShowsEmDash()
    {
        TestObject a, b;
        a.setIntProp(1);
        b.setIntProp(2);  // different values → mixed
        QPropertyModel model(nullptr);
        model.setData(QList<QObject*>{&a, &b});

        QModelIndex idx = findPropertyValueIndex(model, "intProp");
        QVERIFY(idx.isValid());
        QString display = model.data(idx, Qt::DisplayRole).toString();
        // em dash U+2014 indicates mixed value
        QVERIFY2(display == QString("\xe2\x80\x94"),
                 qPrintable("Expected em-dash for mixed value, got: " + display));
    }

    void testMultiObjectUniformValueShowsValue()
    {
        TestObject a, b;
        a.setIntProp(42);
        b.setIntProp(42);  // same value → uniform
        QPropertyModel model(nullptr);
        model.setData(QList<QObject*>{&a, &b});

        QModelIndex idx = findPropertyValueIndex(model, "intProp");
        QVERIFY(idx.isValid());
        QVariant display = model.data(idx, Qt::DisplayRole);
        QCOMPARE(display.toInt(), 42);
    }

    // ── resettable property ────────────────────────────────────────────────────

    void testResettablePropertyCanReset()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "resettableProp");
        QVERIFY2(item != nullptr, "resettableProp not found in model");
        QVERIFY2(item->canReset(), "resettableProp should have canReset() == true");
    }

    void testResettablePropertyResetData()
    {
        TestObject obj;
        obj.setResettableProp(999);
        QPropertyModel model(&obj, nullptr);

        QModelIndex idx = findPropertyValueIndex(model, "resettableProp");
        QVERIFY(idx.isValid());
        model.setData(idx, 999, Qt::EditRole);
        QCOMPARE(obj.resettableProp(), 999);

        // Now call resetData via QVariantPropertyItem
        QPropertyItem *item = findPropertyItem(model, "resettableProp");
        QVERIFY(item != nullptr);
        item->resetData();
        QCOMPARE(obj.resettableProp(), 0);  // reset fn sets to 0
    }

    // ── setName() triggers model update ───────────────────────────────────────

    void testSetNameTriggersDataChanged()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);

        QPropertyItem *item = findPropertyItem(model, "intProp");
        QVERIFY(item != nullptr);

        QSignalSpy spy(&model, &QAbstractItemModel::dataChanged);
        item->setName("renamedProp");
        QVERIFY(spy.count() >= 1);

        // Restore
        item->setName("intProp");
    }

    void testSetNameNoOpWhenSame()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "intProp");
        QVERIFY(item != nullptr);

        QSignalSpy spy(&model, &QAbstractItemModel::dataChanged);
        item->setName("intProp");  // same name → should not signal
        QCOMPARE(spy.count(), 0);
    }
};

QTEST_MAIN(TstQPropertyModel)
#include "tst_qpropertymodel.moc"
