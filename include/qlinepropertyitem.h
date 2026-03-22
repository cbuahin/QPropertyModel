/*!
 * \file qlinepropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for QLine type with expandable P1/P2 children.
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

#ifndef QLINEPROPERTYITEM_H
#define QLINEPROPERTYITEM_H

#include "qvariantpropertyItem.h"

/*!
 * \brief Property item for QLine with P1 and P2 expandable QPoint children.
 *
 * \details The value column displays the line as \c "(x1,y1) -> (x2,y2)".
 * Expanding the item reveals two QPoint child items labelled \b P1 and \b P2,
 * each of which can be further expanded into X and Y components.  Changes to
 * any child are aggregated and written back to the underlying QMetaProperty.
 */
class QLinePropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a line property item.
       *
       * \param[in] value        The initial QLine value wrapped in a QVariant.
       * \param[in] metaProperty The meta-property this item represents on the parent QObject.
       * \param[in] parent       The QObjectClassPropertyItem that owns this item.
       */
      QLinePropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QLinePropertyItem();

      /*!
       * \brief Returns display/edit data for the given \a column and \a role.
       *
       * \details For column 1, Qt::DisplayRole returns \c "(x1,y1) -> (x2,y2)".
       * Qt::EditRole returns the raw QLine wrapped in a QVariant.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      /*!
       * \brief Returns \c true to indicate that P1 and P2 child items exist.
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
       * \details Returns Qt::ItemIsEnabled | Qt::ItemIsSelectable.  Endpoint
       * coordinates are edited through the child point items.
       *
       * \returns Item flags for this node.
       */
      Qt::ItemFlags flags() const override;

   protected:
      /*!
       * \brief Populates or refreshes the P1 and P2 child items.
       *
       * \details Called automatically on first access and whenever the line
       * value changes, keeping children in sync.
       */
      void setChildValues() override;

   private slots:
      /*!
       * \brief Slot invoked when a P1 or P2 child value changes.
       *
       * \details Re-assembles the QLine from the current child values and writes
       * the updated line to the underlying QMetaProperty.
       *
       * \param[in] name  The child property name (\c "P1" or \c "P2").
       * \param[in] value The new QPoint value for that endpoint.
       */
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren; /*!< Guard flag to prevent recursive child-update loops. */

};

#endif // QLINEPROPERTYITEM_H
