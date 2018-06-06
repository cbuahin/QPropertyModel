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
#include <QDebug>
#include "qfontpropertyitem.h"
#include "qfontfamilypropertyitem.h"
#include "qpropertymodel.h"
#include "qchildpropertyitems.h"

QFontPropertyItem::QFontPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
   : QVariantPropertyItem(value, metaProperty, parent), m_settingChildren(false)
{
   m_isEnabled = true;

}

QFontPropertyItem::~QFontPropertyItem()
{

}


QVariant QFontPropertyItem::data(int column, Qt::ItemDataRole  role) const
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
               return	m_metaProperty.read(m_parent->qObject());
               break;
            case Qt::DisplayRole:
            case Qt::ToolTipRole:
            case Qt::StatusTipRole:
            case Qt::WhatsThisRole:
               {
                  QFont font = qvariant_cast<QFont>(m_metaProperty.read(m_parent->qObject()));
                  QString name = "[" + font.family() + ", " + QString::number(font.pointSize()) + " ]";
                  return name;
               }
               break;
            case Qt::FontRole:
               {
                  QFont font = qvariant_cast<QFont>(m_metaProperty.read(m_parent->qObject()));
                  QFont t;
                  font.setPointSizeF(t.pointSizeF());
                  return font;
               }
               break;
         }

         break;
   }
   return QVariant();
}

//bool QFontPropertyItem::setData(const QVariant & value, Qt::ItemDataRole role)
//{
//	switch (role)
//	{
//	case Qt::EditRole:
//		if (m_metaProperty.write(m_parent->qObject(), value))
//		{
//			m_value = value;
//
//			setChildValues();
//
//			emit valueChanged(m_name, m_value);
//
//			return true;
//		}
//		break;
//	}
//
//	return false;
//}


bool QFontPropertyItem::hasChildren()
{
   if (!m_childrenSet)
   {
      m_childrenSet = true;

      m_value = m_metaProperty.read(m_parent->qObject());

      if (m_value.isValid())
      {
         QFont font = qvariant_cast<QFont>(m_value);

         QFontFamilyPropertyItem* fontFamily = new QFontFamilyPropertyItem(font.family(), "Family", this);
         m_children.append(fontFamily);


         QPropertyItem * pointSize = new QPropertyItem(font.pointSize(), "Point Size", this);
         m_children.append(pointSize);


         QPropertyItem * bold = new QChildBoolPropertyItem(font.bold(), "Bold", this);
         m_children.append(bold);


         QPropertyItem * italic = new QChildBoolPropertyItem(font.bold(), "Italic", this);
         m_children.append(italic);


         QPropertyItem * underline = new QChildBoolPropertyItem(font.bold(), "Underline", this);
         m_children.append(underline);


         QPropertyItem * strikeOut = new QChildBoolPropertyItem(font.bold(), "Strikeout", this);
         m_children.append(strikeOut);

         QPropertyItem * kerning = new QChildBoolPropertyItem(font.bold(), "Kerning", this);
         m_children.append(kerning);


         int index = QFont::staticMetaObject.indexOfEnumerator("StyleStrategy");
         QMetaEnum testenum = QFont::staticMetaObject.enumerator(index);
         QChildEnumPropertyItem* styleStrategy = new QChildEnumPropertyItem(font.capitalization(), "Style Strategy", testenum, this);
         m_children.append(styleStrategy);



         connect(fontFamily, SIGNAL(valueChanged(const QString&, const QVariant&)), this, SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
         connect(pointSize, SIGNAL(valueChanged(const QString&, const QVariant&)), this, SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
         connect(bold, SIGNAL(valueChanged(const QString&, const QVariant&)), this, SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
         connect(italic, SIGNAL(valueChanged(const QString&, const QVariant&)), this, SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
         connect(underline, SIGNAL(valueChanged(const QString&, const QVariant&)), this, SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
         connect(strikeOut, SIGNAL(valueChanged(const QString&, const QVariant&)), this, SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
         connect(kerning, SIGNAL(valueChanged(const QString&, const QVariant&)), this, SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
         connect(styleStrategy, SIGNAL(valueChanged(const QString&, const QVariant&)), this, SLOT(onChildItemValueChanged(const QString&, const QVariant&)));

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

void QFontPropertyItem::setChildValues()
{
   if (!m_settingChildren)
   {
      m_settingChildren = true;

      QFont font = qvariant_cast<QFont>(m_value);

      m_model->setData(m_children[0]->index(), qvariant_cast<QVariant>(font.family()));

      m_model->setData(m_children[1]->index(), qvariant_cast<QVariant>(font.pointSize()));

      m_model->setData(m_children[2]->index(), qvariant_cast<QVariant>(font.bold()));

      m_model->setData(m_children[3]->index(), qvariant_cast<QVariant>(font.italic()));

      m_model->setData(m_children[4]->index(), qvariant_cast<QVariant>(font.underline()));

      m_model->setData(m_children[5]->index(), qvariant_cast<QVariant>(font.strikeOut()));

      m_model->setData(m_children[6]->index(), qvariant_cast<QVariant>(font.kerning()));

      m_model->setData(m_children[7]->index(), qvariant_cast<QVariant>(font.styleStrategy()));

      m_settingChildren = false;
   }
}

void QFontPropertyItem::onChildItemValueChanged(const QString& name, const QVariant& value)
{
   if (!m_settingChildren)
   {
      m_settingChildren = true;

      m_value = m_metaProperty.read(m_parent->qObject());

      if (m_value.isValid())
      {
         QFont font = qvariant_cast<QFont>(m_value);

         if (name == "Family")
         {
            font.setFamily(value.toString());
         }
         else if (name == "Point Size")
         {
            font.setPointSize(value.toInt());
         }
         else if (name == "Bold")
         {
            font.setBold(value.toBool());
         }
         else if (name == "Italic")
         {
            font.setItalic(value.toBool());
         }
         else if (name == "Underline")
         {
            font.setUnderline(value.toBool());
         }
         else if (name == "Strikeout")
         {
            font.setStrikeOut(value.toBool());
         }
         else if (name == "Kerning")
         {
            font.setKerning(value.toBool());
         }
         else if (name == "Style Strategy")
         {
            font.setStyleStrategy(QFont::StyleStrategy(value.toInt()));
         }

         m_model->setData(m_index, qvariant_cast<QVariant>(font));
      }

      m_settingChildren = false;
   }
}
