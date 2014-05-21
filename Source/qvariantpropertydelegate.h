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
#ifndef QVARIANTPROPERTYDELEGATE_H
#define QVARIANTPROPERTYDELEGATE_H

#include <QStyledItemDelegate>

class QVariantPropertyDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	QVariantPropertyDelegate(QObject *parent);
	~QVariantPropertyDelegate();


	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setEditorData ( QWidget * editor, const QModelIndex & index ) const;
	void setModelData ( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const;

	bool registerCustomEditorCreator(QString &qproperty, QItemEditorCreatorBase* const & editor);

private:
	QItemEditorCreatorBase*  getRegisteredCustomEditorCreator(QString& qproperty) const;


private:
	QMap<QString,QItemEditorCreatorBase *> registeredWidgets;
	QItemEditorFactory* factory;
};

#endif // QVARIANTPROPERTYDELEGATE_H
