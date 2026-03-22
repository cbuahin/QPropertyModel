/*!
 * \file qchildenumpropertyitem.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of QChildEnumPropertyItem.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */

#include "stdafx.h"
#include "qchildpropertyitems.h"

QChildEnumPropertyItem::QChildEnumPropertyItem(const QVariant& value, const QString& name, const QMetaEnum& metaEnum, QPropertyItem * parent)
   : QPropertyItem(value,name, parent)
{
   m_metaEnumProperty = metaEnum;
}

QChildEnumPropertyItem::~QChildEnumPropertyItem()
{

}

QVariant QChildEnumPropertyItem::data(int column, Qt::ItemDataRole  role) const
{
   switch (column)
   {
      case QPropertyItem::Property:
         switch (role)
         {
            case Qt::DisplayRole:
               return m_name;
               break;
         }

         break;
      case QPropertyItem::Value:
         switch (role)
         {
            case Qt::DisplayRole:
            case Qt::ToolTipRole:
            case Qt::StatusTipRole:
            case Qt::WhatsThisRole:
               {
                  QString name = m_metaEnumProperty.valueToKey(m_value.toInt());
                  return name;
               }
               break;
            case Qt::EditRole:
               return m_value;
               break;
         }

         break;
   }
   return QVariant();
}

QMetaEnum QChildEnumPropertyItem::enumerator() const
{
   return m_metaEnumProperty;
}
