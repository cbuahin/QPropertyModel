#include "stdafx.h"
#include "qabstractlistpropertyeditor.h"
#include <qvariantpropertydelegate.h>

QAbstractListPropertyEditor::QAbstractListPropertyEditor(QWidget *parent)
	: QAbstractVariantPropertyPopUpEditor(parent)
{
	dialog = new QWidget();
	ui.setupUi(dialog);

	ui.label->setVisible(false);
	ui.lineEditKeyValue->setVisible(false);

    contextMenu = new QMenu(dialog);
	
	QAction* addAction = new QAction("Add", contextMenu);
	connect(addAction,SIGNAL(triggered()),this,SLOT(addQString()));
	
	QAction* removeAction = new QAction("Remove", contextMenu);
	connect(removeAction,SIGNAL(triggered()),this,SLOT(removeQString()));

	contextMenu->addAction(addAction);
	contextMenu->addAction(removeAction);


	model = new QStandardItemModel(this);
	model->setColumnCount(1);
	ui.listView->setModel(model);

	ui.listView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
	ui.listView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectItems);
	ui.listView->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);

	connect(ui.listView, SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customContextMenuRequested (QPoint)));
	
	connect(openEditorButton, SIGNAL(clicked()), dialog, SLOT(show()));
	connect(ui.pushButtonOk, SIGNAL(clicked()), dialog, SLOT(close()));

	connect(ui.pushButtonAdd, SIGNAL(clicked()), this, SLOT(addToList()));
	connect(ui.pushButtonRemove, SIGNAL(clicked()), this, SLOT(removeFromList()));

	QItemSelectionModel* selectionModel = ui.listView->selectionModel();
	connect(selectionModel,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this , SLOT(currentChanged(QModelIndex,QModelIndex)));
}

void QAbstractListPropertyEditor::customContextMenuRequested (const QPoint &pos)
{
	if(canEdit)
	{
		contextMenu->popup(ui.listView->viewport()->mapToGlobal(pos));
	}
}

QAbstractListPropertyEditor::~QAbstractListPropertyEditor()
{
	delete model;
	delete dialog;
}

void QAbstractListPropertyEditor::setVariantProperty(QVariantProperty* const & vProperty)
{
	QMetaProperty prop = vProperty->getMetaProperty();

	if(prop.isValid())
	{
		if(prop.isWritable())
		{
			ui.pushButtonAdd->setEnabled(true);
			ui.pushButtonRemove->setEnabled(true);
			ui.treeView->setEditTriggers(QAbstractItemView::AllEditTriggers);
			ui.label->setEnabled(true);
			ui.lineEditKeyValue->setEnabled(true);
			canEdit = true;

		}
		else
		{
			ui.pushButtonAdd->setEnabled(false);
			ui.pushButtonRemove->setEnabled(false);
						ui.label->setEnabled(false);
			ui.lineEditKeyValue->setEnabled(false);
			ui.treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

			canEdit = true;
		}
	}
	else
	{
		ui.pushButtonAdd->setEnabled(true);
		ui.pushButtonRemove->setEnabled(true);
					ui.label->setEnabled(true);
			ui.lineEditKeyValue->setEnabled(true);
		ui.treeView->setEditTriggers(QAbstractItemView::AllEditTriggers);
		canEdit = true;
	}
}

