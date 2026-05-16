/*!
 * \file tst_enum_properties.cpp
 * \brief Tests for QEnumPropertyItem and read-only properties.
 * \license SPDX-License-Identifier: MIT
 */

#include <QtTest>
#include "qpropertymodel.h"
#include "qpropertyitem.h"
#include "qenumpropertyitem.h"
#include "testobject.h"
#include "testhelpers.h"

class TstEnumProperties : public QObject
{
    Q_OBJECT

private slots:

    void testEnumPropertyShowsInModel()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "penStyleProp");
        QVERIFY2(item, "penStyleProp not found");
    }

    void testEnumPropertyDisplayRoleShowsKeyName()
    {
        TestObject obj;
        obj.setPenStyleProp(Qt::SolidLine);
        QPropertyModel model(&obj, nullptr);
        QModelIndex idx = findPropertyValueIndex(model, "penStyleProp");
        QVERIFY(idx.isValid());
        QString display = model.data(idx, Qt::DisplayRole).toString();
        QCOMPARE(display, QString("SolidLine"));
    }

    void testEnumPropertyEditRoleReturnsInt()
    {
        TestObject obj;
        obj.setPenStyleProp(Qt::DashLine);
        QPropertyModel model(&obj, nullptr);
        QModelIndex idx = findPropertyValueIndex(model, "penStyleProp");
        QVERIFY(idx.isValid());
        QCOMPARE(model.data(idx, Qt::EditRole).toInt(), (int)Qt::DashLine);
    }

    void testEnumPropertySetDataByInt()
    {
        TestObject obj;
        obj.setPenStyleProp(Qt::SolidLine);
        QPropertyModel model(&obj, nullptr);
        QModelIndex idx = findPropertyValueIndex(model, "penStyleProp");
        QVERIFY(idx.isValid());
        model.setData(idx, (int)Qt::DotLine, Qt::EditRole);
        QCOMPARE(obj.penStyleProp(), Qt::DotLine);
    }

    void testEnumPropertyHasNoChildren()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "penStyleProp");
        QVERIFY(item);
        QVERIFY(!item->hasChildren());
    }

    void testEnumPropertyIsEditable()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "penStyleProp");
        QVERIFY(item);
        QVERIFY(item->isEditable());
    }

    void testEnumPropertyItemType()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "penStyleProp");
        QVERIFY(item);
        QVERIFY2(dynamic_cast<QEnumPropertyItem*>(item) != nullptr,
                 "penStyleProp should be QEnumPropertyItem");
    }

    void testReadOnlyPropertyNotEditable()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QPropertyItem *item = findPropertyItem(model, "readOnlyProp");
        QVERIFY2(item, "readOnlyProp not found");
        QVERIFY(!item->isEditable());
    }

    void testReadOnlyPropertyDisplayRole()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex idx = findPropertyValueIndex(model, "readOnlyProp");
        QVERIFY(idx.isValid());
        QCOMPARE(model.data(idx, Qt::DisplayRole).toString(), QString("read-only value"));
    }

    void testReadOnlyFlagsNoEditable()
    {
        TestObject obj;
        QPropertyModel model(&obj, nullptr);
        QModelIndex idx = findPropertyValueIndex(model, "readOnlyProp");
        QVERIFY(idx.isValid());
        QVERIFY(!model.flags(idx).testFlag(Qt::ItemIsEditable));
    }
};

QTEST_MAIN(TstEnumProperties)
#include "tst_enum_properties.moc"

