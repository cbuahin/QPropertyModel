/*!
 * \author Caleb Amoa Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * \license
 * This file and its associated files, and libraries are free software.
 * You can redistribute it and/or modify it under the terms of the
 * Lesser GNU General Public License as published by the Free Software Foundation;
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
#include "qobjectpropertyitem.h"
#include "qobjectclasspropertyitem.h"



QObjectPropertyItem::QObjectPropertyItem(QObject* value, const QMetaProperty& prop, QPropertyItem * parent)
   : QPropertyItem(QVariant::fromValue(value), prop.name(), parent), m_hasMetaProperty(false)
{
   if (prop.isValid())
   {
      m_isEditable = prop.isEditable();
      m_canReset = prop.isResettable();
      m_property = prop;
      m_hasMetaProperty = true;

   }
   else
   {
      m_isEnabled = true;
      m_isEditable = true;
      m_isSelectable = true;
   }
   m_objectvalue = value;
}

QObjectPropertyItem::~QObjectPropertyItem()
{

} 

QVariant QObjectPropertyItem::data(int column , Qt::ItemDataRole role) const
{
   switch (column)
   {
      case QPropertyItem::Property:
         switch (role)
         {
            case Qt::DisplayRole:
               {
                  return m_name;
               }
               break;
         }
         break;
      case QPropertyItem::Value:
         switch (role)
         {
            case Qt::DisplayRole:
               if(m_objectvalue)
               {
                  return QVariant();
                  return m_objectvalue->metaObject()->className();
               }
               break;
         }
         break;
   }
   return QVariant();
}



bool QObjectPropertyItem::setData(const QVariant & value, Qt::ItemDataRole role)
{
   switch (role)
   {
      case Qt::EditRole:
         {
            m_value = value;
            emit valueChanged(m_name, m_value);
         }
         break;
   }
   return false;
}

bool QObjectPropertyItem::hasChildren()
{
   if (!m_childrenSet && m_objectvalue)
   {
      const QMetaObject* current = m_objectvalue->metaObject() ;

      QList<const QMetaObject*> childMetaObjects;

      childMetaObjects.append(current);

      while ((current = current->superClass()))
      {
         const QMetaObject* temp = current;
         childMetaObjects.insert(0, temp);
      }

      //childMetaObjects.removeFirst();

      m_childrenSet = true;

      if (childMetaObjects.count() > 0)
      {
         for (int i = 0; i < childMetaObjects.count(); i++)
         {
            const QMetaObject* metaObject = childMetaObjects[i];
            QObjectClassPropertyItem* propertyItem = new QObjectClassPropertyItem(m_objectvalue, metaObject, this);
            m_children.append(propertyItem);
         }

         return true;
      }
   }
   else if (m_children.count() > 0)
   {
      return true;
   }

   return false;
}

QObject* QObjectPropertyItem::qObject() const
{
   return m_objectvalue;
}
