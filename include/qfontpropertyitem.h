/*!
 * \file qfontpropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for QFont type with expandable children.
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

#ifndef QFONTPROPERTYITEM_H
#define QFONTPROPERTYITEM_H

#include "qvariantpropertyItem.h"

/*!
 * \brief Property item for QFont with expandable child items.
 *
 * \details Creates sub-children for the most commonly edited QFont attributes:
 * - **Family** — font family name (string combo-box).
 * - **PointSize** — point size (integer spin-box).
 * - **Bold** — bold weight flag (checkbox).
 * - **Italic** — italic style flag (checkbox).
 * - **Underline** — underline decoration flag (checkbox).
 * - **StrikeOut** — strike-out decoration flag (checkbox).
 * - **Kerning** — kerning enable flag (checkbox).
 *
 * The value column displays the font's family name and size as a decorative
 * preview using the font itself.
 */
class QFontPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a font property item.
       *
       * \param[in] value        The initial QFont value wrapped in a QVariant.
       * \param[in] metaProperty The meta-property this item represents on the parent QObject.
       * \param[in] parent       The QObjectClassPropertyItem that owns this item.
       */
      QFontPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QFontPropertyItem();

      /*!
       * \brief Returns display/edit data for the given \a column and \a role.
       *
       * \details For column 1, Qt::DisplayRole returns a string of the form
       * "Family [PointSize pt]", rendered in the font itself (Qt::FontRole).
       * Qt::EditRole returns the raw QFont wrapped in a QVariant.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      /*!
       * \brief Returns \c true to indicate that font attribute children exist.
       *
       * \details Triggers lazy creation of child items via setChildValues() on
       * the first call.
       *
       * \returns Always \c true.
       */
      bool hasChildren() override;

   protected:
      /*!
       * \brief Populates or refreshes the font attribute child items.
       *
       * \details Called automatically by hasChildren() on the first call and
       * again whenever the font value changes, keeping child items in sync.
       */
      void setChildValues() override;

   private slots:
      /*!
       * \brief Slot invoked when a child item's value changes.
       *
       * \details Re-assembles the QFont from all child values and writes the
       * updated font back to the underlying QMetaProperty.
       *
       * \param[in] name  The property name of the child that changed.
       * \param[in] value The new value of the changed child.
       */
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      void updateChildEnabledStates(const QString& family);

      bool m_settingChildren; /*!< Guard flag to prevent recursive child-update loops. */
};

#endif // QFONTPROPERTYITEM_H
