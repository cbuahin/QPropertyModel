/*!
 * \file qstringlistpropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for QStringList type with popup editor.
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

#ifndef QSTRINGLISTPROPERTYITEM_H
#define QSTRINGLISTPROPERTYITEM_H

#include "qvariantpropertyItem.h"

/*!
 * \brief Property item for QStringList, displaying \c "[Count=N]" in the value column.
 *
 * \details The value column summarises the list length as \c "[Count=N]" (e.g.
 * \c "[Count=3]").  Activating the editor opens a modal
 * QStringListPropertyItemEditor dialog where strings can be added, removed,
 * reordered, and edited inline.
 */
class QPROPERTYMODEL_EXPORT QStringListPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a string-list property item.
       *
       * \param[in] value        The initial QStringList value wrapped in a QVariant.
       * \param[in] metaProperty The meta-property this item represents on the parent QObject.
       * \param[in] parent       The QObjectClassPropertyItem that owns this item.
       */
      Q_INVOKABLE QStringListPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QStringListPropertyItem();

      /*!
       * \brief Returns display/edit data for the given \a column and \a role.
       *
       * \details For column 1, Qt::DisplayRole returns the string
       * \c "[Count=N]" where N is the number of strings in the list.
       * Qt::EditRole returns the raw QStringList wrapped in a QVariant so the
       * popup editor can populate its list widget.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

};

#endif // QSTRINGLISTPROPERTYITEM_H
