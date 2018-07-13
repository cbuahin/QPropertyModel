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
#include <QMessageBox>
#include "qcustomeditors.h"
#include "qpropertymodel.h"
#include "qpropertyitemdelegate.h"
#include "ui_qcustomobjectlistpropertyitemeditor.h"

QObjectListPropertyItemEditor::QObjectListPropertyItemEditor(QWidget* parent)
   :QPopUpPropertyItemEditor(parent) ,
     m_propertyModelDelegate(nullptr) ,
     ui(new Ui::QCustomObjectListPropertyItemEditor)
{
   
   m_editorDialog = new QDialog(this);
   ui->setupUi(m_editorDialog);
   m_editorDialog->setWindowTitle("QObject List Editor");

   m_objectListModel = new QStandardItemModel(ui->listViewItems);

   ui->listViewItems->setModel(m_objectListModel);
   ui->listViewItems->setSelectionBehavior(QAbstractItemView::SelectRows);
   ui->listViewItems->setSelectionMode(QAbstractItemView::ExtendedSelection);
   ui->listViewItems->setEditTriggers(QAbstractItemView::NoEditTriggers);

   m_propertyModel = new QPropertyModel(this);
   ui->treeViewProperties->setModel(m_propertyModel);
   ui->treeViewProperties->setEditTriggers(QAbstractItemView::AllEditTriggers);
   ui->treeViewProperties->setAlternatingRowColors(true);
   ui->treeViewProperties->expandToDepth(1);
   ui->treeViewProperties->resizeColumnToContents(0);
   ui->treeViewProperties->resizeColumnToContents(1);

   connect(ui->pushButtonOK, SIGNAL(clicked()), m_editorDialog, SLOT(accept()));
   connect(ui->listViewItems, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onItemClicked(const QModelIndex&)));
   connect(ui->pushButtonAdd, SIGNAL(clicked()), this, SLOT(onAddNewObject()));
   connect(ui->pushButtonRemove, SIGNAL(clicked()), this, SLOT(onRemoveObject()));
   connect(ui->pushButtonOK, SIGNAL(clicked()), this, SLOT(close()));

   if(m_windowState != -1000)
   {
      m_editorDialog->restoreGeometry(m_state);
      Qt::WindowState windowState = (Qt::WindowState) m_windowState;
      m_editorDialog->setWindowState(windowState);
      m_editorDialog->setGeometry(m_geometry);
   }
}

QObjectListPropertyItemEditor::~QObjectListPropertyItemEditor()
{
   delete ui;
}


void QObjectListPropertyItemEditor::setValue(const QVariant &value)
{
   if(!m_propertyModelDelegate)
   {
      m_propertyModelDelegate = new QPropertyItemDelegate(this);
      ui->treeViewProperties->setItemDelegate(m_propertyModelDelegate);
   }

   m_values = qvariant_cast<QList<QObject*>>(value);
   setUpChildWidget();
}

QVariant QObjectListPropertyItemEditor::getValue() const
{
   return QVariant::fromValue(m_values);
}

void QObjectListPropertyItemEditor::setUpChildWidget()
{

   m_objectListModel->clear();


   if(m_values.length())
   {
      for(int i = 0 ; i < m_values.length() ; i++ )
      {
         QVariant v = QVariant::fromValue(m_values[i]);
         QStandardItem* item = new QStandardItem();
         item->setData(v,Qt::UserRole);
         item->setData(QString(m_values[i]->metaObject()->className()) + "*" , Qt::DisplayRole);
         m_objectListModel->appendRow(item);

         if(i == 0)
         {
            QString winName(m_values[i]->metaObject()->className());
            m_editorDialog->setWindowTitle(winName + " List Editor");
            m_propertyModel->setData(v);
         }
      }
   }

   QVariantPropertyItem* test = (QVariantPropertyItem*) m_propertyItem ;

   if ( (m_propertyItem->isEditable() && !test ) || (test && test->metaProperty().isValid()
                                                    && test->metaProperty().isWritable()))
   {
      ui->pushButtonAdd->setEnabled(true);
      ui->pushButtonRemove->setEnabled(true);
     // ui->treeViewProperties->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked |
      //                                       QAbstractItemView::EditKeyPressed | QAbstractItemView::AnyKeyPressed);
   }
   else
   {
      ui->pushButtonAdd->setEnabled(false);
      ui->pushButtonRemove->setEnabled(false);
    //  ui->treeViewProperties->setEditTriggers(QAbstractItemView::NoEditTriggers);
   }
}


void QObjectListPropertyItemEditor::onItemClicked(const QModelIndex& index)
{
   m_currentlySelected = index;
   QVariant value = index.data(Qt::UserRole);
   m_propertyModel->setData(value);
   ui->treeViewProperties->expandToDepth(0);
   ui->treeViewProperties->resizeColumnToContents(0);
   ui->treeViewProperties->resizeColumnToContents(1);
}


void QObjectListPropertyItemEditor::onAddNewObject()
{
   if(m_values.length())
   {
      const QMetaObject* mobj = m_values[0]->metaObject();
      QObject* parent = m_values[0]->parent();
      QObject* test = mobj->newInstance(Q_ARG(QObject* , parent));

      if(test)
      {
         m_values.append(test);
         setUpChildWidget();
      }
   }
   else
   {
      QMessageBox msgBox;
      msgBox.setText("The list must have at least on object to serve as a template");
      msgBox.exec();
   }
}

void QObjectListPropertyItemEditor::onRemoveObject()
{
   QModelIndexList selectedItems = ui->listViewItems->selectionModel()->selectedRows();

   while (selectedItems.count() > 0)
   {
      m_objectListModel->removeRow(selectedItems[0].row());
      QObject* value = m_values[selectedItems[0].row()];
      m_values.removeAt(selectedItems[0].row());

      if(!value->parent())
      {
         delete value;
      }
      selectedItems = ui->listViewItems->selectionModel()->selectedRows();
   }
}

void QObjectListPropertyItemEditor::close()
{
   m_state  = m_editorDialog->saveGeometry();
   m_windowState = (int) m_editorDialog->windowState();
   m_geometry = m_editorDialog->geometry();
   qDebug() << "Object";
}


