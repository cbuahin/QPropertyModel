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
