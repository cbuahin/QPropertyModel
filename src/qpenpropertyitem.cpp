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
#include <QPen>
#include "qpenpropertyitem.h"
#include "qpropertymodel.h"
#include "qchildpropertyitems.h"

QPenPropertyItem::QPenPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
   : QVariantPropertyItem(value, metaProperty, parent), m_isSettingChildren(false)
{

}

QPenPropertyItem::~QPenPropertyItem()
{

}

QVariant QPenPropertyItem::data(int column, Qt::ItemDataRole  role) const
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
               {
                  return  m_metaProperty.read(m_parent->qObject());
               }
               break;
         }

         break;
   }
   return QVariant();
}


void QPenPropertyItem::setChildValues()
{
   if (!m_isSettingChildren)
   {
      m_isSettingChildren = true;

      QPen pen = qvariant_cast<QPen>(m_metaProperty.read(m_parent->qObject()));

      for (int i = 0; i < m_children.count(); i++)
      {
         QPropertyItem* child = m_children[i];
         QString propertyName = child->name();
         QVariant tval;

         if (propertyName == "Width")
         {
            tval = pen.widthF();
         }
         else if (propertyName == "Dash Offset")
         {
            tval = pen.dashOffset();
         }
         else if (propertyName == "Style")
         {
            tval = (int)pen.style();
         }
         else if (propertyName == "Cap Style")
         {
            tval = (int)pen.capStyle();
         }
         else if (propertyName == "Join Style")
         {
            tval = (int)pen.capStyle();
         }
         else if (propertyName == "Brush")
         {
            tval = (int)pen.capStyle();
         }

         m_model->setData(child->index(), tval);
      }


      m_isSettingChildren = false;
   }
}

bool QPenPropertyItem::hasChildren()
{
   if (!m_childrenSet)
   {
      m_childrenSet = true;

      QPen pen = qvariant_cast<QPen>(m_metaProperty.read(m_parent->qObject()));

      QPropertyItem* width = new QPropertyItem(pen.widthF(), "Width", this);
      m_children.append(width);
      connect(width, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
              SLOT(onChildItemValueChanged(const QString&, const QVariant&)));

      QPropertyItem* dashOffset = new QPropertyItem(pen.dashOffset(), "Dash Offset", this);
      m_children.append(dashOffset);
      connect(dashOffset, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
              SLOT(onChildItemValueChanged(const QString&, const QVariant&)));


      int index = staticQtMetaObject.indexOfEnumerator("PenStyle");
      QMetaEnum enumeration = staticQtMetaObject.enumerator(index);
      QChildEnumPropertyItem* penStyle = new QChildEnumPropertyItem((int)pen.style(), "Style", enumeration, this);
      m_children.append(penStyle);
      connect(penStyle, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
              SLOT(onChildItemValueChanged(const QString&, const QVariant&)));


      index = staticQtMetaObject.indexOfEnumerator("PenCapStyle");
      QMetaEnum enumeration1 = staticQtMetaObject.enumerator(index);
      QChildEnumPropertyItem* penCapStyle = new QChildEnumPropertyItem((int)pen.capStyle(), "Cap Style", enumeration1, this);
      m_children.append(penCapStyle);
      connect(penCapStyle, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
              SLOT(onChildItemValueChanged(const QString&, const QVariant&)));


      index = staticQtMetaObject.indexOfEnumerator("PenJoinStyle");
      QMetaEnum enumeration2 = staticQtMetaObject.enumerator(index);
      QChildEnumPropertyItem* penJoinStyle = new QChildEnumPropertyItem((int)pen.joinStyle(), "Join Style", enumeration2, this);
      m_children.append(penJoinStyle);
      connect(penJoinStyle, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
              SLOT(onChildItemValueChanged(const QString&, const QVariant&)));

      QChildBrushPropertyItem* brush = new QChildBrushPropertyItem(pen.brush(), "Brush", this);
      m_children.append(brush);
      connect(brush, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
              SLOT(onChildItemValueChanged(const QString&, const QVariant&)));

      return true;
   }
   else
   {
      if (m_children.count() > 0)
      {
         return true;
      }
   }

   return false;
}

Qt::ItemFlags QPenPropertyItem::flags() const
{
   Qt::ItemFlags  flags;

   if (m_isCheckable)
      flags = flags | Qt::ItemFlag::ItemIsUserCheckable;
   if (m_isEnabled)
      flags = flags | Qt::ItemFlag::ItemIsEnabled;
   //if (m_isEditable)
   //	flags = flags | Qt::ItemFlag::ItemIsEditable;
   if (m_isEnabled)
      flags = flags | Qt::ItemFlag::ItemIsEnabled;
   if (m_isSelectable)
      flags = flags | Qt::ItemFlag::ItemIsSelectable;
   if (m_isTristate)
      flags = flags | Qt::ItemFlag::ItemIsTristate;

   return flags;
}

void QPenPropertyItem::onChildItemValueChanged(const QString& name, const QVariant& value)
{
   if (!m_isSettingChildren)
   {
      m_isSettingChildren = true;

      QPen pen = qvariant_cast<QPen>(m_value);

      if (name == "Width")
      {
         pen.setWidthF(value.toDouble());
      }
      else if (name == "Dash Offset")
      {
         pen.setDashOffset(value.toDouble());
      }
      else if (name == "Style")
      {
         pen.setStyle( (Qt::PenStyle) value.toInt() );
      }
      else if (name == "Cap Style")
      {
         pen.setCapStyle((Qt::PenCapStyle) value.toInt());
      }
      else if (name == "Join Style")
      {
         pen.setJoinStyle((Qt::PenJoinStyle) value.toInt());
      }
      else if (name == "Brush")
      {
         pen.setBrush(qvariant_cast<QBrush>(value));
      }
      m_model->setData(m_index, pen);
      m_isSettingChildren = false;
   }
}
