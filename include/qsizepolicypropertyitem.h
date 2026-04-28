/*!
 * \file qsizepolicypropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for QSizePolicy type with expandable child items.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 * \copyright
 * Copyright 2026, Caleb Buahin, All rights reserved.
 * \date 2014-2026
 */

#ifndef QSIZEPOLICYPROPERTYITEM_H
#define QSIZEPOLICYPROPERTYITEM_H

#include "qvariantpropertyItem.h"

/*!
 * \brief Property item for QSizePolicy with expandable children for policy attributes.
 *
 * \details Displays size policy description in the value column.
 * Expanding the item reveals child items for:
 * - **Horizontal Policy** — QSizePolicy::Policy enum selector.
 * - **Vertical Policy** — QSizePolicy::Policy enum selector.
 * - **Horizontal Stretch** — horizontal stretch factor (int).
 * - **Vertical Stretch** — vertical stretch factor (int).
 *
 * Changes to any child are aggregated and written back to the underlying
 * QMetaProperty via onChildItemValueChanged().
 */
class QSizePolicyPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a size policy property item.
       *
       * \param[in] value        The initial QSizePolicy value wrapped in a QVariant.
       * \param[in] metaProperty The meta-property this item represents on the parent QObject.
       * \param[in] parent       The QObjectClassPropertyItem that owns this item.
       */
      QSizePolicyPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QSizePolicyPropertyItem();

      /*!
       * \brief Lazily creates child items for the size policy components.
       *
       * \details Invoked when the item is expanded. Creates four children:
       * horizontal policy, vertical policy, horizontal stretch, and vertical stretch.
       *
       * \returns \c true if children exist or were just created; \c false otherwise.
       */
      bool hasChildren() override;

      /*!
       * \brief Returns item flags indicating this item is enabled and selectable.
       *
       * \details Size policy items are editable through their children.
       *
       * \returns Qt::ItemFlags bitmask.
       */
      Qt::ItemFlags flags() const override;

   private slots:
      /*!
       * \brief Called when a child item's value has changed.
       *
       * \details Constructs a new QSizePolicy from the updated child values
       * and writes it back to the QObject using the model's setData().
       *
       * \param[in] name  The child item's name (e.g., "Horizontal Policy").
       * \param[in] value The new value for that child component.
       */
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren; /*!< Prevents recursive child update loops. */
};

#endif // QSIZEPOLICYPROPERTYITEM_H
