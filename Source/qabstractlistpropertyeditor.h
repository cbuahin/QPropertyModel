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
#ifndef QABSTRACTLISTPROPERTYEDITOR_H
#define QABSTRACTLISTPROPERTYEDITOR_H

#include "ui_qabstractlistpropertyeditor.h"
#include "qabstractvariantpropertypopupeditor.h"
#include "qtpropertymodel.h"
#include "qvariantproperty.h"


class QAbstractListPropertyEditor : public QAbstractVariantPropertyPopUpEditor
{
	Q_OBJECT

public:
	QAbstractListPropertyEditor(QWidget *parent = 0);
	virtual ~QAbstractListPropertyEditor();

	virtual void setVariantProperty(QVariantProperty* const & vProperty);
	virtual void setUpModel() = 0;

private slots:
	virtual void currentChanged (const QModelIndex & current, const QModelIndex & previous ) = 0;
    void customContextMenuRequested (const QPoint & pos);
	virtual void addToList() = 0;
	virtual void removeFromList() = 0;

protected:
	QStandardItemModel* model;
	QtPropertyModel* tmodel;
	QWidget* dialog;
	Ui::QAbstractListPropertyEditor ui;
	QMenu* contextMenu;
	bool canEdit;
};

#endif // QABSTRACTLISTPROPERTYEDITOR_H
