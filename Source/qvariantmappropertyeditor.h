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
#ifndef QVARIANTMAPPROPERTYEDITOR_H
#define QVARIANTMAPPROPERTYEDITOR_H

#include "qabstractlistpropertyeditor.h"
#include "qvariantproperty.h"

class QVariantMapPropertyEditor : public QAbstractListPropertyEditor
{
	Q_OBJECT

public:
	QVariantMapPropertyEditor(QWidget *parent);
	~QVariantMapPropertyEditor();

    void setValue(const QVariant& value); 
    QVariant getValue() const; 

	 void setUpModel();

private slots:
    void currentChanged (const QModelIndex & current, const QModelIndex & previous );
	void addToList();
	void removeFromList();

protected:
	QVariantMap map;
	QVariant templateValue;
	
};

#endif // QVARIANTMAPPROPERTYEDITOR_H
