/*!
 * \file qpolygonpropertyitem.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of QPolygonPropertyItem and QPolygonFPropertyItem.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */

#include "qpolygonpropertyitem.h"
#include "qpointpropertyitem.h"
#include "qpointfpropertyitem.h"
#include "qpropertymodel.h"
#include <QPolygon>
#include <QPolygonF>

// ============================================================================
// QPolygonPropertyItem implementation
// ============================================================================

QPolygonPropertyItem::QPolygonPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
   : QVariantPropertyItem(value, metaProperty, parent),
     m_isSettingChildren(false)
{

}

QPolygonPropertyItem::~QPolygonPropertyItem()
{

}

bool QPolygonPropertyItem::hasChildren()
{
   if (!m_childrenSet)
   {
      m_childrenSet = true;

      QPolygon polygon = qvariant_cast<QPolygon>(m_metaProperty.read(m_parent->qObject()));

      // Create child items for each point
      for (int i = 0; i < polygon.size(); i++)
      {
         QString name = QString("Point %1").arg(i);
         QPropertyItem* item = new QPropertyItem(polygon.at(i), name, this);
         m_children.append(item);
         connect(item, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
                 SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
      }

      return polygon.size() > 0;
   }
   else
   {
      if (m_children.count() > 0)
      {
         return true;
      }
   }

   return false;
}

Qt::ItemFlags QPolygonPropertyItem::flags() const
{
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void QPolygonPropertyItem::onChildItemValueChanged(const QString& name, const QVariant& value)
{
   if (!m_isSettingChildren)
   {
      m_isSettingChildren = true;

      QPolygon polygon = qvariant_cast<QPolygon>(m_metaProperty.read(m_parent->qObject()));
      
      // Extract point index from name (e.g., "Point 0" -> 0)
      int index = name.mid(6).toInt();
      
      if (index >= 0 && index < polygon.size())
      {
         polygon[index] = qvariant_cast<QPoint>(value);

         // Update via model
         m_model->setData(m_index, QVariant::fromValue(polygon));
      }

      m_isSettingChildren = false;
   }
}

// ============================================================================
// QPolygonFPropertyItem implementation
// ============================================================================

QPolygonFPropertyItem::QPolygonFPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
   : QVariantPropertyItem(value, metaProperty, parent),
     m_isSettingChildren(false)
{

}

QPolygonFPropertyItem::~QPolygonFPropertyItem()
{

}

bool QPolygonFPropertyItem::hasChildren()
{
   if (!m_childrenSet)
   {
      m_childrenSet = true;

      QPolygonF polygon = qvariant_cast<QPolygonF>(m_metaProperty.read(m_parent->qObject()));

      // Create child items for each point
      for (int i = 0; i < polygon.size(); i++)
      {
         QString name = QString("Point %1").arg(i);
         QPropertyItem* item = new QPropertyItem(polygon.at(i), name, this);
         m_children.append(item);
         connect(item, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
                 SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
      }

      return polygon.size() > 0;
   }
   else
   {
      if (m_children.count() > 0)
      {
         return true;
      }
   }

   return false;
}

Qt::ItemFlags QPolygonFPropertyItem::flags() const
{
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void QPolygonFPropertyItem::onChildItemValueChanged(const QString& name, const QVariant& value)
{
   if (!m_isSettingChildren)
   {
      m_isSettingChildren = true;

      QPolygonF polygon = qvariant_cast<QPolygonF>(m_metaProperty.read(m_parent->qObject()));
      
      // Extract point index from name (e.g., "Point 0" -> 0)
      int index = name.mid(6).toInt();
      
      if (index >= 0 && index < polygon.size())
      {
         polygon[index] = qvariant_cast<QPointF>(value);

         // Update via model
         m_model->setData(m_index, QVariant::fromValue(polygon));
      }

      m_isSettingChildren = false;
   }
}
