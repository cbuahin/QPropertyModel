/*!
 * \file qimagepropertyitem.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of QImagePropertyItem.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */


#include <QBitmap>
#include "qimagepropertyitem.h"

QImagePropertyItem::QImagePropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
   : QVariantPropertyItem(value, metaProperty , parent)
{

}

QImagePropertyItem::~QImagePropertyItem()
{

}


QVariant QImagePropertyItem::data(int column, Qt::ItemDataRole  role) const
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
               return m_metaProperty.read(m_parent->qObject());
               break;
            case Qt::DecorationRole:
               {
                  QVariant value = m_metaProperty.read(m_parent->qObject());
                  int typeId = value.typeId();
                  if (typeId == QMetaType::QPixmap || typeId == QMetaType::QBitmap)
                     return QIcon(qvariant_cast<QPixmap>(value));
                  else if (typeId == QMetaType::QImage)
                     return QIcon(QPixmap::fromImage(qvariant_cast<QImage>(value)));
                  else if (typeId == QMetaType::QIcon)
                     return qvariant_cast<QIcon>(value);
                  return QVariant();
               }
               break;
         }

         break;
   }
   return QVariant();
}
