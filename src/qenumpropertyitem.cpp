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
#include "qenumpropertyitem.h"

QEnumPropertyItem::QEnumPropertyItem(const QVariant& value, const QMetaEnum& metaEnumProperty, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
  : QVariantPropertyItem(value, metaProperty, parent)
{
  m_metaEnumProperty = metaEnumProperty;
}

QEnumPropertyItem::~QEnumPropertyItem()
{

}

QVariant QEnumPropertyItem::data(int column , Qt::ItemDataRole  role) const
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
            QVariant v = m_metaProperty.read(m_parent->qObject());
            QString name = m_metaEnumProperty.valueToKey(v.toInt());
            return name;
          }
          break;
        case Qt::EditRole:
          return m_metaProperty.read(m_parent->qObject());
          break;
      }

      break;
  }
  return QVariant();
}

QMetaEnum QEnumPropertyItem::enumerator() const
{
  return m_metaEnumProperty;
}
