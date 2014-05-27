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
#ifndef QTPROPERTYMODEL_H
#define QTPROPERTYMODEL_H



#include <QAbstractItemModel>
#include <qvariantproperty.h>

class QtPropertyModel : public QAbstractItemModel 
{
	Q_OBJECT

public:
	explicit QtPropertyModel(QObject *parent);
	explicit QtPropertyModel(const QVariant& parent);

	~QtPropertyModel();

	bool hasChildren(const QModelIndex & parent = QModelIndex()) const;

	QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;

	QModelIndex parent(const QModelIndex &index) const;

	int rowCount(const QModelIndex &parent = QModelIndex()) const;

	int columnCount(const QModelIndex &parent = QModelIndex()) const;

	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

	bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

	Qt::ItemFlags flags(const QModelIndex & index) const;



private:
	QVariantProperty* getProperty(const QModelIndex &parent = QModelIndex()) const;
	QVariantProperty* rootProperty;
	QVector<int> roles;   	

};

#endif // QTPROPERTYMODEL_H
