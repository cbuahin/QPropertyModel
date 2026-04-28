/*!
 * \file qobjectpropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item wrapping a QObject pointer for sub-object expansion.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 * \copyright
 * Copyright 2026, Caleb Buahin, All rights reserved.
 * \date 2014-2026
 * \pre
 * \bug
 * \warning
 * \todo
 */

#ifndef QOBJECTPROPERTYITEM_H
#define QOBJECTPROPERTYITEM_H

#include "qpropertyitem.h"
#include <QMetaProperty>

/*!
 * \brief Property item wrapping a QObject pointer for hierarchical expansion.
 *
 * \details When a QMetaProperty's value can be cast to a QObject*, this item
 * is used as the expandable container.  Expanding it creates one
 * QObjectClassPropertyItem per class in the target object's meta-object chain,
 * following the pattern used for the top-level object in QPropertyModel.
 *
 * \details The property item also handles write-back: when the user edits a
 * leaf property inside this subtree, the change propagates up via the
 * valueChanged() signal chain and is eventually committed through
 * m_property.write() on the parent QObject.
 *
 * \sa QObjectClassPropertyItem, QVariantPropertyItem
 */
class QPROPERTYMODEL_EXPORT QObjectPropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a QObjectPropertyItem for a single QObject.
       */
      Q_INVOKABLE QObjectPropertyItem(QObject* value, const QMetaProperty& prop, QPropertyItem* parent);

      /*!
       * \brief Constructs a QObjectPropertyItem for multiple QObjects.
       *
       * \details All objects should share the same (or compatible)
       * meta-object hierarchy.  The first object in the list is used as the
       * primary for display and child construction.
       */
      QObjectPropertyItem(const QList<QObject*>& values, const QMetaProperty& prop, QPropertyItem* parent);

      virtual ~QObjectPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole role = Qt::UserRole) const override;
      bool setData(const QVariant& value, Qt::ItemDataRole role = Qt::UserRole) override;
      bool hasChildren() override;
      int rowCount() const override;

      /*!
       * \brief Returns the primary QObject pointer.
       */
      QObject* qObject() const;

      /*!
       * \brief Returns all managed QObject pointers.
       */
      QList<QObject*> qObjects() const;

   protected:
      QList<QObject*> m_objectvalues; /*!< \brief The wrapped QObject instances. */

   private:
      QMetaProperty m_property;
      bool          m_hasMetaProperty;
};

#endif // QOBJECTPROPERTYITEM_H
