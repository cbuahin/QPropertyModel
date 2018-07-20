/*!
 * \author Caleb Amoa Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * \license
 * This file and its associated files, and libraries are free software.
 * You can redistribute it and/or modify it under the terms of the
 * Lesser GNU Lesser General Public License as published by the Free Software Foundation;
 * either version 3 of the License, or (at your option) any later version.
 * This file and its associated files is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.(see <http://www.gnu.org/licenses/> for details)
 * \copyright Copyright 2014-2018, Caleb Buahin, All rights reserved.
 * \date 2014-2018
 * \pre
 * \bug
 * \warning
 * \todo
 */

#include "stdafx.h"
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

         break;
   }

   return false;
}
