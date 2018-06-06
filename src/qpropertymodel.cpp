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
#include "qpropertymodel.h"
#include "qobjectpropertyitem.h"
#include "qpropertyitemdelegate.h"
#include "qobjectlistpropertyitem.h"
#include <QDebug>
#include <qcustomeditors.h>

int m_windowState(-1000);
QByteArray m_state;
QRect m_geometry;

QMap<int, const QMetaObject*> QPropertyModel::m_registeredPropertyItems = QMap<int, const QMetaObject*>();

QPropertyModel::QPropertyModel(QObject* parent)
   :QAbstractItemModel(parent), m_wrapperUsed(false)
{

   m_rootPropertyItem = nullptr;
   m_variantHolder = new QVariantHolderHelper(QVariant(), this);

   int type = (QMetaType::Type) qMetaTypeId< QList<QObject*> >();
   registerCustomPropertyItemType(type, & QObjectListPropertyItem::staticMetaObject);

}

QPropertyModel::QPropertyModel(const QVariant& item, QObject* parent)
   : QAbstractItemModel(parent)
{
   m_rootPropertyItem = nullptr;
   m_variantHolder = new QVariantHolderHelper(QVariant(), this);

   int type = (QMetaType::Type) qMetaTypeId< QList<QObject*> >();
   registerCustomPropertyItemType(type, & QObjectListPropertyItem::staticMetaObject);

   setData(item);
}

QPropertyModel::~QPropertyModel()
{
   delete m_rootPropertyItem;
}

void QPropertyModel::setData(const QVariant& item)
{
   beginResetModel();

   m_wrapperUsed = false;

   if (m_rootPropertyItem)
   {
      delete m_rootPropertyItem;
      m_rootPropertyItem = nullptr;
   }


   QObject* qobject = nullptr;

   if (!createRootPropertyItemByType(item.userType(), item))
   {
      m_variantHolder = qvariant_cast<QVariantHolderHelper*>(item);

      if(m_variantHolder)
      {
         m_wrapperUsed = true;
         m_rootPropertyItem = new QObjectClassPropertyItem(m_variantHolder, m_variantHolder->metaObject(), nullptr);
      }
      else
      {
         qobject = qvariant_cast<QObject*>(item);

         if (qobject)
         {
            m_rootPropertyItem = new QObjectPropertyItem(qobject, QMetaProperty(), nullptr);
         }
         else if (item.isValid())
         {
            m_wrapperUsed = true;
            m_variantHolder->setValue(item);
            m_rootPropertyItem = new QObjectClassPropertyItem(m_variantHolder, m_variantHolder->metaObject(), nullptr);
         }
      }
   }

   if (m_rootPropertyItem != nullptr)
   {
      m_rootPropertyItem->m_model = this;
   }

   endResetModel();
}

int QPropertyModel::columnCount(const QModelIndex & parent) const
{
   return 2;
}

int QPropertyModel::rowCount(const QModelIndex & parent) const
{

   QPropertyItem* propertyItem = parent.isValid() ? static_cast<QPropertyItem*>(parent.internalPointer()) : m_rootPropertyItem;

   if (propertyItem)
   {
      return propertyItem->rowCount();
   }

   return 0;
}

QVariant QPropertyModel::data(const QModelIndex & index, int role) const
{
   Qt::ItemDataRole r = (Qt::ItemDataRole) role;

   if (index.isValid())
   {
      QPropertyItem* propertyItem = static_cast<QPropertyItem*>(index.internalPointer());

      if (propertyItem)
      {
         return propertyItem->data(index.column(), r);
      }
   }

   return QVariant();
}

bool QPropertyModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
   QPropertyItem* propertyItem = index.isValid() ? static_cast<QPropertyItem*>(index.internalPointer()) : m_rootPropertyItem;

   if (propertyItem)
   {
      if (propertyItem->setData(value, (Qt::ItemDataRole)role))
      {
         emit dataChanged(index, index);

         return true;
      }
   }

   return false;
}

QModelIndex QPropertyModel::index(int row, int column, const QModelIndex & parent) const
{
   QPropertyItem* propertyItem = parent.isValid() ? static_cast<QPropertyItem*>(parent.internalPointer()) : m_rootPropertyItem;

   if (propertyItem && row > -1 && row < propertyItem->rowCount())
   {
      QPropertyItem* child = propertyItem->childPropertyItem(row);
      QModelIndex tempindex;

      if (child->index().isValid() && child->index().column() == column)
      {
         return child->index();
      }
      else
      {
         tempindex = createIndex(row, column, child);

         if (column == 0)
            child->m_index = tempindex;

         return tempindex;
      }
   }

   return QModelIndex();
}

