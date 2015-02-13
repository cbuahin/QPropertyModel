#include "stdafx.h"
#include "qpropertymodeltesting.h"
#include "qpropertymodel.h"
#include "qpropertyitemdelegate.h"
#include "tempobject.h"

QPropertyModelTesting::QPropertyModelTesting(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QPropertyModel* model = new QPropertyModel(this);
	QPropertyItemDelegate* modelDelegate = new QPropertyItemDelegate(model);
	TempObject* t = new TempObject(this);
	QVariant variant = QVariant::fromValue(t);
	model->setParentData(variant);
	
	ui.treeView->setModel(model);
	ui.treeView->setEditTriggers(QAbstractItemView::AllEditTriggers);
	ui.treeView->setItemDelegate(modelDelegate);
	ui.treeView->expandToDepth(0);
	ui.treeView->setAlternatingRowColors(true);
	ui.treeView->resizeColumnToContents(0);
	ui.treeView->resizeColumnToContents(1);


}

QPropertyModelTesting::~QPropertyModelTesting()
{

}
