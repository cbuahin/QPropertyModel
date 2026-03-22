/*!
 * \file qflagspropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for Qt flags (QFlags<T>) types.
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

#ifndef QFLAGSPROPERTYITEM_H
#define QFLAGSPROPERTYITEM_H

#include "qvariantpropertyItem.h"

/*!
 * \brief Property item for Qt flags types with one QChildBoolPropertyItem per flag bit.
 *
 * \details The value column displays the combined flags value as a
 * comma-separated list of active key names (e.g. \c "Bold, Italic").
 * Expanding the item shows a checkbox child for each individual flag defined
 * in the QMetaEnum, enabling fine-grained per-bit toggling.  Changes to any
 * child checkbox are ORed/ANDed back into the combined flags value and written
 * to the underlying QMetaProperty.
 */
class QFlagsPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a flags property item.
       *
       * \param[in] value            The initial flags value wrapped in a QVariant.
       * \param[in] metaEnumProperty The QMetaEnum describing the flags type.
       * \param[in] metaProperty     The meta-property this item represents on the parent QObject.
       * \param[in] parent           The QObjectClassPropertyItem that owns this item.
       */
      QFlagsPropertyItem(const QVariant& value, const QMetaEnum& metaEnumProperty, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QFlagsPropertyItem();

      /*!
       * \brief Returns display/edit data for the given \a column and \a role.
       *
       * \details For column 1, Qt::DisplayRole returns a comma-separated string
       * listing all flag keys that are currently set.  Qt::EditRole returns the
       * raw integer flags value.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      /*!
       * \brief Returns \c true to indicate that per-flag checkbox children exist.
       *
       * \details Triggers lazy creation of child items via setChildValues() on
       * the first call.
       *
       * \returns Always \c true.
       */
      bool hasChildren() override;

      /*!
       * \brief Returns item flags.
       *
       * \details Returns Qt::ItemIsEnabled | Qt::ItemIsSelectable.  Individual
       * flag bits are toggled through the checkbox child items.
       *
       * \returns Item flags for this node.
       */
      Qt::ItemFlags flags() const override;

      /*!
       * \brief Returns the QMetaEnum associated with this property item.
       *
       * \details Exposes the enumerator so the delegate can determine the full
       * set of flag keys when creating child checkboxes.
       *
       * \returns The QMetaEnum describing the flags type.
       */
      QMetaEnum enumerator() const;

   protected:
      /*!
       * \brief Populates or refreshes one QChildBoolPropertyItem per flag bit.
       *
       * \details Called automatically by hasChildren() on the first call and
       * whenever the flags value changes, keeping child checkboxes in sync.
       */
      void setChildValues() override;

   private slots:
      /*!
       * \brief Slot invoked when a child checkbox value changes.
       *
       * \details Re-computes the combined flags value by OR-ing all checked
       * child bits and writes the result back to the underlying QMetaProperty.
       *
       * \param[in] name  The flag key name of the child that changed.
       * \param[in] value The new checked state (bool wrapped in QVariant).
       */
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      QMetaEnum m_metaEnum;          /*!< Metadata for the flags type represented by this item. */
      bool m_isSettingChildren;      /*!< Guard flag to prevent recursive child-update loops. */
};

#endif // QFLAGSPROPERTYITEM_H
