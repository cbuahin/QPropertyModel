/*!
 * \file qpointfpropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for QPointF type with expandable X/Y children.
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

#ifndef QPOINTFPROPERTYITEM_H
#define QPOINTFPROPERTYITEM_H

#include "qvariantpropertyItem.h"

/*!
 * \brief Property item for QPointF with expandable X and Y children.
 *
 * \details The value column displays the point as \c "(x, y)" with floating-
 * point precision.  Expanding the item reveals two double spin-box children
 * labelled \b X and \b Y.  Changes to either child are aggregated and written
 * back to the underlying QMetaProperty.
 */
class QPointFPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a floating-point point property item.
       *
       * \param[in] value        The initial QPointF value wrapped in a QVariant.
       * \param[in] metaProperty The meta-property this item represents on the parent QObject.
       * \param[in] parent       The QObjectClassPropertyItem that owns this item.
       */
      QPointFPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QPointFPropertyItem();

      /*!
       * \brief Returns display/edit data for the given \a column and \a role.
       *
       * \details For column 1, Qt::DisplayRole returns \c "(x, y)" with
       * floating-point values.  Qt::EditRole returns the raw QPointF.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      /*!
       * \brief Returns \c true to indicate that X and Y child items exist.
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
       * X and Y components are edited through their child items.
       *
       * \returns Item flags for this node.
       */
      Qt::ItemFlags flags() const override;


   protected:
      /*!
       * \brief Populates or refreshes the X and Y child items.
       *
       * \details Called automatically on first access and whenever the point
       * value changes, ensuring children stay synchronised.
       */
      void setChildValues() override;

   private slots:
      /*!
       * \brief Slot invoked when an X or Y child value changes.
       *
       * \details Re-assembles the QPointF from the current child values and
       * writes the updated point to the underlying QMetaProperty.
       *
       * \param[in] name  The child property name (\c "X" or \c "Y").
       * \param[in] value The new floating-point coordinate value.
       */
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren; /*!< Guard flag to prevent recursive child-update loops. */

};

#endif // QPOINTFPROPERTYITEM_H
