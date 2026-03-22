/*!
 * \file qobjectlistpropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item representing a QList<QObject*> property.
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

#ifndef QOBJECTLISTPROPERTYITEM_H
#define QOBJECTLISTPROPERTYITEM_H

#include "qvariantpropertyItem.h"

typedef QList<QObject*> (VariantToObjectListConverter)(const QVariant&);

/*!
 * \brief Property item representing a \c QList<QObject*> property.
 *
 * \details Displays the list count as "[Count=N]" in the value column and
 * opens a popup editor (QObjectListPropertyItemEditor) on edit that embeds a
 * separate QPropertyModel for each element in the list, allowing individual
 * object properties to be inspected and modified inline.
 *
 * \details An optional converter function may be registered via
 * setQVariantToQObjectListConverter() to handle QVariant types that wrap a
 * list of objects but are not of type \c QList<QObject*> directly (e.g.
 * custom container types).
 *
 * \sa QVariantPropertyItem, QObjectClassPropertyItem
 */
class QPROPERTYMODEL_EXPORT QObjectListPropertyItem :  public QVariantPropertyItem
{
      Q_OBJECT

   public:

      /*!
       * \brief Constructs a QObjectListPropertyItem.
       *
       * \param[in] value        The QVariant containing the \c QList<QObject*>.
       * \param[in] metaProperty The corresponding QMetaProperty descriptor.
       * \param[in] parent       Owning class-level property item.
       */
      Q_INVOKABLE QObjectListPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem* parent);

      /*!
       * \brief Destroys this item.
       */
      virtual ~QObjectListPropertyItem();

      /*!
       * \brief Returns display data for the given column and role.
       *
       * \details Column 1, Qt::DisplayRole returns the list size formatted as
       * "[Count=N]".  All other roles delegate to QVariantPropertyItem::data().
       *
       * \param[in] column  Target column (0 = Property, 1 = Value).
       * \param[in] role    Qt item-data role.
       * \returns The requested data, or an invalid QVariant.
       */
      QVariant data(int column = 1, Qt::ItemDataRole role = Qt::UserRole) const override;

      /*!
       * \brief Registers a converter function used to extract a
       *        \c QList<QObject*> from an arbitrary QVariant.
       *
       * \details Useful when the registered Q_PROPERTY is a custom container
       * type that can be converted to \c QList<QObject*> but does not carry
       * that type signature directly.
       *
       * \param[in] converter  Pointer to a conversion function.  The function
       *                       receives the property QVariant and must return a
       *                       \c QList<QObject*>.
       */
      void setQVariantToQObjectListConverter(VariantToObjectListConverter* converter);

   private:
      VariantToObjectListConverter* m_variantToObjectListConverter; /*!< \brief Optional custom converter; may be \c nullptr. */

};

#endif // QOBJECTLISTPROPERTYITEM_H


