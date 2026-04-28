/*!
 * \file qmatrix4x4propertyitem.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of QMatrix4x4PropertyItem.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */

#include "qmatrix4x4propertyitem.h"
#include "qpropertymodel.h"
#include <QMatrix4x4>

QMatrix4x4PropertyItem::QMatrix4x4PropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
   : QVariantPropertyItem(value, metaProperty, parent),
     m_isSettingChildren(false)
{

}

QMatrix4x4PropertyItem::~QMatrix4x4PropertyItem()
{

}

bool QMatrix4x4PropertyItem::hasChildren()
{
   if (!m_childrenSet)
   {
      m_childrenSet = true;

      QMatrix4x4 matrix = qvariant_cast<QMatrix4x4>(m_metaProperty.read(m_parent->qObject()));

      // Create child items for all 16 matrix elements
      for (int row = 1; row <= 4; row++)
      {
         for (int col = 1; col <= 4; col++)
         {
            QString name = QString("m%1%2").arg(row).arg(col);
            float value = matrix(row-1, col-1);
            QPropertyItem* item = new QPropertyItem(value, name, this);
            m_children.append(item);
            connect(item, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
                    SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
         }
      }

      return true;
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

Qt::ItemFlags QMatrix4x4PropertyItem::flags() const
{
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void QMatrix4x4PropertyItem::onChildItemValueChanged(const QString& name, const QVariant& value)
{
   if (!m_isSettingChildren)
   {
      m_isSettingChildren = true;

      QMatrix4x4 matrix = qvariant_cast<QMatrix4x4>(m_metaProperty.read(m_parent->qObject()));
      float val = value.toFloat();

      // Extract row and column from name (e.g., "m12" -> row=1, col=2)
      int row = name.mid(1, 1).toInt() - 1;
      int col = name.mid(2, 1).toInt() - 1;

      matrix(row, col) = val;

      // Update via model
      m_model->setData(m_index, QVariant::fromValue(matrix));

      m_isSettingChildren = false;
   }
}
