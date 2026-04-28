/*!
 * \file qfontpropertyitem.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of QFontPropertyItem.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */


#include <QDebug>
#include <QFontDatabase>
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
                  QString name = "[" + font.family() + ", " + QString::number(font.pointSize()) + "]";
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


         QPropertyItem * italic = new QChildBoolPropertyItem(font.italic(), "Italic", this);
         m_children.append(italic);


         QPropertyItem * underline = new QChildBoolPropertyItem(font.underline(), "Underline", this);
         m_children.append(underline);


         QPropertyItem * strikeOut = new QChildBoolPropertyItem(font.strikeOut(), "Strikeout", this);
         m_children.append(strikeOut);

         QPropertyItem * kerning = new QChildBoolPropertyItem(font.kerning(), "Kerning", this);
         m_children.append(kerning);


         int index = QFont::staticMetaObject.indexOfEnumerator("StyleStrategy");
         QMetaEnum testenum = QFont::staticMetaObject.enumerator(index);
         QChildEnumPropertyItem* styleStrategy = new QChildEnumPropertyItem((int)font.styleStrategy(), "Style Strategy", testenum, this);
         m_children.append(styleStrategy);



         connect(fontFamily, SIGNAL(valueChanged(const QString&, const QVariant&)), this, SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
         connect(pointSize, SIGNAL(valueChanged(const QString&, const QVariant&)), this, SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
         connect(bold, SIGNAL(valueChanged(const QString&, const QVariant&)), this, SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
         connect(italic, SIGNAL(valueChanged(const QString&, const QVariant&)), this, SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
         connect(underline, SIGNAL(valueChanged(const QString&, const QVariant&)), this, SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
         connect(strikeOut, SIGNAL(valueChanged(const QString&, const QVariant&)), this, SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
         connect(kerning, SIGNAL(valueChanged(const QString&, const QVariant&)), this, SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
         connect(styleStrategy, SIGNAL(valueChanged(const QString&, const QVariant&)), this, SLOT(onChildItemValueChanged(const QString&, const QVariant&)));

         updateChildEnabledStates(font.family());

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

      updateChildEnabledStates(font.family());

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
            updateChildEnabledStates(value.toString());
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

void QFontPropertyItem::updateChildEnabledStates(const QString& family)
{
   QStringList styles = QFontDatabase::styles(family);
   bool supportsBold = QFontDatabase::bold(family, "Bold") ||
                       styles.contains("Bold") ||
                       styles.contains("Bold Italic");
   bool supportsItalic = QFontDatabase::italic(family, "Italic") ||
                         styles.contains("Italic") ||
                         styles.contains("Bold Italic");

   // children: 0=Family, 1=PointSize, 2=Bold, 3=Italic, 4=Underline, 5=Strikeout, 6=Kerning, 7=StyleStrategy
   if (m_children.count() > 3)
   {
      Qt::ItemFlags enabledFlags = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
      Qt::ItemFlags disabledFlags = Qt::ItemIsSelectable;

      m_children[2]->setFlags(supportsBold ? enabledFlags : disabledFlags);
      m_children[3]->setFlags(supportsItalic ? enabledFlags : disabledFlags);
   }
}
