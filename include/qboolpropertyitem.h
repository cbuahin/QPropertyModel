/*!
 * \file qboolpropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for bool type rendered as a checkbox.
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

#ifndef QBOOLPROPERTYITEM_H
#define QBOOLPROPERTYITEM_H

#include "qvariantpropertyItem.h"

/*!
 * \brief Property item for \c bool properties rendered as a checkbox.
 *
 * \details Returns Qt::CheckStateRole data so the view renders a checkbox in the
 * value column.  Setting data via either Qt::CheckStateRole or Qt::EditRole
 * converts the input to a bool and writes it back to the underlying
 * QMetaProperty.
 */
class QBoolPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a bool property item.
       *
       * \param[in] value        The initial bool value wrapped in a QVariant.
       * \param[in] metaProperty The meta-property this item represents on the parent QObject.
       * \param[in] parent       The QObjectClassPropertyItem that owns this item.
       */
      QBoolPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QBoolPropertyItem();

      /*!
       * \brief Returns display/edit/check-state data for the given \a column and \a role.
       *
       * \details For column 1:
       * - Qt::DisplayRole returns an empty string (the checkbox acts as the display).
       * - Qt::CheckStateRole returns Qt::Checked or Qt::Unchecked based on the current bool value.
       * - Qt::EditRole returns the raw bool wrapped in a QVariant.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const Q_DECL_OVERRIDE;

      /*!
       * \brief Sets the bool value from \a value for the given \a role.
       *
       * \details Accepts Qt::CheckStateRole (Qt::Checked / Qt::Unchecked) and
       * Qt::EditRole (raw bool).  Writes the converted bool to the underlying
       * QMetaProperty and emits valueChanged().
       *
       * \param[in] value The new value; may be a Qt::CheckState or a bool variant.
       * \param[in] role  The role under which to set data; Qt::CheckStateRole or Qt::EditRole.
       * \returns \c true if the value was accepted and written successfully.
       */
      bool setData(const QVariant & value, Qt::ItemDataRole role = Qt::UserRole) Q_DECL_OVERRIDE;

};


#endif // QBOOLPROPERTYITEM_H

