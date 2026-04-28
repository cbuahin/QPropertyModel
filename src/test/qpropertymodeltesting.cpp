/*!
 * \author Caleb Buahin <caleb.buahin@gmail.com>
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


#include "qpropertymodeltesting.h"
#include "qpropertymodel.h"
#include "qpropertyitemdelegate.h"
#include "tempobject.h"
#include "qstringlistpropertyitem.h"
#include "qcustomeditors.h"
#include <QPushButton>
#include <QToolBar>

QPropertyModelTesting::QPropertyModelTesting(QWidget *parent)
   : QMainWindow(parent), m_multiMode(false)
{
   ui.setupUi(this);

   m_model = new QPropertyModel(ui.treeView);
   m_model->registerCustomPropertyItemType((QMetaType::Type) qMetaTypeId<TempObject*>(), &TempObjectPropertyItem::staticMetaObject);
   m_model->registerCustomPropertyItemType((QMetaType::Type) qMetaTypeId<QList<QGraphicsScene*>>(), &TempObjectListPropertyItem::staticMetaObject);

   QPropertyItemDelegate* modelDelegate = new QPropertyItemDelegate(m_model);

   ui.treeView->setModel(m_model);
   ui.treeView->setEditTriggers(QAbstractItemView::AllEditTriggers);
   ui.treeView->setItemDelegate(modelDelegate);
   ui.treeView->setAlternatingRowColors(true);

   // Create two TempObjects with some different property values
   TempObject* t1 = new TempObject(this);
   t1->setName("Object A");
   t1->setColor(QColor(Qt::red));
   t1->setSize(QSize(100, 200));

   TempObject* t2 = new TempObject(this);
   t2->setName("Object B");
   t2->setColor(QColor(Qt::blue));
   t2->setSize(QSize(100, 200));  // same size as t1

   m_tempObj1 = t1;
   m_tempObj2 = t2;

   // Start in single-object mode
   m_model->setData(QVariant::fromValue(static_cast<QObject*>(m_tempObj1)));

   ui.treeView->expandToDepth(1);
   ui.treeView->resizeColumnToContents(0);
   ui.treeView->resizeColumnToContents(1);

   // Add a toolbar button to toggle multi-object mode
   QToolBar* toolbar = addToolBar("Multi-Object");
   QPushButton* toggleBtn = new QPushButton("Toggle Multi-Object (2 TempObjects)");
   toolbar->addWidget(toggleBtn);
   connect(toggleBtn, &QPushButton::clicked, this, &QPropertyModelTesting::onToggleMultiObject);
}

QPropertyModelTesting::~QPropertyModelTesting()
{

}

void QPropertyModelTesting::onToggleMultiObject()
{
   m_multiMode = !m_multiMode;

   if (m_multiMode)
   {
      QList<QObject*> objects;
      objects << m_tempObj1 << m_tempObj2;
      m_model->setData(objects);
      statusBar()->showMessage("Multi-object mode: 2 TempObjects — mixed values show \xe2\x80\x94");
   }
   else
   {
      m_model->setData(QVariant::fromValue(m_tempObj1));
      statusBar()->showMessage("Single-object mode: Object A");
   }

   ui.treeView->expandToDepth(1);
   ui.treeView->resizeColumnToContents(0);
   ui.treeView->resizeColumnToContents(1);
}
