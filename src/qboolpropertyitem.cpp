/*!
 * \file qboolpropertyitem.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of QBoolPropertyItem.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */


#include "qboolpropertyitem.h"

QBoolPropertyItem::QBoolPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
   : QVariantPropertyItem(value, metaProperty, parent)
{

   m_isEditable = false;
   m_isTristate = false;
   m_isEnabled = m_metaProperty.isReadable();
   m_isCheckable = m_metaProperty.isWritable();
   m_isSelectable = m_metaProperty.isReadable();
   m_canReset = m_metaProperty.isResettable();
}

QBoolPropertyItem::~QBoolPropertyItem()
{

}


QVariant QBoolPropertyItem::data(int column, Qt::ItemDataRole  role) const
{
   switch (column)
   {
      case QPropertyItem::Property:
         {
            switch (role)
            {
               case Qt::DisplayRole:
                  return m_name;
                  break;
            }
         }
         break;
      case QPropertyItem::Value:
         {
            switch (role)
            {
               case Qt::CheckStateRole:
                  {
                     QVariant value = m_metaProperty.read(m_parent->qObject());
                     if (value.toInt() == 0)
                        return Qt::CheckState::Unchecked;
                     else
                        return Qt::CheckState::Checked;
                  }
                  break;
            }
         }
         break;
   }
   return QVariant();
}


bool QBoolPropertyItem::setData(const QVariant & value, Qt::ItemDataRole role)
{
   switch (role)
   {
      case Qt::CheckStateRole:
         if (m_parent->writePropertyToAll(m_metaProperty, qvariant_cast<bool>(value)))
         {
            m_value = m_metaProperty.read(m_parent->qObject());
            emit valueChanged(m_name, m_value);
            return true;
         }
         break;
   }

   return false;
}
