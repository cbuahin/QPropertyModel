/*!
 * \file qtransformpropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for QTransform type with expandable child items.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 * \copyright
 * Copyright 2026, Caleb Buahin, All rights reserved.
 * \date 2014-2026
 */

#ifndef QTRANSFORMPROPERTYITEM_H
#define QTRANSFORMPROPERTYITEM_H

#include "qvariantpropertyItem.h"

/*!
 * \brief Property item for QTransform with expandable children for matrix elements.
 *
 * \details Displays "Transform" in the value column.
 * Expanding the item reveals child items for all 9 matrix elements:
 * - **m11** through **m33** — double values for the 3x3 transformation matrix.
 *
 * Changes to any child are aggregated and written back to the underlying
 * QMetaProperty via onChildItemValueChanged().
 */
class QTransformPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a transform property item.
       *
       * \param[in] value        The initial QTransform value wrapped in a QVariant.
       * \param[in] metaProperty The meta-property this item represents on the parent QObject.
       * \param[in] parent       The QObjectClassPropertyItem that owns this item.
       */
      QTransformPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QTransformPropertyItem();

      /*!
       * \brief Lazily creates child items for the matrix elements.
       *
       * \details Invoked when the item is expanded. Creates nine children
       * for m11, m12, m13, m21, m22, m23, m31, m32, m33.
       *
       * \returns \c true if children exist or were just created; \c false otherwise.
       */
      bool hasChildren() override;

      /*!
       * \brief Returns item flags indicating this item is enabled and selectable.
       *
       * \details Transform items are editable through their children.
       *
       * \returns Qt::ItemFlags bitmask.
       */
      Qt::ItemFlags flags() const override;

   private slots:
      /*!
       * \brief Called when a child item's value has changed.
       *
       * \details Constructs a new QTransform from the updated child values
       * and writes it back to the QObject using the model's setData().
       *
       * \param[in] name  The child item's name (e.g., "m11").
       * \param[in] value The new value for that matrix element.
       */
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren; /*!< Prevents recursive child update loops. */
};

#endif // QTRANSFORMPROPERTYITEM_H
