/*!
 * \file qpolygonpropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for QPolygon/QPolygonF types with expandable child items.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 * \copyright
 * Copyright 2026, Caleb Buahin, All rights reserved.
 * \date 2014-2026
 */

#ifndef QPOLYGONPROPERTYITEM_H
#define QPOLYGONPROPERTYITEM_H

#include "qvariantpropertyItem.h"

/*!
 * \brief Property item for QPolygon with expandable children for each point.
 *
 * \details Displays point count in the value column (e.g., "[3 points]").
 * Expanding the item reveals child items for each point:
 * - **Point 0**, **Point 1**, etc. — QPoint values that expand to x,y children.
 *
 * Changes to any child point are aggregated and written back to the underlying
 * QMetaProperty via onChildItemValueChanged().
 */
class QPolygonPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a polygon property item.
       *
       * \param[in] value        The initial QPolygon value wrapped in a QVariant.
       * \param[in] metaProperty The meta-property this item represents on the parent QObject.
       * \param[in] parent       The QObjectClassPropertyItem that owns this item.
       */
      QPolygonPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QPolygonPropertyItem();

      /*!
       * \brief Lazily creates child items for each polygon point.
       *
       * \details Invoked when the item is expanded. Creates a child item
       * for each point in the polygon.
       *
       * \returns \c true if children exist or were just created; \c false otherwise.
       */
      bool hasChildren() override;

      /*!
       * \brief Returns item flags indicating this item is enabled and selectable.
       *
       * \details Polygon items are editable through their children.
       *
       * \returns Qt::ItemFlags bitmask.
       */
      Qt::ItemFlags flags() const override;

   private slots:
      /*!
       * \brief Called when a child item's value has changed.
       *
       * \details Constructs a new QPolygon from the updated child values
       * and writes it back to the QObject using the model's setData().
       *
       * \param[in] name  The child item's name (e.g., "Point 0").
       * \param[in] value The new QPoint value for that point.
       */
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren; /*!< Prevents recursive child update loops. */
};


/*!
 * \brief Property item for QPolygonF with expandable children for each point.
 *
 * \details Displays point count in the value column (e.g., "[3 points]").
 * Expanding the item reveals child items for each point:
 * - **Point 0**, **Point 1**, etc. — QPointF values that expand to x,y children.
 *
 * Changes to any child point are aggregated and written back to the underlying
 * QMetaProperty via onChildItemValueChanged().
 */
class QPolygonFPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a polygonF property item.
       *
       * \param[in] value        The initial QPolygonF value wrapped in a QVariant.
       * \param[in] metaProperty The meta-property this item represents on the parent QObject.
       * \param[in] parent       The QObjectClassPropertyItem that owns this item.
       */
      QPolygonFPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QPolygonFPropertyItem();

      /*!
       * \brief Lazily creates child items for each polygon point.
       *
       * \details Invoked when the item is expanded. Creates a child item
       * for each point in the polygon.
       *
       * \returns \c true if children exist or were just created; \c false otherwise.
       */
      bool hasChildren() override;

      /*!
       * \brief Returns item flags indicating this item is enabled and selectable.
       *
       * \details PolygonF items are editable through their children.
       *
       * \returns Qt::ItemFlags bitmask.
       */
      Qt::ItemFlags flags() const override;

   private slots:
      /*!
       * \brief Called when a child item's value has changed.
       *
       * \details Constructs a new QPolygonF from the updated child values
       * and writes it back to the QObject using the model's setData().
       *
       * \param[in] name  The child item's name (e.g., "Point 0").
       * \param[in] value The new QPointF value for that point.
       */
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren; /*!< Prevents recursive child update loops. */
};

#endif // QPOLYGONPROPERTYITEM_H
