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
       * \brief Constructs a QObjectPropertyItem.
       *
       * \param[in] value   The QObject instance to display as a sub-tree.
       * \param[in] prop    The QMetaProperty through which \a value was obtained.
       *                    Pass an empty QMetaProperty for manually constructed
       *                    (non-Q_PROPERTY) items.
       * \param[in] parent  Parent property item.
       */
      Q_INVOKABLE QObjectPropertyItem(QObject* value, const QMetaProperty& prop, QPropertyItem* parent);

      /*!
       * \brief Destroys this item and all lazily created child items.
       */
      virtual ~QObjectPropertyItem();

      /*!
       * \brief Returns data for the given column and role.
       *
       * \details Column 0 returns the class name of the wrapped QObject.
       * Column 1 is typically empty; subclasses may override this.
       *
       * \param[in] column  Target column (0 = Property, 1 = Value).
       * \param[in] role    Qt item-data role.
       * \returns The requested data, or an invalid QVariant.
       */
      QVariant data(int column = 1, Qt::ItemDataRole role = Qt::UserRole) const override;

      /*!
       * \brief Writes the object pointer through the backing QMetaProperty.
       *
       * \details Only meaningful when this item was created from a writable
       * Q_PROPERTY.  If m_hasMetaProperty is false this is a no-op.
       *
       * \param[in] value  New QObject* wrapped in a QVariant.
       * \param[in] role   Qt item-data role.
       * \returns \c true if the write succeeded, \c false otherwise.
       */
      bool setData(const QVariant& value, Qt::ItemDataRole role = Qt::UserRole) override;

      /*!
       * \brief Returns \c true if the wrapped QObject is non-null and
       *        implements at least one Q_PROPERTY declaration.
       * \returns \c true when children can be constructed.
       */
      bool hasChildren() override;

      /*!
       * \brief Returns the number of child class-level items.
       *
       * \details Triggers lazy child construction (via hasChildren()) on the
       * first call so that rowCount() always reflects the actual hierarchy.
       *
       * \returns The number of child items.
       */
      int rowCount() const override;

      /*!
       * \brief Returns the wrapped QObject pointer.
       * \returns The QObject instance passed at construction time.
       */
      QObject* qObject() const;

   protected:
      QObject* m_objectvalue; /*!< \brief The wrapped QObject instance. */

   private:
      QMetaProperty m_property;       /*!< \brief Optional backing Q_PROPERTY through which this object was obtained. */
      bool          m_hasMetaProperty; /*!< \brief Whether m_property is valid and writable. */

};

#endif // QOBJECTPROPERTYITEM_H
