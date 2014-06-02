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
#include "qvariantlistpropertyeditor.h"
#include <qvariantpropertydelegate.h>

QVariantListPropertyEditor::QVariantListPropertyEditor(QWidget *parent)
	: QAbstractListPropertyEditor(parent)
{
	model->setColumnCount(2);
	dialog->setWindowTitle("List Editor");
}

QVariantListPropertyEditor::~QVariantListPropertyEditor()
{

}

void QVariantListPropertyEditor::setValue(const QVariant& value)
{
    list = qvariant_cast<QVariantList>(value);
	setUpModel();
}

QVariant QVariantListPropertyEditor::getValue() const
{
	return list;
}

void QVariantListPropertyEditor::setUpModel() 
{	

	model->clear();
	
	for(int i =0 ; i < list.count(); i++)
	{
		QVariant value = list[i];
		templateValue = QVariant(value);

		QString vName;

		if(value.canConvert<QString>())
		{
			vName = value.toString();
		}
		else
		{
			vName = value.typeName();
		}

		vName = "[Index = "+QString::number(i)+", Item = "+vName+"]";

    	QStandardItem* item = new QStandardItem();
		item->setData(vName, Qt::DisplayRole);
		item->setData(value, Qt::UserRole);

		model->appendRow(item);
	}

}

void QVariantListPropertyEditor::currentChanged(const QModelIndex & current, const QModelIndex & previous )
{
	//update previous selection
	if(previous.isValid())
	{
	    QVariant value = tmodel->getRootValue();
		list[previous.row()] = value;

		QString vName;
		if(value.canConvert<QString>())
		{
			vName = value.toString();
		}
		else
		{
			vName = value.typeName();
		}

		vName = "[Index = "+QString::number(previous.row())+", Item = "+vName+"]";

		QStandardItem* item = model->itemFromIndex(previous);
		item->setData(value, Qt::UserRole);
		item->setData(vName, Qt::DisplayRole);
	}

	if(current.isValid())
	{
		QVariant value = model->data(current, Qt::UserRole);

		if (value.isValid())
		{
			int type = value.userType();
			tmodel = new QtPropertyModel(value);
			QVariantPropertyDelegate* itemDelegate = new QVariantPropertyDelegate(ui.treeView);
			ui.treeView->setAlternatingRowColors(true);
			ui.treeView->setModel(tmodel);
			ui.treeView->setEditTriggers(QAbstractItemView:: AllEditTriggers);
			ui.treeView->setItemDelegate(itemDelegate);
			ui.treeView->expandToDepth(1);
			ui.treeView->resizeColumnToContents(0);
			ui.treeView->resizeColumnToContents(1);
		}
	}
}

void QVariantListPropertyEditor::addToList()
{
	
	QItemSelectionModel* selectionModel = ui.listView->selectionModel();

	if(selectionModel->hasSelection())
	{
		QModelIndexList selected = selectionModel->selectedIndexes();
		QModelIndex index = selected[selected.count()-1];
		list.insert(index.row(), cloneDefault());
	}
	else
	{
		list.append(cloneDefault());
	}
	setUpModel();
	emit valueChanged();
}

void QVariantListPropertyEditor::removeFromList()
{
	QModelIndexList selected = ui.listView->selectionModel()->selectedIndexes();

	for (int i = 0 ; i < selected.count(); i++)
	{
		selected = ui.listView->selectionModel()->selectedIndexes();
		model->removeRow(selected[0].row());
		list.removeAt(selected[0].row());
	}

	emit valueChanged();
}

QVariant QVariantListPropertyEditor::cloneDefault()
{
	QObject* templateObj = qvariant_cast<QObject*>(templateValue);

	if(templateObj)
	{
		const QMetaObject* mobj = templateObj->metaObject();

		QObject* returnObject = mobj->newInstance();

		if(returnObject)
		{
			return QVariant::fromValue(returnObject);
		}
	}

	return QVariant(templateValue);
}
