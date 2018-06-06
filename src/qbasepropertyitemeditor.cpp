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
#include "qcustomeditors.h"
#include "qpropertymodel.h"
#include <QDebug>

QBasePropertyItemEditor::QBasePropertyItemEditor( QWidget *parent)
   : QWidget(parent)
{
   m_editorWidget = nullptr;
   m_propertyItem = nullptr;

   this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

   m_resetPushButton = new QPushButton(this);
   m_resetPushButton->setFixedWidth(20);
   m_resetPushButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
   m_resetPushButton->setToolTip("Reset Property");
   m_resetPushButton->setStatusTip("Reset Property");
   m_resetPushButton->setWhatsThis("Reset Property");
   m_resetPushButton->setIcon(QIcon(":/QPropertyModel/reset"));

   QHBoxLayout* layout = new QHBoxLayout(this);
   layout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

   layout->setSpacing(2.0);
   layout->setContentsMargins(1, 1, 1, 1);
   layout->addWidget(m_resetPushButton);
}

QBasePropertyItemEditor::QBasePropertyItemEditor(QWidget* childEditor, QPropertyItem* propertyItem, QWidget *parent)
   : QWidget(parent)
{


   m_editorWidget = childEditor;
   m_valueProperty = m_editorWidget->metaObject()->userProperty();
   m_propertyItem = propertyItem;

   this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

   m_resetPushButton = new QPushButton(this);
   m_resetPushButton->setFixedWidth(20);
   m_resetPushButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
   m_resetPushButton->setEnabled(propertyItem->canReset());
   m_resetPushButton->setToolTip("Reset Property");
   m_resetPushButton->setStatusTip("Reset Property");
   m_resetPushButton->setWhatsThis("Reset Property");
   m_resetPushButton->setIcon(QIcon(":/QPropertyModel/reset"));

   connect(m_resetPushButton, SIGNAL(clicked()), this, SLOT(onRefresh()));

   QHBoxLayout* layout = new QHBoxLayout(this);
   layout->setSpacing(2.0);
   layout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
   layout->setContentsMargins(1, 1, 1, 1);

   m_editorWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   layout->addWidget(m_editorWidget);
   layout->addWidget(m_resetPushButton);

   setValue(m_propertyItem->data(1, Qt::EditRole));
}

QBasePropertyItemEditor::~QBasePropertyItemEditor()
{
   if(m_editorWidget)
      delete m_editorWidget;
}

void QBasePropertyItemEditor::setPropertyItem(QPropertyItem* const propertyItem)
{
   m_propertyItem = propertyItem;
   m_resetPushButton->setEnabled(propertyItem->canReset());
   setUpChildWidget();
}

void QBasePropertyItemEditor::setValue(const QVariant& value)
{
   m_valueProperty.write(m_editorWidget, value);
}

QVariant QBasePropertyItemEditor::getValue() const
{
   return  m_valueProperty.read(m_editorWidget);
}

void QBasePropertyItemEditor::focusOutEvent(QFocusEvent * event)
{
   emit valueChanged(this);
}

void QBasePropertyItemEditor::setUpChildWidget()
{

}

void QBasePropertyItemEditor::onRefresh()
{
   if (m_valueProperty.isValid() && m_propertyItem)
   {
      m_propertyItem->resetData();
      m_valueProperty.write(m_editorWidget, m_propertyItem->data(1, Qt::EditRole));
   }
}

