/*!
 * \file testhelpers.h
 * \brief Shared helper functions for QPropertyModel unit tests.
 * \license SPDX-License-Identifier: MIT
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 */

#ifndef TESTHELPERS_H
#define TESTHELPERS_H

#include <QString>
#include <QModelIndex>
#include "qpropertymodel.h"
#include "qpropertyitem.h"

/*!
 * \brief Returns the column-1 (Value) index for a named property in the model.
 *
 * Searches all class-level rows at the top level of the model for a child whose
 * column-0 DisplayRole text matches \a propName.
 */
static inline QModelIndex findPropertyValueIndex(QPropertyModel &model,
                                                 const QString &propName)
{
    const int topRows = model.rowCount();
    for (int r = 0; r < topRows; ++r) {
        QModelIndex classIdx = model.index(r, 0);
        const int childRows = model.rowCount(classIdx);
        for (int c = 0; c < childRows; ++c) {
            QModelIndex nameIdx = model.index(c, 0, classIdx);
            if (model.data(nameIdx, Qt::DisplayRole).toString() == propName)
                return model.index(c, 1, classIdx);
        }
    }
    return QModelIndex();
}

/*!
 * \brief Returns the column-0 (Property name) index for a named property.
 */
static inline QModelIndex findPropertyNameIndex(QPropertyModel &model,
                                                const QString &propName)
{
    const int topRows = model.rowCount();
    for (int r = 0; r < topRows; ++r) {
        QModelIndex classIdx = model.index(r, 0);
        const int childRows = model.rowCount(classIdx);
        for (int c = 0; c < childRows; ++c) {
            QModelIndex nameIdx = model.index(c, 0, classIdx);
            if (model.data(nameIdx, Qt::DisplayRole).toString() == propName)
                return nameIdx;
        }
    }
    return QModelIndex();
}

/*!
 * \brief Returns the column-1 (Value) index for a named child of a named parent property.
 *
 * Useful for testing composite items (e.g. the "X" child of "pointProp").
 * \a parentPropName is the column-0 name of the parent property item.
 * \a childName is the column-0 name of the desired child.
 */
static inline QModelIndex findChildValueIndex(QPropertyModel &model,
                                              const QString &parentPropName,
                                              const QString &childName)
{
    QModelIndex parentNameIdx = findPropertyNameIndex(model, parentPropName);
    if (!parentNameIdx.isValid())
        return QModelIndex();

    // Trigger lazy child population (composite items require hasChildren() first)
    model.hasChildren(parentNameIdx);

    const int childRows = model.rowCount(parentNameIdx);
    for (int c = 0; c < childRows; ++c) {
        QModelIndex nameIdx = model.index(c, 0, parentNameIdx);
        if (model.data(nameIdx, Qt::DisplayRole).toString() == childName)
            return model.index(c, 1, parentNameIdx);
    }
    return QModelIndex();
}

/*!
 * \brief Returns the QPropertyItem* for a named property in the model.
 */
static inline QPropertyItem *findPropertyItem(QPropertyModel &model,
                                              const QString &propName)
{
    QModelIndex idx = findPropertyNameIndex(model, propName);
    if (!idx.isValid())
        return nullptr;
    return static_cast<QPropertyItem *>(idx.internalPointer());
}

#endif // TESTHELPERS_H

