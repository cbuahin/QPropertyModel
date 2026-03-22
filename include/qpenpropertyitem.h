/*!
 * \file qpenpropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for QPen type with expandable child items.
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

#ifndef QPENPROPERTYITEM_H
#define QPENPROPERTYITEM_H

#include "qvariantpropertyItem.h"

/*!
 * \brief Property item for QPen with expandable children for pen attributes.
 *
 * \details Displays a line preview of the pen colour and style in the value
 * column.  Expanding the item reveals child items for:
 * - **Width** — pen width in pixels (double).
 * - **DashOffset** — the offset into the dash pattern.
 * - **Style** — Qt::PenStyle enum selector.
 * - **CapStyle** — Qt::PenCapStyle enum selector.
 * - **JoinStyle** — Qt::PenJoinStyle enum selector.
 * - **Brush** — the pen brush (expandable QBrush child).
 *
 * Changes to any child are aggregated and written back to the underlying
 * QMetaProperty via onChildItemValueChanged().
 */
class QPenPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a pen property item.
       *
       * \param[in] value        The initial QPen value wrapped in a QVariant.
       * \param[in] metaProperty The meta-property this item represents on the parent QObject.
       * \param[in] parent       The QObjectClassPropertyItem that owns this item.
       */
      QPenPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QPenPropertyItem();

      /*!
       * \brief Returns display/edit data for the given \a column and \a role.
       *
       * \details For column 1, Qt::DecorationRole returns a QPixmap showing a
       * short line drawn with the current pen so the style is visually apparent.
       * Qt::DisplayRole returns an empty string (the decoration acts as display).
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      /*!
       * \brief Returns \c true to indicate that pen attribute children exist.
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
       * \details Returns Qt::ItemIsEnabled | Qt::ItemIsSelectable.  The pen is
       * edited through its child items rather than directly.
       *
       * \returns Item flags for this node.
       */
      Qt::ItemFlags flags() const override;


   protected:
      /*!
       * \brief Populates or refreshes the pen attribute child items.
       *
       * \details Called automatically by hasChildren() the first time it is
       * invoked, and again whenever the pen value changes so child items
       * remain in sync.
       */
      void setChildValues() override;

   private slots:
      /*!
       * \brief Slot invoked when a child item's value changes.
       *
       * \details Re-assembles the QPen from all child values and writes the
       * updated pen back to the underlying QMetaProperty.
       *
       * \param[in] name  The property name of the child that changed.
       * \param[in] value The new value of the changed child.
       */
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren; /*!< Guard flag to prevent recursive child-update loops. */

};

#endif // QPENPROPERTYITEM_H
