/*!
 * \file qsizepolicypropertyitem.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of QSizePolicyPropertyItem.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */

#include "qsizepolicypropertyitem.h"
#include "qchildpropertyitems.h"
#include "qpropertymodel.h"
#include <QSizePolicy>

QSizePolicyPropertyItem::QSizePolicyPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
   : QVariantPropertyItem(value,metaProperty, parent),
     m_isSettingChildren(false)
{

}

QSizePolicyPropertyItem::~QSizePolicyPropertyItem()
{

}

bool QSizePolicyPropertyItem::hasChildren()
{
   if (!m_childrenSet)
   {
      m_childrenSet = true;

      QSizePolicy policy = qvariant_cast<QSizePolicy>(m_metaProperty.read(m_parent->qObject()));

      // Horizontal Policy
      int index = QSizePolicy::staticMetaObject.indexOfEnumerator("Policy");
      QMetaEnum policyEnum = QSizePolicy::staticMetaObject.enumerator(index);
      QChildEnumPropertyItem* hPolicy = new QChildEnumPropertyItem((int)policy.horizontalPolicy(), "Horizontal Policy", policyEnum, this);
      m_children.append(hPolicy);
      connect(hPolicy, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
              SLOT(onChildItemValueChanged(const QString&, const QVariant&)));

      // Vertical Policy
      QChildEnumPropertyItem* vPolicy = new QChildEnumPropertyItem((int)policy.verticalPolicy(), "Vertical Policy", policyEnum, this);
      m_children.append(vPolicy);
      connect(vPolicy, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
              SLOT(onChildItemValueChanged(const QString&, const QVariant&)));

      // Horizontal Stretch
      QPropertyItem* hStretch = new QPropertyItem(policy.horizontalStretch(), "Horizontal Stretch", this);
      m_children.append(hStretch);
      connect(hStretch, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
              SLOT(onChildItemValueChanged(const QString&, const QVariant&)));

      // Vertical Stretch
      QPropertyItem* vStretch = new QPropertyItem(policy.verticalStretch(), "Vertical Stretch", this);
      m_children.append(vStretch);
      connect(vStretch, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
              SLOT(onChildItemValueChanged(const QString&, const QVariant&)));

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

Qt::ItemFlags QSizePolicyPropertyItem::flags() const
{
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void QSizePolicyPropertyItem::onChildItemValueChanged(const QString& name, const QVariant& value)
{
   if (!m_isSettingChildren)
   {
      m_isSettingChildren = true;

      QSizePolicy policy = qvariant_cast<QSizePolicy>(m_metaProperty.read(m_parent->qObject()));

      if (name == "Horizontal Policy")
      {
         policy.setHorizontalPolicy((QSizePolicy::Policy)value.toInt());
      }
      else if (name == "Vertical Policy")
      {
         policy.setVerticalPolicy((QSizePolicy::Policy)value.toInt());
      }
      else if (name == "Horizontal Stretch")
      {
         policy.setHorizontalStretch(value.toInt());
      }
      else if (name == "Vertical Stretch")
      {
         policy.setVerticalStretch(value.toInt());
      }

      // Update via model
      m_model->setData(m_index, QVariant::fromValue(policy));

      m_isSettingChildren = false;
   }
}
