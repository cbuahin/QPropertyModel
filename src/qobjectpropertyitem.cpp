/*!
 * \file qobjectpropertyitem.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of QObjectPropertyItem.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */


#include "qobjectpropertyitem.h"
#include "qobjectclasspropertyitem.h"
#include "qpropertymodel.h"



QObjectPropertyItem::QObjectPropertyItem(QObject* value, const QMetaProperty& prop, QPropertyItem * parent)
   : QPropertyItem(QVariant::fromValue(value), prop.name(), parent), m_hasMetaProperty(false)
{
   if (prop.isValid())
   {
      m_isEditable = prop.isWritable();
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
   m_objectvalues.append(value);
}

QObjectPropertyItem::QObjectPropertyItem(const QList<QObject*>& values, const QMetaProperty& prop, QPropertyItem * parent)
   : QPropertyItem(values.isEmpty() ? QVariant() : QVariant::fromValue(values.first()), prop.name(), parent), m_hasMetaProperty(false)
{
   if (prop.isValid())
   {
      m_isEditable = prop.isWritable();
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
   m_objectvalues = values;
}

QObjectPropertyItem::~QObjectPropertyItem()
{

} 

QVariant QObjectPropertyItem::data(int column , Qt::ItemDataRole role) const
{
   QObject* primary = m_objectvalues.isEmpty() ? nullptr : m_objectvalues.first();
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
               if(primary)
               {
                  return primary->metaObject()->className();
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

int QObjectPropertyItem::rowCount() const
{
   if (!m_childrenSet && !m_objectvalues.isEmpty())
      const_cast<QObjectPropertyItem*>(this)->hasChildren();
   return m_children.count();
}

bool QObjectPropertyItem::hasChildren()
{
   QObject* primary = m_objectvalues.isEmpty() ? nullptr : m_objectvalues.first();
   if (!m_childrenSet && primary)
   {
      const QMetaObject* current = primary->metaObject();

      QList<const QMetaObject*> childMetaObjects;

      childMetaObjects.append(current);

      while ((current = current->superClass()))
      {
         const QMetaObject* temp = current;
         childMetaObjects.insert(0, temp);
      }

      // Hide the inherited QObject class level (which only exposes the
      // objectName property) unless the model has explicitly opted in.
      // QObject is identified as the meta-object with no super-class.
      const bool showQObjectName = m_model ? m_model->showQObjectName() : false;
      if (!showQObjectName)
      {
         for (int i = childMetaObjects.size() - 1; i >= 0; --i)
         {
            if (childMetaObjects.at(i)->superClass() == nullptr)
               childMetaObjects.removeAt(i);
         }
      }

      m_childrenSet = true;

      if (childMetaObjects.count() > 0)
      {
         for (int i = 0; i < childMetaObjects.count(); i++)
         {
            const QMetaObject* metaObject = childMetaObjects[i];
            QObjectClassPropertyItem* propertyItem = new QObjectClassPropertyItem(m_objectvalues, metaObject, this);
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
   return m_objectvalues.isEmpty() ? nullptr : m_objectvalues.first();
}

QList<QObject*> QObjectPropertyItem::qObjects() const
{
   return m_objectvalues;
}
