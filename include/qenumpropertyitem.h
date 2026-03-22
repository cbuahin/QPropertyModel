/*!
 * \file qenumpropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for Qt enumeration types.
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

#ifndef QENUMPROPERTYITEM_H
#define QENUMPROPERTYITEM_H

#include "qvariantpropertyItem.h"

/*!
 * \brief Property item for Qt enumeration types, displaying the enumerator key name.
 *
 * \details The value column shows the human-readable enumerator key (e.g.
 * \c "AlignLeft") rather than the raw integer.  Editing is provided via a
 * QComboBox populated with all keys of the corresponding QMetaEnum, allowing
 * type-safe selection of the desired enum value.
 */
class QEnumPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs an enum property item.
       *
       * \param[in] value            The initial enum value wrapped in a QVariant.
       * \param[in] metaEnumProperty The QMetaEnum describing the enum type.
       * \param[in] metaProperty     The meta-property this item represents on the parent QObject.
       * \param[in] parent           The QObjectClassPropertyItem that owns this item.
       */
      QEnumPropertyItem(const QVariant& value, const QMetaEnum& metaEnumProperty, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QEnumPropertyItem();

      /*!
       * \brief Returns display/edit data for the given \a column and \a role.
       *
       * \details For column 1, Qt::DisplayRole returns the enumerator key string
       * corresponding to the current integer value (e.g. \c "AlignLeft").
       * Qt::EditRole returns the raw integer wrapped in a QVariant so the
       * delegate's QComboBox can match it by index.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      /*!
       * \brief Returns the QMetaEnum associated with this property item.
       *
       * \details Exposes the enumerator so the delegate can populate its QComboBox
       * with the full list of enumerator keys and their integer values.
       *
       * \returns The QMetaEnum describing the enum type.
       */
      QMetaEnum enumerator() const;

   private:
      QMetaEnum m_metaEnumProperty; /*!< Metadata for the enum type represented by this item. */
};

#endif // QENUMPROPERTYITEM_H
