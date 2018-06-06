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
#include "qpropertymodeltesting.h"
#include "qpropertymodel.h"
#include "qpropertyitemdelegate.h"
#include "tempobject.h"
#include "qstringlistpropertyitem.h"
#include "qcustomeditors.h"

QPropertyModelTesting::QPropertyModelTesting(QWidget *parent)
   : QMainWindow(parent)
{
   ui.setupUi(this);

   QPropertyModel* model = new QPropertyModel(ui.treeView);
   model->registerCustomPropertyItemType((QMetaType::Type) qMetaTypeId<TempObject*>(), &TempObjectPropertyItem::staticMetaObject);
   model->registerCustomPropertyItemType((QMetaType::Type) qMetaTypeId<QList<QGraphicsScene*>>(), &TempObjectListPropertyItem::staticMetaObject);


   //model->registerCustomPropertyItemType(QMetaType::QStringList,&QStringListPropertyItem::staticMetaObject);

   QPropertyItemDelegate* modelDelegate = new QPropertyItemDelegate(model);
   //modelDelegate->registerCustomTypeEditorCreator(QMetaType::QStringList, new QStandardItemEditorCreator<QStringListPropertyItemEditor>());



   ui.treeView->setModel(model);
   ui.treeView->setEditTriggers(QAbstractItemView::AllEditTriggers);
   ui.treeView->setItemDelegate(modelDelegate);
   ui.treeView->setAlternatingRowColors(true);



   TempObject* t = new TempObject(this);
   QVariant variant = QVariant::fromValue(t);
   model->setData(variant);

   ui.treeView->expandToDepth(1);
   ui.treeView->resizeColumnToContents(0);
   ui.treeView->resizeColumnToContents(1);

}

QPropertyModelTesting::~QPropertyModelTesting()
{

}
