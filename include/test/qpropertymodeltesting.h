/*!
 * \qpropertymodeltesting.h
 * \author Caleb Amoa Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * \license
 * This file and its associated files, and libraries are free software.
 * You can redistribute it and/or modify it under the terms of the
 * Lesser GNU Lesser General Public License as published by the Free Software Foundation;
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
