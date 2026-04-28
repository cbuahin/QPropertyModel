/*!
 * \file qtransformpropertyitem.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of QTransformPropertyItem.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */

#include "qtransformpropertyitem.h"
#include "qpropertymodel.h"
#include <QTransform>

QTransformPropertyItem::QTransformPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
   : QVariantPropertyItem(value, metaProperty, parent),
     m_isSettingChildren(false)
{

}

QTransformPropertyItem::~QTransformPropertyItem()
{

}

bool QTransformPropertyItem::hasChildren()
{
   if (!m_childrenSet)
   {
      m_childrenSet = true;

      QTransform transform = qvariant_cast<QTransform>(m_metaProperty.read(m_parent->qObject()));

      // Create child items for all 9 matrix elements
      QString names[] = {"m11", "m12", "m13", "m21", "m22", "m23", "m31", "m32", "m33"};
      qreal values[] = {
         transform.m11(), transform.m12(), transform.m13(),
         transform.m21(), transform.m22(), transform.m23(),
         transform.m31(), transform.m32(), transform.m33()
      };

      for (int i = 0; i < 9; i++)
      {
         QPropertyItem* item = new QPropertyItem(values[i], names[i], this);
         m_children.append(item);
         connect(item, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
                 SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
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

Qt::ItemFlags QTransformPropertyItem::flags() const
{
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void QTransformPropertyItem::onChildItemValueChanged(const QString& name, const QVariant& value)
{
   if (!m_isSettingChildren)
   {
      m_isSettingChildren = true;

      QTransform transform = qvariant_cast<QTransform>(m_metaProperty.read(m_parent->qObject()));
      qreal val = value.toDouble();

      // Update the appropriate matrix element
      if (name == "m11")
         transform.setMatrix(val, transform.m12(), transform.m13(),
                           transform.m21(), transform.m22(), transform.m23(),
                           transform.m31(), transform.m32(), transform.m33());
      else if (name == "m12")
         transform.setMatrix(transform.m11(), val, transform.m13(),
                           transform.m21(), transform.m22(), transform.m23(),
                           transform.m31(), transform.m32(), transform.m33());
      else if (name == "m13")
         transform.setMatrix(transform.m11(), transform.m12(), val,
                           transform.m21(), transform.m22(), transform.m23(),
                           transform.m31(), transform.m32(), transform.m33());
      else if (name == "m21")
         transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                           val, transform.m22(), transform.m23(),
                           transform.m31(), transform.m32(), transform.m33());
      else if (name == "m22")
         transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                           transform.m21(), val, transform.m23(),
                           transform.m31(), transform.m32(), transform.m33());
      else if (name == "m23")
         transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                           transform.m21(), transform.m22(), val,
                           transform.m31(), transform.m32(), transform.m33());
      else if (name == "m31")
         transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                           transform.m21(), transform.m22(), transform.m23(),
                           val, transform.m32(), transform.m33());
      else if (name == "m32")
         transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                           transform.m21(), transform.m22(), transform.m23(),
                           transform.m31(), val, transform.m33());
      else if (name == "m33")
         transform.setMatrix(transform.m11(), transform.m12(), transform.m13(),
                           transform.m21(), transform.m22(), transform.m23(),
                           transform.m31(), transform.m32(), val);

      // Update via model
      m_model->setData(m_index, QVariant::fromValue(transform));

      m_isSettingChildren = false;
   }
}
