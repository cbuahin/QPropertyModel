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

#include "stdafx.h"
#include <qtpropertymodel.h>
#include <qvariantqobjectproperty.h>

#include <qvariantobjectsuperclassproperty.h>

#include <qboolvariantproperty.h>
#include <qcolorvariantproperty.h>
#include <qfontvariantproperty.h>
#include <qsizevariantproperty.h>
#include <qsizefvariantproperty.h>
#include <qrectvariantproperty.h>
#include <qrectfvariantproperty.h>
#include <qpointvariantproperty.h>
#include <qpointfvariantproperty.h>
#include <qlinevariantproperty.h>
#include <qlinefvariantproperty.h>
#include <qvector2dvariantproperty.h>
#include <qvector3dvariantproperty.h>
#include <qvector4dvariantproperty.h>
#include <qpixmapvariantproperty.h>
#include <qbitmapvariantproperty.h>
#include <qenumvariantproperty.h>
#include <qflagsvariantproperty.h>
#include <qiconvariantproperty.h>
#include <qbrushvariantproperty.h>
#include <qpenvariantproperty.h>
#include <qsizepolicyvariantproperty.h>
#include <qstringlistvariantproperty.h>
#include <qvariantmapproperty.h>

QtPropertyModel::QtPropertyModel(QObject *parent)
	: QAbstractItemModel (parent) , rootProperty(nullptr), parentIsQObject(true)
{
	rootProperty = new QVariantQObjectProperty(parent,QMetaProperty(),this, 0, nullptr);
	
}

QtPropertyModel::QtPropertyModel(const QVariant& parent)
	: QAbstractItemModel (nullptr) , rootProperty(nullptr), parentIsQObject(false)
{
	ParentObject* p = new ParentObject(parent,this);
	rootProperty = new QVariantObjectSuperClassProperty(p,p->metaObject(),this,0);
	
}

QtPropertyModel::~QtPropertyModel()
{
	delete rootProperty;
}

bool QtPropertyModel::hasChildren(const QModelIndex & parent) const
{

	QVariantProperty* qproperty = getProperty(parent);

	if(qproperty != nullptr)
	{
		bool hasinfs =qproperty->hasChildren();
		return hasinfs;
	}

	return false;
}

int QtPropertyModel::rowCount(const QModelIndex &parent) const
{
	QVariantProperty* qproperty = getProperty(parent);

	if(qproperty != nullptr)
	{
		return qproperty->getRowCount();
	}

	return 0;
}

int QtPropertyModel::columnCount(const QModelIndex &parent) const
{
	return 2;
}

QModelIndex QtPropertyModel::index(int row, int column, const QModelIndex & parent) const	
{
	if (parent.isValid() && parent.column() != 0)
		return QModelIndex();

	QVariantProperty* parentItem  = getProperty(parent);

	const QList<QVariantProperty*> children = parentItem->childProperties();

	if(row > -1 && row < children.count())
	{
		QVariantProperty *temp = children[row];
		QModelIndex tempindex = createIndex(row, column, temp);
	
		if(column == 0)
		temp->setModelIndex(tempindex);

		return tempindex;
	}
	

	return QModelIndex();
}

QModelIndex QtPropertyModel::parent(const QModelIndex &index) const
{
	QModelIndex returnIndex;

	if(index.isValid())
	{
		QVariantProperty* qproperty = getProperty(index);

		if(qproperty != nullptr )
		{
			QVariantProperty* parentProp = static_cast<QVariantProperty*>(qproperty->parent());

			if(parentProp != nullptr)
			{
				if(parentProp != rootProperty)
				{
					returnIndex = createIndex(parentProp->getRowInParent(), 0, parentProp);
					parentProp->setModelIndex(returnIndex);
				}
			}
		}
	}

	return returnIndex;
}

QVariant  QtPropertyModel::data(const QModelIndex & index, int role) const
{

	if(index.isValid())
	{
		QVariantProperty* qproperty = getProperty(index);

		if(qproperty != nullptr)
		{
			return qproperty->getData((Qt::ItemDataRole)role, (QVariantProperty::Column)index.column());
		}
	}

	return QVariant();
}

bool QtPropertyModel::setData(const QModelIndex & index, const QVariant & value, int role)
{	
	if(index.column() == 0)
		return false;

	QVariantProperty* qproperty = getProperty(index);

	if(qproperty)
	{
		bool valid = qproperty->setData(value,(Qt::ItemDataRole)role,(QVariantProperty::Column)index.column());

		if(valid)
		{
			emit dataChanged(index,index);
			
			return valid;
		}
	}

	return false;
}

QVariantProperty*  QtPropertyModel::getProperty(const QModelIndex & index) const
{

	if(index.isValid())
	{
		QVariantProperty* qvproperty = nullptr;
		qvproperty = static_cast<QVariantProperty*>(index.internalPointer());

		if(qvproperty != nullptr)
		{
			return qvproperty;
		}
	}

	return rootProperty;

}

QVariant QtPropertyModel::headerData(int section, Qt::Orientation orientation, int role) const
{

	if (orientation == Qt::Horizontal )
	{
		switch(section)
		{
		case 0:
			switch (role)
			{
			case Qt::DisplayRole:
			case Qt::ToolTipRole:
			case Qt::StatusTipRole:
				return QString("Property");
				break;
			case Qt::WhatsThisRole:
				return QString("Column for name of property");
				break;
			}
			break;
		case 1:
			switch (role)
			{
			case Qt::DisplayRole:
			case Qt::ToolTipRole:
			case Qt::StatusTipRole:
				return QString("Value");
				break;
			case Qt::WhatsThisRole:
				return QString("Column for value of property");
				break;
			}
			break;
		}
	}

	return QVariant();
}

Qt::ItemFlags QtPropertyModel::flags(const QModelIndex & index) const
{
	if(index.column() == 1)
	{
		QVariantProperty* qproperty = getProperty(index);

		if(qproperty != nullptr)
		{
			return qproperty->flags();
		}
	}
	return Qt::ItemIsEnabled|Qt::ItemIsSelectable;
}

QVariant QtPropertyModel::getRootValue() const
{
	if(parentIsQObject)
	{
		return rootProperty->getData();
	}
	else
	{
		ParentObject* inputObject = qvariant_cast<ParentObject*>(rootProperty->getData());
		return inputObject->getValue();
	}
}

QVariantProperty* QtPropertyModel::getRootProperty() const
{
	return rootProperty;

}
