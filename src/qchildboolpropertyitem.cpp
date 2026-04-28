/*!
 * \file qchildboolpropertyitem.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of QChildBoolPropertyItem.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */


#include "qchildpropertyitems.h"

QChildBoolPropertyItem::QChildBoolPropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent)
   : QPropertyItem(value,name,parent)
{
   m_isEditable = false;
   m_isCheckable = true;
   m_isTristate = false;
}

QChildBoolPropertyItem::~QChildBoolPropertyItem()
{

}

QVariant QChildBoolPropertyItem::data(int column, Qt::ItemDataRole  role) const
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
                     if (m_value.toInt() == 0)
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

bool QChildBoolPropertyItem::setData(const QVariant & value, Qt::ItemDataRole role)
{
   switch (role)
   {
      case Qt::CheckStateRole:
      case Qt::EditRole:

         m_value = qvariant_cast<bool>(value);

         emit valueChanged(m_name, m_value);

         return true;
   }

   return false;
}
