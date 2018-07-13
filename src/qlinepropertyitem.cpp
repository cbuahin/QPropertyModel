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
#include "qlinepropertyitem.h"
#include "qpropertymodel.h"
#include "qchildpropertyitems.h"

QLinePropertyItem::QLinePropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
   : QVariantPropertyItem(value, metaProperty, parent), m_isSettingChildren(false)
{

}

QLinePropertyItem::~QLinePropertyItem()
{

}

QVariant QLinePropertyItem::data(int column, Qt::ItemDataRole  role) const
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
                  QLine v = qvariant_cast<QLine>(m_metaProperty.read(m_parent->qObject()));
                  QString label = QString("P1=[X=%1, Y=%2], P2=[X=%3, Y=%4]").arg(v.p1().x()).arg(v.p1().y()).arg(v.p2().x()).arg(v.p2().y());
                  return label;
               }
               break;
         }

         break;
   }
   return QVariant();
}

void QLinePropertyItem::setChildValues()
{
   if (!m_isSettingChildren)
   {
      m_isSettingChildren = true;

      QLine line = qvariant_cast<QLine>(m_metaProperty.read(m_parent->qObject()));

      for (int i = 0; i < m_children.count(); i++)
      {
         QPropertyItem* child = m_children[i];
         QString propertyName = child->name();
         QVariant tval;

         if (propertyName == "P1")
         {
            tval = line.p1();
         }
         else if (propertyName == "P2")
         {
            tval = line.p2();
         }


         m_model->setData(child->index(), tval);
      }


      m_isSettingChildren = false;
   }
}

bool QLinePropertyItem::hasChildren()
{
   if (!m_childrenSet)
   {
      m_childrenSet = true;

      QLine line = qvariant_cast<QLine>(m_metaProperty.read(m_parent->qObject()));

      QChildPointPropertyItem* p1 = new QChildPointPropertyItem(qvariant_cast<QVariant>(line.p1()), "P1", this);
      m_children.append(p1);
      connect(p1, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
              SLOT(onChildItemValueChanged(const QString&, const QVariant&)));


      QChildPointPropertyItem* p2 = new QChildPointPropertyItem(qvariant_cast<QVariant>(line.p1()), "P2", this);
      m_children.append(p2);
      connect(p2, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
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

Qt::ItemFlags QLinePropertyItem::flags() const
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

void QLinePropertyItem::onChildItemValueChanged(const QString& name, const QVariant& value)
{
   if (!m_isSettingChildren)
   {
      m_isSettingChildren = true;

      QLine line = qvariant_cast<QLine>(m_metaProperty.read(m_parent->qObject()));

      if (name == "P1")
      {
         line.setP1(qvariant_cast<QPoint>(value));
      }
      else if (name == "P2")
      {
         line.setP2(qvariant_cast<QPoint>(value));
      }

      m_model->setData(m_index, line);

      m_isSettingChildren = false;

   }
}