QModelIndex QPropertyModel::parent(const QModelIndex & index) const
{
   if (index.isValid())
   {
      QPropertyItem* propertyItem = static_cast<QPropertyItem*>(index.internalPointer());

      if (propertyItem)
      {
         if (propertyItem->parent())
            return propertyItem->parent()->index();
      }
   }

   return QModelIndex();
}

Qt::ItemFlags QPropertyModel::flags(const QModelIndex & index) const
{
   if (index.isValid() && index.column() > 0)
   {
      QPropertyItem* propertyItem = static_cast<QPropertyItem*>(index.internalPointer());

      if (propertyItem)
      {
         return propertyItem->flags();
      }
   }

   return Qt::ItemFlags(Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsSelectable);
}

QVariant QPropertyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role == 0 && orientation == Qt::Orientation::Horizontal)
   {
      switch (section)
      {
         case 0:
            return "Property";
            break;
         case 1:
            return "Value";
            break;
      }
   }

   return QVariant();
}

bool QPropertyModel::hasChildren(const QModelIndex & parent) const
{
   QPropertyItem* propertyItem = parent.isValid() ? static_cast<QPropertyItem*>(parent.internalPointer()) : m_rootPropertyItem;

   if (propertyItem)
   {
      return propertyItem->hasChildren();
   }

   return false;
}

void QPropertyModel::clear()
{
   beginResetModel();

   setData(QVariant());

   endResetModel();
}

QPropertyItem* QPropertyModel::rootPropertyItem() const
{
   return m_rootPropertyItem;
}

QVariant QPropertyModel::rootQVariantItem() const
{
   if (m_wrapperUsed)
      return m_variantHolder->value();
   else
      return m_rootPropertyItem->data() ;
}

bool QPropertyModel::registerCustomPropertyItemType(int userType, const QMetaObject* metaObject)
{
   if (checkIfSuperClassIsPropertyItem(metaObject))
   {
      m_registeredPropertyItems[userType] = metaObject;
      return true;
   }

   return false;
}

void QPropertyModel::onDataChanged(const QModelIndex & index)
{
   emit dataChanged(index, index);
}

bool QPropertyModel::checkIfSuperClassIsPropertyItem(const QMetaObject* metaObject)
{
   if (metaObject->superClass())
   {
      const QMetaObject* superClass = metaObject->superClass();

      if (!QString(superClass->className()).compare(QPropertyItem::staticMetaObject.className(), Qt::CaseSensitive))
      {
         return true;
      }
      else
      {
         if (superClass->superClass())
         {
            return checkIfSuperClassIsPropertyItem(superClass);
         }
      }
   }

   return false;
}

bool QPropertyModel::createRootPropertyItemByType(int userType, const QVariant& item)
{
   if (m_registeredPropertyItems.contains(userType))
   {
      QObject* object = qvariant_cast<QObject*>(item);

      if(object)
      {
         if (m_rootPropertyItem)
         {
            delete m_rootPropertyItem;
            m_rootPropertyItem = nullptr;
         }

         const QMetaObject* metaObject = QPropertyModel::m_registeredPropertyItems[userType];
         m_rootPropertyItem = (QVariantPropertyItem*)metaObject->newInstance(Q_ARG(const QVariant&, item), Q_ARG(const QMetaProperty&, QMetaProperty()), Q_ARG(QObjectClassPropertyItem*, nullptr));
      }
      else
      {
         m_wrapperUsed = true;
         m_variantHolder->setValue(item);
         m_rootPropertyItem = new QObjectClassPropertyItem(m_variantHolder, m_variantHolder->metaObject(), nullptr);
      }

      if (m_rootPropertyItem != nullptr)
      {
         return true;
      }
   }

   return false;
}

QPropertyItem* QPropertyModel::createPropertyItemByType(int userType, const QVariant& item, const QMetaProperty& property, QPropertyItem * parent)
{
   QPropertyItem* propItem = nullptr;

   if (m_registeredPropertyItems.contains(userType))
   {
      const QMetaObject* metaObject = m_registeredPropertyItems[userType];

      qDebug() << metaObject->className();

      propItem = (QPropertyItem*)metaObject->newInstance(Q_ARG(const QVariant&, item), Q_ARG(const QMetaProperty&, property), Q_ARG(QPropertyItem*, parent));

      if(!propItem && static_cast<QObjectClassPropertyItem*>(parent))
      {
         propItem = (QPropertyItem*)metaObject->newInstance(Q_ARG(const QVariant&, item), Q_ARG(const QMetaProperty&, property), Q_ARG(QObjectClassPropertyItem*, static_cast<QObjectClassPropertyItem*>(parent)));
      }

      return propItem;
   }

   return propItem;
}

