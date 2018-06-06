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
#include "qiconpropertyitem.h"
#include "qchildpropertyitems.h"
#include "qpropertymodel.h"

QIconPropertyItem::QIconPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
   : QVariantPropertyItem(value, metaProperty, parent), m_isSettingChildren(false)
{

}

QIconPropertyItem::~QIconPropertyItem()
{

}

QVariant QIconPropertyItem::data(int column, Qt::ItemDataRole  role) const
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
            case Qt::DecorationRole:
               return m_metaProperty.read(m_parent->qObject());
               break;
         }

         break;
   }
   return QVariant();
}


void QIconPropertyItem::setChildValues()
{
   if (!m_isSettingChildren)
   {
      m_isSettingChildren = true;

      m_value = m_metaProperty.read(m_parent->qObject());
      QIcon currentIcon = qvariant_cast<QIcon>(m_value);

      QSize outrageousSize = QSize(5000, 5000);

      for (int i = 0; i < m_children.count(); i++)
      {
         QPropertyItem* child = m_children[i];
         QString propertyName = child->name();
         QVariant tval;

         if (propertyName == "Normal On")
         {
            tval = currentIcon.pixmap(outrageousSize, QIcon::Mode::Normal, QIcon::State::On);
         }
         else if (propertyName == "Normal Off")
         {
            tval = currentIcon.pixmap(outrageousSize, QIcon::Mode::Normal, QIcon::State::Off);
         }
         else if (propertyName == "Active On")
         {
            tval = currentIcon.pixmap(outrageousSize, QIcon::Mode::Active, QIcon::State::On);
         }
         else if (propertyName == "Active Off")
         {
            tval = currentIcon.pixmap(outrageousSize, QIcon::Mode::Active, QIcon::State::Off);
         }
         else if (propertyName == "Selected On")
         {
            tval = currentIcon.pixmap(outrageousSize, QIcon::Mode::Selected, QIcon::State::On);
         }
         else if (propertyName == "Selected Off")
         {
            tval = currentIcon.pixmap(outrageousSize, QIcon::Mode::Selected, QIcon::State::Off);
         }
         else if (propertyName == "Disabled On")
         {
            tval = currentIcon.pixmap(outrageousSize, QIcon::Mode::Disabled, QIcon::State::On);
         }
         else if (propertyName == "Disabled Off")
         {
            tval = currentIcon.pixmap(outrageousSize, QIcon::Mode::Disabled, QIcon::State::Off);
         }

         m_model->setData(child->index(), tval);
      }


      m_isSettingChildren = false;
   }
}

bool QIconPropertyItem::hasChildren()
{
   if (!m_childrenSet)
   {
      m_childrenSet = true;

      m_value = m_metaProperty.read(m_parent->qObject());
      QIcon currentIcon = qvariant_cast<QIcon>(m_value);

      if (m_value.isValid())
      {
         QSize outrageousSize = QSize(5000, 5000);

         for (int i = 0; i < 8; i++)
         {

            switch (i)
            {
               case 0:
                  {
                     QString propName = "Normal On";
                     QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Normal, QIcon::State::On);
                     QChildIconPropertyItem* tempProp = new QChildIconPropertyItem(pixvalue, propName, this);
                     m_children.append(tempProp);

                     connect(tempProp, SIGNAL(valueChanged(const QString&,const QVariant&)), this,
                             SLOT(onChildItemValueChanged(const QString&,const QVariant&)));
                  }
                  break;
               case 1:
                  {
                     QString propName = "Normal Off";
                     QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Normal, QIcon::State::Off);
                     QChildIconPropertyItem* tempProp = new QChildIconPropertyItem(pixvalue, propName, this);
                     m_children.append(tempProp);

                     connect(tempProp, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
                             SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
                  }
                  break;
               case 2:
                  {
                     QString propName = "Active On";
                     QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Active, QIcon::State::On);
                     QChildIconPropertyItem* tempProp = new QChildIconPropertyItem(pixvalue, propName, this);
                     m_children.append(tempProp);
                     connect(tempProp, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
                             SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
                  }
                  break;
               case 3:
                  {
                     QString propName = "Active Off";
                     QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Active, QIcon::State::Off);
                     QChildIconPropertyItem* tempProp = new QChildIconPropertyItem(pixvalue, propName, this);
                     m_children.append(tempProp);

                     connect(tempProp, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
                             SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
                  }
                  break;
               case 4:
                  {
                     QString propName = "Selected On";
                     QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Selected, QIcon::State::On);
                     QChildIconPropertyItem* tempProp = new QChildIconPropertyItem(pixvalue, propName, this);
                     m_children.append(tempProp);
                     connect(tempProp, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
                             SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
                  }
                  break;
               case 5:
                  {
                     QString propName = "Selected Off";
                     QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Selected, QIcon::State::Off);
                     QChildIconPropertyItem* tempProp = new QChildIconPropertyItem(pixvalue, propName, this);
                     m_children.append(tempProp);
                     connect(tempProp, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
                             SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
                  }
                  break;
               case 6:
                  {
                     QString propName = "Disabled On";
                     QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Disabled, QIcon::State::On);
                     QChildIconPropertyItem* tempProp = new QChildIconPropertyItem(pixvalue, propName, this);
                     m_children.append(tempProp);

                     connect(tempProp, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
                             SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
                  }
                  break;
               case 7:
                  {
                     QString propName = "Disabled Off";
                     QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Disabled, QIcon::State::Off);
                     QChildIconPropertyItem* tempProp = new QChildIconPropertyItem(pixvalue, propName, this);
                     m_children.append(tempProp);

                     connect(tempProp, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
                             SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
                  }
                  break;
            }
         }

         return true;
      }
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


void QIconPropertyItem::onChildItemValueChanged(const QString& name, const QVariant& value)
{
   if (!m_isSettingChildren)
   {
      m_isSettingChildren = true;

      m_value = m_metaProperty.read(m_parent->qObject());
      QIcon icon = qvariant_cast<QIcon>(m_value);


      QPixmap pixvalue = qvariant_cast<QPixmap>(value);

      if (name == "Normal On")
      {
         icon.addPixmap(pixvalue, QIcon::Mode::Normal, QIcon::State::On);
      }
      else if (name == "Normal Off")
      {
         icon.addPixmap(pixvalue, QIcon::Mode::Normal, QIcon::State::Off);
      }
      else if (name == "Active On")
      {
         icon.addPixmap(pixvalue, QIcon::Mode::Active, QIcon::State::On);
      }
      else if (name == "Active Off")
      {
         icon.addPixmap(pixvalue, QIcon::Mode::Active, QIcon::State::Off);
      }
      else if (name == "Selected On")
      {
         icon.addPixmap(pixvalue, QIcon::Mode::Selected, QIcon::State::On);
      }
      else if (name == "Selected Off")
      {
         icon.addPixmap(pixvalue, QIcon::Mode::Selected, QIcon::State::Off);
      }
      else if (name == "Disabled On")
      {
         icon.addPixmap(pixvalue, QIcon::Mode::Disabled, QIcon::State::On);
      }
      else if (name == "Disabled Off")
      {
         icon.addPixmap(pixvalue, QIcon::Mode::Disabled, QIcon::State::Off);
      }

      m_model->setData(m_index, icon);

      m_isSettingChildren = false;

   }
}
