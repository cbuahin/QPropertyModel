#ifndef QPROPERTYMODELTESTING_H
#define QPROPERTYMODELTESTING_H

#include <QtWidgets/QMainWindow>
#include "ui_qpropertymodeltesting.h"
#include  "qvariantpropertyitem.h"
#include "tempobject.h"

//class QCustomListPropertyItem: public QVariantPropertyItem
//{
//      Q_OBJECT

//   public:
//     Q_INVOKABLE QCustomListPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

//};


class QPropertyModelTesting : public QMainWindow
{
      Q_OBJECT

   public:
      QPropertyModelTesting(QWidget *parent = 0);

      ~QPropertyModelTesting();

   private:
      Ui::QPropertyModelTestingClass ui;
};

#endif // QPROPERTYMODELTESTING_H
