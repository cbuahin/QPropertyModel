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
#include "qrectpropertyitem.h"
#include "qpropertymodel.h"

QRectPropertyItem::QRectPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
   : QVariantPropertyItem(value, metaProperty, parent), m_isSettingChildren(false)
{

}

QRectPropertyItem::~QRectPropertyItem()
{

}

QVariant QRectPropertyItem::data(int column, Qt::ItemDataRole  role) const
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

               }break;
            case Qt::DisplayRole:
            case Qt::ToolTipRole:
            case Qt::StatusTipRole:
            case Qt::WhatsThisRole:
               {
                  QRect v = qvariant_cast<QRect>(m_metaProperty.read(m_parent->qObject()));
                  QString label = QString("[X=%1, Y=%2, Width=%3, Height=%4]").arg(v.x()).arg(v.y()).arg(v.width()).arg(v.height());
                  return label;
               }
               break;
         }

         break;
   }
   return QVariant();
}


void QRectPropertyItem::setChildValues()
{
   if (!m_isSettingChildren)
   {
      m_isSettingChildren = true;

      QRect v = qvariant_cast<QRect>(m_metaProperty.read(m_parent->qObject()));

      for (int i = 0; i < m_children.count(); i++)
      {
         QPropertyItem* child = m_children[i];
         QString propertyName = child->name();
         QVariant tval;

         if (propertyName == "X")
         {
            tval = v.x();
         }
         else if (propertyName == "Y")
         {
            tval = v.y();
         }
         else if (propertyName == "Width")
         {
            tval = v.width();
         }
         else if (propertyName == "Height")
         {
            tval = v.height();
         }
         m_model->setData(child->index(), tval);
      }


      m_isSettingChildren = false;
   }
}

bool QRectPropertyItem::hasChildren()
{
   if (!m_childrenSet)
   {
      m_childrenSet = true;

      QRect v = qvariant_cast<QRect>(m_metaProperty.read(m_parent->qObject()));

      QPropertyItem* X = new QPropertyItem(v.x(), "X", this);
      m_children.append(X);
      connect(X, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
              SLOT(onChildItemValueChanged(const QString&, const QVariant&)));

      QPropertyItem* Y = new QPropertyItem(v.y(), "Y", this);
      m_children.append(Y);
      connect(Y, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
              SLOT(onChildItemValueChanged(const QString&, const QVariant&)));


      QPropertyItem* width = new QPropertyItem(v.width(), "Width", this);
      m_children.append(width);
      connect(width, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
              SLOT(onChildItemValueChanged(const QString&, const QVariant&)));

      QPropertyItem* height = new QPropertyItem(v.height(), "Height", this);
      m_children.append(height);

      connect(height, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
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

Qt::ItemFlags QRectPropertyItem::flags() const
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

void QRectPropertyItem::onChildItemValueChanged(const QString& name, const QVariant& value)
{
   if (!m_isSettingChildren)
   {
      m_isSettingChildren = true;

      QRect v = qvariant_cast<QRect>(m_metaProperty.read(m_parent->qObject()));

      if (name == "X")
      {
         v.setX(value.toInt());
      }
      else if (name == "Y")
      {
         v.setY(value.toInt());
      }
      else if (name == "Width")
      {
         v.setWidth(value.toInt());
      }
      else if (name == "Height")
      {
         v.setHeight(value.toInt());
      }

      m_model->setData(m_index, v);

      m_isSettingChildren = false;

   }
}
