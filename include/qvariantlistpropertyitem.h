/*!
 * \file qvariantlistpropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for QVariantList type.
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

#ifndef QVARIANTLISTPROPERTYITEM_H
#define QVARIANTLISTPROPERTYITEM_H

#include "qvariantpropertyItem.h"

/*!
 * \brief Property item for QVariantList, displaying \c "[Count=N]" in the value column.
 *
 * \details The value column summarises the list length as \c "[Count=N]".  Activating
 * the editor opens a modal popup dialog where variants can be inspected and
 * edited individually.
 */
class QVariantListPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a variant-list property item.
       *
       * \param[in] value        The initial QVariantList value wrapped in a QVariant.
       * \param[in] metaProperty The meta-property this item represents on the parent QObject.
       * \param[in] parent       The QObjectClassPropertyItem that owns this item.
       */
      Q_INVOKABLE QVariantListPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QVariantListPropertyItem();

      /*!
       * \brief Returns display/edit data for the given \a column and \a role.
       *
       * \details For column 1, Qt::DisplayRole returns \c "[Count=N]" where N is
       * the number of elements in the list.  Qt::EditRole returns the raw
       * QVariantList so the popup editor can populate its widget.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

};

#endif // QVARIANTLISTPROPERTYITEM_H
