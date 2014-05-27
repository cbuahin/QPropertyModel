/****************************************************************************
**
**  Copyright (C) 2014 Caleb Amoa Buahin
**  Contact: calebgh@gmail.com
** 
**  This file is part of QPropertGrid.exe and QPropertGrid.dll
**
**  QPropertGrid.exe and QPropertGrid.dll and its associated files is free software; you can redistribute it and/or modify
**  it under the terms of the Lesser GNU General Public License as published by
**  the Free Software Foundation; either version 3 of the License, or
**  (at your option) any later version.
**
**  QPropertGrid.exe and QPropertGrid.dll and its associated files is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  Lesser GNU General Public License for more details.
**
**  You should have received a copy of the Lesser GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>
**
****************************************************************************/


#include "stdafx.h"
#include "qtpropertygrid.h"
#include "TestObject.h"
#include <qtpropertymodel.h>
#include <qvariantpropertydelegate.h>

QtPropertyGrid::QtPropertyGrid(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	TestObject* temp =new TestObject(this);

	//QObjectList children = temp->children();

	//for(int i = 0 ; i < children.count() ; i++)
	//{
	//	QObject* temptt = children[i];
	//	temptt->blockSignals(true);
	//}


	//const QMetaObject* tempmeta = temp->metaObject();


	//qDebug() << "Original Object " << tempmeta->className() << "Original Object Parent " ;

	//const QMetaObject* parent1 =  tempmeta->superClass();

	//qDebug() << "Parent Class Object " << parent1->className();

	//QObject* tempCast = static_cast<QObject*>(temp);

	//

	//const QMetaObject* tempmetac = tempCast->metaObject();
	//
	//qDebug() << "Cast of Original Class to Object" << tempmetac->className();

	//const QMetaObject* parent2 =  tempmetac->superClass();

	//	qDebug() << "Cast of Original Class to Object Parent" << parent2->className();

	//Q_ASSERT(parent1 == parent2);

	//QtPropertyModel* model = new QtPropertyModel(ui.treeView);
	QVariantPropertyDelegate* itemDelegate = new QVariantPropertyDelegate(ui.treeView);
	QtPropertyModel* model = new QtPropertyModel(temp);
	connect(model,SIGNAL(dataChanged(QModelIndex,QModelIndex)),ui.treeView,SLOT(repaint()));
	ui.treeView->setModel(model);
	ui.treeView->setEditTriggers(QAbstractItemView:: AllEditTriggers);
	ui.treeView->setItemDelegate(itemDelegate);
	ui.treeView->expandToDepth(0);
	ui.treeView->setAlternatingRowColors(true);
	ui.treeView->resizeColumnToContents(0);
	ui.treeView->resizeColumnToContents(1);

	
}

QtPropertyGrid::~QtPropertyGrid()
{

}
