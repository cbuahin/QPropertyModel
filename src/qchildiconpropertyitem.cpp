/*!
 * \file qchildiconpropertyitem.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of QChildIconPropertyItem.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */

#include "stdafx.h"
#include "qchildpropertyitems.h"
#include <QBitmap>

QChildIconPropertyItem::QChildIconPropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent)
   : QPropertyItem(value, name , parent)
{

}

QChildIconPropertyItem::~QChildIconPropertyItem()
{

}

QVariant QChildIconPropertyItem::data(int column, Qt::ItemDataRole  role) const
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
            case Qt::EditRole:
               return m_value;
               break;
            case Qt::DecorationRole:
               {
                  int typeId = m_value.typeId();
                  if (typeId == QMetaType::QPixmap || typeId == QMetaType::QBitmap)
                     return QIcon(qvariant_cast<QPixmap>(m_value));
                  else if (typeId == QMetaType::QImage)
                     return QIcon(QPixmap::fromImage(qvariant_cast<QImage>(m_value)));
                  else if (typeId == QMetaType::QIcon)
                     return qvariant_cast<QIcon>(m_value);
                  return QVariant();
               }
               break;
         }

         break;
   }
   return QVariant();
}
