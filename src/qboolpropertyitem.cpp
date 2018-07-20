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
         if (m_metaProperty.write(m_parent->qObject(), qvariant_cast<bool>(value)))
         {
            m_value = m_metaProperty.read(m_parent->qObject());
            emit valueChanged(m_name, m_value);
            return true;
         }
         break;
   }

   return false;
}
