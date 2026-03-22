/*!
 * \file qvector3dpropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for QVector3D type with expandable X/Y/Z children.
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

#ifndef QVECTOR3DPROPERTYITEM_H
#define QVECTOR3DPROPERTYITEM_H

#include "qvariantpropertyItem.h"

/*!
 * \brief Property item for QVector3D with expandable X, Y, and Z components.
 *
 * \details The value column displays the vector as \c "(x, y, z)".  Expanding
 * the item reveals three double spin-box children labelled \b X, \b Y, and
 * \b Z.  Changes to any child are aggregated and written back to the underlying
 * QMetaProperty.
 */
class QVector3DPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a 3D vector property item.
       *
       * \param[in] value        The initial QVector3D value wrapped in a QVariant.
       * \param[in] metaProperty The meta-property this item represents on the parent QObject.
       * \param[in] parent       The QObjectClassPropertyItem that owns this item.
       */
      QVector3DPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QVector3DPropertyItem();

      /*!
       * \brief Returns display/edit data for the given \a column and \a role.
       *
       * \details For column 1, Qt::DisplayRole returns \c "(x, y, z)".
       * Qt::EditRole returns the raw QVector3D wrapped in a QVariant.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      /*!
       * \brief Returns \c true to indicate that X, Y, and Z child items exist.
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
       * \details Returns Qt::ItemIsEnabled | Qt::ItemIsSelectable.
       * Individual components are edited through their child items.
       *
       * \returns Item flags for this node.
       */
      Qt::ItemFlags flags() const override;


   protected:
      /*!
       * \brief Populates or refreshes the X, Y, and Z child items.
       *
       * \details Called automatically on first access and whenever the vector
       * value changes, keeping children in sync.
       */
      void setChildValues() override;

   private slots:
      /*!
       * \brief Slot invoked when an X, Y, or Z child value changes.
       *
       * \details Re-assembles the QVector3D from the current child values and
       * writes the updated vector to the underlying QMetaProperty.
       *
       * \param[in] name  The child property name (\c "X", \c "Y", or \c "Z").
       * \param[in] value The new floating-point component value.
       */
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren; /*!< Guard flag to prevent recursive child-update loops. */

};

#endif // QVECTOR3DPROPERTYITEM_H
