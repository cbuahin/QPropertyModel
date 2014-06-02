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
#include "qstringlistpropertyeditor.h"

QStringListPropertyEditor::QStringListPropertyEditor(QWidget *parent)
	: QAbstractVariantPropertyPopUpEditor(parent)
{
	dialog = new QWidget();
	ui.setupUi(dialog);
	dialog->setWindowTitle("String List Editor");

	model = new QStringListModel(this);
	ui.listView->setModel(model);	
	ui.listView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
	ui.listView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectItems);
	ui.listView->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);

	contextMenu = new QMenu(dialog);
	
	QAction* addAction = new QAction("Add", contextMenu);
	connect(addAction,SIGNAL(triggered()),this,SLOT(addQString()));
	
	QAction* removeAction = new QAction("Remove", contextMenu);
	connect(removeAction,SIGNAL(triggered()),this,SLOT(removeQString()));

	contextMenu->addAction(addAction);
	contextMenu->addAction(removeAction);

	connect(openEditorButton, SIGNAL(clicked()), dialog, SLOT(show()));
	connect(ui.pushButtonOk, SIGNAL(clicked()), dialog, SLOT(close()));

	connect(ui.pushButtonAdd, SIGNAL(clicked()), this, SLOT(addQString()));
	connect(ui.pushButtonRemove, SIGNAL(clicked()), this, SLOT(removeQString()));

	connect(ui.pushButtonOk, SIGNAL(clicked()), dialog, SLOT(close()));

	connect(ui.listView, SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customContextMenuRequested (QPoint)));
}

QStringListPropertyEditor::~QStringListPropertyEditor()
{
	
	delete model;
	delete dialog;
}


void QStringListPropertyEditor::setValue(const QVariant& value)
{
	QStringList list = qvariant_cast<QStringList>(value);
	model->setStringList(list);
}

QVariant QStringListPropertyEditor::getValue() const
{
	return model->stringList();
}

void QStringListPropertyEditor::setVariantProperty(QVariantProperty* const & vProperty)
{
	QMetaProperty prop = vProperty->getMetaProperty();

	if(prop.isValid())
	{
		dialog->setWindowTitle(prop.name());
		if(prop.isWritable())
		{
			canEdit = true;
			ui.pushButtonAdd->setEnabled(true);
			ui.pushButtonRemove->setEnabled(true);
			ui.listView->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked|
				QAbstractItemView::EditKeyPressed|QAbstractItemView::AnyKeyPressed);
		}
		else
		{
			canEdit = false;
			ui.pushButtonAdd->setEnabled(false);
			ui.pushButtonRemove->setEnabled(false);
			ui.listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		}
	}
	else
	{
		canEdit = true;
		dialog->setWindowTitle("StringListEditor");
		ui.pushButtonAdd->setEnabled(true);
		ui.pushButtonRemove->setEnabled(true);
		ui.listView->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked|
				QAbstractItemView::EditKeyPressed|QAbstractItemView::AnyKeyPressed);
	}
}

void QStringListPropertyEditor::customContextMenuRequested (const QPoint &pos)
{
	if(canEdit)
	{
		contextMenu->popup(ui.listView->viewport()->mapToGlobal(pos));
	}
}

void QStringListPropertyEditor::addQString()
{
	QItemSelectionModel* selectionModel = ui.listView->selectionModel();

	if(selectionModel->hasSelection())
	{
		QModelIndexList selected = selectionModel->selectedIndexes();
		QModelIndex index = selected[selected.count()-1];
		model->insertRow(index.row()+1);
		index = model->index(index.row()+1);
		model->setData(index,QString("New String"));
	}
	else
	{
		model->insertRow(model->rowCount()+1);
        QModelIndex index = model->index(model->rowCount()+1);
		model->setData(index,QString("New String"));
	}

	emit valueChanged();
}

void QStringListPropertyEditor::removeQString()
{
	QModelIndexList list = ui.listView->selectionModel()->selectedIndexes();

	while (list.count() > 0)
	{
		model->removeRow(list[0].row());
		list = ui.listView->selectionModel()->selectedIndexes();
	}
	emit valueChanged();
}