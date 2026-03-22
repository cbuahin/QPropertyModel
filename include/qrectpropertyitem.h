/*!
 * \file qrectpropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for QRect type with expandable coordinate children.
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

#ifndef QRECTPROPERTYITEM_H
#define QRECTPROPERTYITEM_H

#include "qvariantpropertyItem.h"

/*!
 * \brief Property item for QRect with expandable X, Y, Width, and Height children.
 *
 * \details The value column displays the rectangle as \c "[x, y, w x h]".
 * Expanding the item reveals four integer spin-box children labelled
 * \b X, \b Y, \b Width, and \b Height.  Changes to any child are aggregated
 * and written back to the underlying QMetaProperty.
 */
class QRectPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a rectangle property item.
       *
       * \param[in] value        The initial QRect value wrapped in a QVariant.
       * \param[in] metaProperty The meta-property this item represents on the parent QObject.
       * \param[in] parent       The QObjectClassPropertyItem that owns this item.
       */
      QRectPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
     virtual ~QRectPropertyItem();

      /*!
       * \brief Returns display/edit data for the given \a column and \a role.
       *
       * \details For column 1, Qt::DisplayRole returns \c "[x, y, w x h]".
       * Qt::EditRole returns the raw QRect wrapped in a QVariant.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      /*!
       * \brief Returns \c true to indicate that X, Y, Width, Height children exist.
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
       * components are edited through their child items.
       *
       * \returns Item flags for this node.
       */
      Qt::ItemFlags flags() const override;

   protected:
      /*!
       * \brief Populates or refreshes the X, Y, Width, and Height child items.
       *
       * \details Called automatically on first access and whenever the rect
       * value changes, keeping children in sync.
       */
      void setChildValues() override;

   private slots:
      /*!
       * \brief Slot invoked when any child value changes.
       *
       * \details Re-assembles the QRect from the current child values and writes
       * the updated rectangle to the underlying QMetaProperty.
       *
       * \param[in] name  The child property name (\c "X", \c "Y", \c "Width", or \c "Height").
       * \param[in] value The new integer coordinate or dimension value.
       */
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren; /*!< Guard flag to prevent recursive child-update loops. */

};

#endif // QRECTPROPERTYITEM_H
