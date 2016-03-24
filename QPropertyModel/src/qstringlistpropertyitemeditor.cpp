#include "stdafx.h"
#include <QMenu>
#include <QDialog>

#include "qcustomeditors.h"
#include "qvariantpropertyItem.h"

QStringListPropertyItemEditor::QStringListPropertyItemEditor(QWidget *parent)
   : QPopUpPropertyItemEditor(parent)//, m_canEdit(false)
{

   m_editorDialog = new QDialog(this);
   ui.setupUi(m_editorDialog);
   m_editorDialog->setWindowTitle("QStringList Editor");

   m_model = new QStringListModel(this);
   ui.listView->setModel(m_model);
   ui.listView->setContextMenuPolicy(Qt::CustomContextMenu);
   ui.listView->setSelectionBehavior(QAbstractItemView::SelectItems);
   ui.listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

   m_contextMenu = new QMenu(m_editorDialog);

   QAction* addAction = new QAction("Add", m_contextMenu);
   connect(addAction, SIGNAL(triggered()), this, SLOT(add()));

   QAction* removeAction = new QAction("Remove", m_contextMenu);
   connect(removeAction, SIGNAL(triggered()), this, SLOT(remove()));

   m_contextMenu->addAction(addAction);
   m_contextMenu->addAction(removeAction);

   connect(ui.pushButtonOK, SIGNAL(clicked()), m_editorDialog, SLOT(accept()));
   connect(m_editorDialog, SIGNAL(accepted()), this, SLOT(close()));

   connect(ui.pushButtonAdd, SIGNAL(clicked()), this, SLOT(add()));
   connect(ui.pushButtonRemove, SIGNAL(clicked()), this, SLOT(remove()));

   connect(ui.listView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customContextMenuRequested(QPoint)));
}

QStringListPropertyItemEditor::~QStringListPropertyItemEditor()
{
}

void QStringListPropertyItemEditor::setValue(const QVariant& value)
{
   QStringList list = qvariant_cast<QStringList>(value);
   m_model->setStringList(list);
}

QVariant QStringListPropertyItemEditor::getValue() const
{
   return m_model->stringList();
}

void QStringListPropertyItemEditor::setUpChildWidget()
{
   QVariant value = m_propertyItem->data(1, Qt::EditRole);
   QStringList list = qvariant_cast<QStringList>(value);
   m_model->setStringList(list);

   QVariantPropertyItem* test = (QVariantPropertyItem*) m_propertyItem ;

   if ( (m_propertyItem->isEditable() && !test ) || (test && test->metaProperty().isValid()
                                                    && test->metaProperty().isWritable()))
   {
      ui.pushButtonAdd->setEnabled(true);
      ui.pushButtonRemove->setEnabled(true);
      ui.listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked |
                                   QAbstractItemView::EditKeyPressed | QAbstractItemView::AnyKeyPressed);
      m_canEdit = true;
   }
   else
   {
      ui.pushButtonAdd->setEnabled(false);
      ui.pushButtonRemove->setEnabled(false);
      ui.listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
      m_canEdit = false;
   }
}

void QStringListPropertyItemEditor::customContextMenuRequested(const QPoint & pos)
{
   if (m_canEdit)
   {
      m_contextMenu->popup(ui.listView->viewport()->mapToGlobal(pos));
   }
}

void QStringListPropertyItemEditor::add()
{
   QItemSelectionModel* selectionModel = ui.listView->selectionModel();

   if (selectionModel->hasSelection())
   {
      QModelIndexList selected = selectionModel->selectedIndexes();
      QModelIndex index = selected[selected.count() - 1];
      m_model->insertRow(index.row() + 1);
      index = m_model->index(index.row() + 1);
      m_model->setData(index, QString("New String"));
   }
   else
   {
      m_model->insertRow(m_model->rowCount());
      QModelIndex index = m_model->index(m_model->rowCount()-1);
      m_model->setData(index, QString("New String"));
   }

   emit valueChanged(this);
}

void QStringListPropertyItemEditor::remove()
{
   QModelIndexList list = ui.listView->selectionModel()->selectedIndexes();

   while (list.count() > 0)
   {
      m_model->removeRow(list[0].row());
      list = ui.listView->selectionModel()->selectedIndexes();
   }
   emit valueChanged(this);
}


void QStringListPropertyItemEditor::close()
{
   emit valueChanged(this);
}
