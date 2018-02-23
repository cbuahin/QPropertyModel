/*!
 * \file *.h
 * \author Caleb Amoa Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * \license
 * This file and its associated files, and libraries are free software.
 * You can redistribute it and/or modify it under the terms of the
 * Lesser GNU General Public License as published by the Free Software Foundation;
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

#ifndef QPROPERTYITEMDELEGATE_H
#define QPROPERTYITEMDELEGATE_H

#include "qpropertymodel_global.h"
#include <QStyledItemDelegate>
#include <QItemEditorFactory>

class QPROPERTYMODEL_EXPORT QPropertyItemDelegate : public QStyledItemDelegate
{
      Q_OBJECT

   public:
      QPropertyItemDelegate(QObject *parent);

      ~QPropertyItemDelegate();

      void registerCustomTypeEditorCreator(QMetaType::Type type, QItemEditorCreatorBase* creator);

      QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const override;

      void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const override;

      void setEditorData(QWidget * editor, const QModelIndex & index) const override;

      void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const override;

      QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const override;

      void updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const override;

   private slots:

      void onEditorValueChanged(QWidget* widget);

};

#endif // QPROPERTYITEMDELEGATE_H
