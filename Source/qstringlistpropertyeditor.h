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
#ifndef QSTRINGLISTPROPERTYEDITOR_H
#define QSTRINGLISTPROPERTYEDITOR_H

#include "ui_qstringlistpropertyeditor.h"
#include "qabstractvariantpropertypopupeditor.h"
#include "qvariantproperty.h"

class QStringListPropertyEditor : public QAbstractVariantPropertyPopUpEditor
{
	Q_OBJECT

public:
	QStringListPropertyEditor(QWidget *parent = 0);
	~QStringListPropertyEditor();

    void setValue(const QVariant& value); 
    QVariant getValue() const; 

	void setVariantProperty(QVariantProperty* const & vProperty);

private slots:
	void customContextMenuRequested (const QPoint & pos);
	void addQString();
	void removeQString();

protected:
	QWidget* dialog;
	Ui::QStringListPropertyEditor ui;
	QStringListModel* model;
	QMenu* contextMenu;
	bool canEdit;
};

#endif // QSTRINGLISTPROPERTYEDITOR_H
