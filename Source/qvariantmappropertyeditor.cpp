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
#include "qvariantmappropertyeditor.h"
#include <qvariantpropertydelegate.h>

QVariantMapPropertyEditor::QVariantMapPropertyEditor(QWidget *parent)
	: QAbstractListPropertyEditor(parent)
{
	ui.label->setVisible(true);
	ui.lineEditKeyValue->setVisible(true);
	dialog->setWindowTitle("Map Editor");
}

QVariantMapPropertyEditor::~QVariantMapPropertyEditor()
{
}

void QVariantMapPropertyEditor::setValue(const QVariant& value)
{
    map = qvariant_cast<QVariantMap>(value);
	setUpModel();
}

QVariant QVariantMapPropertyEditor::getValue() const
{
	return map;
}

void QVariantMapPropertyEditor::setUpModel() 
{	
	QList<QString> keys = map.keys();
	model->clear();
	
	for(int i =0 ; i < keys.count() ; i++)
	{
		QString key = keys[i];
		QVariant value = map[key];
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

		vName = "[" + key + ", " + vName + "]"; 

		QStandardItem* item = new QStandardItem();
		item->setData(vName, Qt::DisplayRole);
		item->setData(key, Qt::ToolTipRole);
		item->setData(value, Qt::UserRole);
		model->setHeaderData(0,Qt::Orientation::Horizontal , i , Qt::DisplayRole);
		model->appendRow(item);
	}

	ui.lineEditKeyValue->setText("New Key" + QString::number(keys.count()));
}

void QVariantMapPropertyEditor::currentChanged(const QModelIndex & current, const QModelIndex & previous )
{
	//update previous selection
	if(previous.isValid())
	{
	    QVariant key = model->data(previous, Qt::ToolTipRole);
	    QVariant value = tmodel->getRootValue();
		map[key.toString()] = value;

		QString vName;
		if(value.canConvert<QString>())
		{
			vName = value.toString();
		}
		else
		{
			vName = value.typeName();
		}

		vName = "[" + key.toString() + ", " + vName + "]"; 

		QStandardItem* item = model->itemFromIndex(previous);
		item->setData(value, Qt::UserRole);
		item->setData(vName, Qt::DisplayRole);
		
	}

	if(current.isValid())
	{
		QVariant value = model->data(current, Qt::UserRole);
		QString test = value.toString();

		if (value.isValid())
		{
			int type = value.userType();
			tmodel = new QtPropertyModel(value);
			QVariantPropertyDelegate* itemDelegate = new QVariantPropertyDelegate(ui.treeView);
			ui.treeView->setAlternatingRowColors(true);
			ui.treeView->setModel(tmodel);
			ui.treeView->setEditTriggers(QAbstractItemView:: AllEditTriggers);
			ui.treeView->setItemDelegate(itemDelegate);
			ui.treeView->expandToDepth(0);
			ui.treeView->resizeColumnToContents(0);
			ui.treeView->resizeColumnToContents(1);
		}
	}
}

void QVariantMapPropertyEditor::addToList()
{
	
	QString key = ui.lineEditKeyValue->text();
	
	if(templateValue.isValid() && !key.isEmpty() && !key.isNull() && !map.contains(key))
	{
		QVariant dataToInsert = QVariant(templateValue);
		map[key] = dataToInsert;
	    setUpModel();
	   emit valueChanged();
	}
}

void QVariantMapPropertyEditor::removeFromList()
{
	QModelIndexList list = ui.listView->selectionModel()->selectedIndexes();

	for (int i = 0 ; i < list.count(); i++)
	{
		QStandardItem* item =  model->itemFromIndex(list[i]);
		QString key = item->data(Qt::ToolTipRole).toString();
		map.remove(key);
	}

	setUpModel();
	emit valueChanged();
}