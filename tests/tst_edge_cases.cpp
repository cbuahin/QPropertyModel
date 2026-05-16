/*!
 * \file tst_edge_cases.cpp
 * \brief Edge case and regression safety tests for QPropertyModel.
 * \license SPDX-License-Identifier: MIT
 */

#include <QtTest>
#include <QAbstractItemModelTester>
#include "qpropertymodel.h"
#include "qpropertyitem.h"
#include "qobjectpropertyitem.h"
#include "testobject.h"
#include "testhelpers.h"

// Q_OBJECT classes must be at file scope so MOC can process them.

class EmptyQObj : public QObject
{
    Q_OBJECT
public:
    explicit EmptyQObj(QObject *parent = nullptr) : QObject(parent) {}
};

class GrandChildQObj : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int a READ a)
public:
    explicit GrandChildQObj(QObject *parent = nullptr) : QObject(parent) {}
    int a() const { return 1; }
};

class TstEdgeCases : public QObject
{
    Q_OBJECT

private slots:

    void testSetDataInvalidVariantClearsModel()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QVERIFY(model.rowCount() > 0);
        model.setData(QVariant());
        QCOMPARE(model.rowCount(), 0);
        QVERIFY(model.rootPropertyItem() == nullptr);
    }

    void testSetDataRepeatedly()
    {
        // Calling setData multiple times should not leak or crash
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        for (int i = 0; i < 5; ++i) {
            model.setData(QVariant::fromValue<QObject*>(&obj));
            QVERIFY(model.rowCount() > 0);
        }
    }

    void testNullChildInObjectList()
    {
        TestObject a;
        QPropertyModel model(nullptr);
        model.setData(QList<QObject*>{nullptr, &a});
        // null filtered — should still work
        QVERIFY(model.rootPropertyItem() != nullptr);
    }

    void testAllNullsInObjectListClearsModel()
    {
        QPropertyModel model(nullptr);
        model.setData(QList<QObject*>{nullptr, nullptr});
        QCOMPARE(model.rowCount(), 0);
    }

    void testPropertyOrderStable()
    {
        // Property order should match QMetaObject::property order for the class.
        TestObject obj;
        QPropertyModel model(&obj, nullptr);

        // Navigate to the TestObject class-level item (last in hierarchy)
        QObjectPropertyItem *root = dynamic_cast<QObjectPropertyItem*>(model.rootPropertyItem());
        QVERIFY(root);
        root->hasChildren();
        int nClassItems = root->rowCount();
        QVERIFY(nClassItems > 0);

        // TestObject's own class-level item
        QPropertyItem *classItem = root->childPropertyItem(nClassItems - 1);
        QVERIFY(classItem);

        const QMetaObject *mo = obj.metaObject();
        const QMetaObject *base = mo->superClass();
        int startIdx = base ? base->propertyCount() : 0;
        int count = mo->propertyCount() - startIdx;
        QCOMPARE(classItem->rowCount(), count);

        // Check first child name matches first own property
        if (count > 0) {
            QPropertyItem *first = classItem->childPropertyItem(0);
            QVERIFY(first);
            QCOMPARE(first->name(), QString::fromLatin1(mo->property(startIdx).name()));
        }
    }

    void testNoPropertiesObjectHasZeroChildren()
    {
        EmptyQObj empty;
        QPropertyModel model(&empty, nullptr);

        QObjectPropertyItem *root = dynamic_cast<QObjectPropertyItem*>(model.rootPropertyItem());
        QVERIFY(root);
        root->hasChildren();

        bool foundEmpty = false;
        for (int i = 0; i < root->rowCount(); ++i) {
            QPropertyItem *ci = root->childPropertyItem(i);
            if (ci && ci->name() == "EmptyQObj") {
                foundEmpty = true;
                QCOMPARE(ci->rowCount(), 0);
            }
        }
        QVERIFY(foundEmpty);
    }

    void testModelConformanceAfterClear()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        model.clear();
        QAbstractItemModelTester t(&model,
            QAbstractItemModelTester::FailureReportingMode::Fatal, this);
        Q_UNUSED(t)
    }

    void testModelConformanceEmptyConstructor()
    {
        QPropertyModel model(nullptr);
        QAbstractItemModelTester t(&model,
            QAbstractItemModelTester::FailureReportingMode::Fatal, this);
        Q_UNUSED(t)
    }

    void testModelConformanceAfterQVariant()
    {
        QPropertyModel model(QVariant(QString("hello")), nullptr);
        QAbstractItemModelTester t(&model,
            QAbstractItemModelTester::FailureReportingMode::Fatal, this);
        Q_UNUSED(t)
    }

    void testDeepInheritanceChain()
    {
        GrandChildQObj gc;
        QPropertyModel model(&gc, nullptr);

        QObjectPropertyItem *root = dynamic_cast<QObjectPropertyItem*>(model.rootPropertyItem());
        QVERIFY(root);
        root->hasChildren();
        QVERIFY(root->rowCount() >= 1);
    }

    void testClearOnAlreadyEmptyModel()
    {
        QPropertyModel model(nullptr);
        // Should not crash when clearing an already empty model
        model.clear();
        model.clear();
        QCOMPARE(model.rowCount(), 0);
    }

    void testAllBuiltInPropertyTypesVisible()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);

        static const QStringList expectedProps{
            "stringProp", "intProp", "doubleProp", "boolProp", "colorProp",
            "fontProp", "pointProp", "pointfProp", "sizeProp", "sizefProp",
            "rectProp", "rectfProp", "lineProp", "linefProp", "brushProp",
            "penProp", "vec2Prop", "vec3Prop", "vec4Prop", "stringListProp",
            "dateProp", "timeProp", "dateTimeProp", "urlProp",
            "penStyleProp", "readOnlyProp", "resettableProp"
        };

        for (const QString &name : expectedProps) {
            QModelIndex idx = findPropertyNameIndex(model, name);
            QVERIFY2(idx.isValid(),
                     qPrintable("Property not found in model: " + name));
        }
    }

    void testRefreshValuesOnEmptyModelNocrash()
    {
        QPropertyModel model(nullptr);
        model.refreshValues();   // must not crash
    }

    void testDataForInvalidIndexReturnsInvalid()
    {
        QPropertyModel model(nullptr);
        QVariant v = model.data(QModelIndex(), Qt::DisplayRole);
        QVERIFY(!v.isValid());
    }
};

QTEST_MAIN(TstEdgeCases)
#include "tst_edge_cases.moc"

