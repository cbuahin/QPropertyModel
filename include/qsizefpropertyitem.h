/*!
 * \file qsizefpropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for QSizeF type with expandable Width/Height children.
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

#ifndef QSIZEFPROPERTYITEM_H
#define QSIZEFPROPERTYITEM_H

#include "qvariantpropertyItem.h"

/*!
 * \brief Property item for QSizeF with expandable Width and Height children.
 *
 * \details The value column displays the size as \c "w x h" with floating-
 * point precision.  Expanding the item reveals two double spin-box children
 * labelled \b Width and \b Height.  Changes to either child are aggregated
 * and written back to the underlying QMetaProperty.
 */
class QSizeFPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a floating-point size property item.
       *
       * \param[in] value        The initial QSizeF value wrapped in a QVariant.
       * \param[in] metaProperty The meta-property this item represents on the parent QObject.
       * \param[in] parent       The QObjectClassPropertyItem that owns this item.
       */
      QSizeFPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QSizeFPropertyItem();

      /*!
       * \brief Returns display/edit data for the given \a column and \a role.
       *
       * \details For column 1, Qt::DisplayRole returns \c "w x h" with
       * floating-point values.  Qt::EditRole returns the raw QSizeF.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      /*!
       * \brief Returns \c true to indicate that Width and Height child items exist.
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
       * dimensions are edited through their child items.
       *
       * \returns Item flags for this node.
       */
      Qt::ItemFlags flags() const override;


   protected:
      /*!
       * \brief Populates or refreshes the Width and Height child items.
       *
       * \details Called automatically on first access and whenever the size
       * value changes, keeping children in sync.
       */
      void setChildValues() override;

   private slots:
      /*!
       * \brief Slot invoked when a Width or Height child value changes.
       *
       * \details Re-assembles the QSizeF from the current child values and writes
       * the updated size to the underlying QMetaProperty.
       *
       * \param[in] name  The child property name (\c "Width" or \c "Height").
       * \param[in] value The new floating-point dimension value.
       */
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren; /*!< Guard flag to prevent recursive child-update loops. */

};

#endif // QSIZEFPROPERTYITEM_H
