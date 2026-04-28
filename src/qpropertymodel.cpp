/*!
 * \file qpropertymodel.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of QPropertyModel.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */


#include "qpropertymodel.h"
#include "qobjectpropertyitem.h"
#include "qpropertyitemdelegate.h"
#include "qobjectlistpropertyitem.h"
#include "qvariantpropertyItem.h"
#include <QDebug>
#include <QFont>
#include <QColor>
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

QPropertyModel::QPropertyModel(QObject* item, QObject* parent)
   : QAbstractItemModel(parent)
{
   m_rootPropertyItem = nullptr;
   m_variantHolder = new QVariantHolderHelper(QVariant(), this);

   int type = (QMetaType::Type) qMetaTypeId< QList<QObject*> >();
   registerCustomPropertyItemType(type, & QObjectListPropertyItem::staticMetaObject);

   if (item)
      setData(QVariant::fromValue(item));
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
   m_objects.clear();

   if (m_rootPropertyItem)
   {
      delete m_rootPropertyItem;
      m_rootPropertyItem = nullptr;
   }


   QObject* qobject = nullptr;

   if (!createRootPropertyItemByType(item.userType(), item))
   {
      QVariantHolderHelper* holder = qvariant_cast<QVariantHolderHelper*>(item);

      if(holder)
      {
         m_variantHolder = holder;
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

void QPropertyModel::setData(const QList<QObject*>& objects)
{
   beginResetModel();

   m_wrapperUsed = false;
   m_objects = objects;

   if (m_rootPropertyItem)
   {
      delete m_rootPropertyItem;
      m_rootPropertyItem = nullptr;
   }

   // Filter out nulls
   QList<QObject*> validObjects;
   for (QObject* obj : objects)
   {
      if (obj)
         validObjects.append(obj);
   }

   if (!validObjects.isEmpty())
   {
      m_rootPropertyItem = new QObjectPropertyItem(validObjects, QMetaProperty(), nullptr);
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
   if (parent.isValid() && parent.column() != 0)
      return 0;

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
         // In multi-object mode, show mixed-value indicator for non-uniform properties
         if (m_objects.size() > 1 && index.column() == 1)
         {
            QVariantPropertyItem* varItem = dynamic_cast<QVariantPropertyItem*>(propertyItem);
            if (varItem && varItem->metaProperty().isValid())
            {
               QObjectClassPropertyItem* classParent = dynamic_cast<QObjectClassPropertyItem*>(varItem->parent());
               if (classParent && !classParent->hasUniformValue(varItem->metaProperty()))
               {
                  if (r == Qt::DisplayRole)
                     return QString("\xe2\x80\x94");  // em dash for mixed values
                  if (r == Qt::FontRole)
                  {
                     QFont f;
                     f.setItalic(true);
                     return f;
                  }
                  if (r == Qt::ForegroundRole)
                     return QColor(Qt::gray);
               }
            }
         }

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
   if (!index.isValid())
      return Qt::ItemIsDropEnabled;

   if (index.column() > 0)
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
   if (parent.isValid() && parent.column() != 0)
      return false;

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

   if (m_rootPropertyItem)
   {
      delete m_rootPropertyItem;
      m_rootPropertyItem = nullptr;
   }

   m_wrapperUsed = false;

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
   else if (m_rootPropertyItem)
      return m_rootPropertyItem->data();
   return QVariant();
}

bool QPropertyModel::registerCustomPropertyItemType(int userType, const QMetaObject* metaObject)
{
   if (!metaObject)
   {
      qWarning() << "QPropertyModel::registerCustomPropertyItemType: metaObject is null";
      return false;
   }

   if (checkIfSuperClassIsPropertyItem(metaObject))
   {
      m_registeredPropertyItems[userType] = metaObject;
      return true;
   }

   qWarning() << "QPropertyModel::registerCustomPropertyItemType:"
              << metaObject->className()
              << "is not a subclass of QPropertyItem";
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

