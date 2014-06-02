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
#include "qvariantqobjectproperty.h"
#include <QVariantObjectSuperClassProperty.h>
#include <TestObject.h>

QVariantQObjectProperty::QVariantQObjectProperty(QObject* const & object, const QMetaProperty& qproperty,QtPropertyModel* const &  model, int row, QVariantProperty* parent)
	: QVariantProperty(QVariant::fromValue(object), qproperty, model, row, parent),
	object(nullptr)
{
	this->object = object;
	columnCount = 2;
}

QVariantQObjectProperty::~QVariantQObjectProperty()
{

}

bool QVariantQObjectProperty::hasChildren()
{
	if(object != nullptr)
	{
		const QMetaObject* current = object->metaObject();

		QList<const QMetaObject*> childClasses ;

		childClasses.append(current);

		while((current = current->superClass()))
		{
			const QMetaObject* temp = current;
			childClasses.insert(0,temp);
		}
		 
		if(childClasses.count() > 0)
			return true;
	}

	return false;
}

QVariant QVariantQObjectProperty::getData(Qt::ItemDataRole  role , Column column)
{
	switch (column)
	{
	case QVariantProperty::PropertyNameColumn:
		switch (role)
		{
		case Qt::DecorationRole:
			return QVariant();
			break;
		case Qt::EditRole:
			return QVariant();
			break;
		case Qt::DisplayRole:
		case Qt::ToolTipRole:
		case Qt::StatusTipRole:
		case Qt::WhatsThisRole:
			{
				return QVariant(metaProperty.name());
			}
			break;
		case Qt::FontRole:
			return QVariant();
			break;
		case Qt::TextAlignmentRole:
			return QVariant();
			break;
		case Qt::BackgroundRole:
			return QBrush(Qt::gray);
			break;
		case Qt::ForegroundRole:
			return QBrush(Qt::white);
			break;
		case Qt::CheckStateRole:
			return QVariant();
			break;
		case Qt::AccessibleTextRole:
			return QVariant();
			break;
		case Qt::AccessibleDescriptionRole:
			return QVariant();
			break;
		case Qt::SizeHintRole:
			return QVariant();
			break;
		case Qt::InitialSortOrderRole:
			return QVariant();
			break;
		}
		break;

	case QVariantProperty::PropertyValueColumn:

		switch (role)
		{
		case Qt::DecorationRole:
			return QVariant();
			break;
		case Qt::EditRole:
			return QVariant();
			break;
		case Qt::DisplayRole:
		case Qt::ToolTipRole:
		case Qt::StatusTipRole:
		case Qt::WhatsThisRole:
			{
				return QVariant(metaProperty.typeName());
			}
			break;
		case Qt::FontRole:
			return QVariant();
			break;
		case Qt::TextAlignmentRole:
			return QVariant();
			break;
		case Qt::BackgroundRole:
			return QBrush(Qt::gray);
			break;
		case Qt::ForegroundRole:
			return QVariant();
			break;
		case Qt::CheckStateRole:
			return QVariant();
			break;
		case Qt::AccessibleTextRole:
			return QVariant();
			break;
		case Qt::AccessibleDescriptionRole:
			return QVariant();
			break;
		case Qt::SizeHintRole:
			return QVariant();
			break;
		case Qt::InitialSortOrderRole:
			return QVariant();
			break;
		}

		break;
	}

	return QVariant();
}

QObject* QVariantQObjectProperty::getObject() const 
{
	return object;
}

bool QVariantQObjectProperty::setData(const QVariant & value, Qt::ItemDataRole  role, Column column)
{
	QObject* parent = QVariantProperty::parent();

	if(parent != nullptr && role == Qt::EditRole && column == Column::PropertyValueColumn)
	{
		QVariantProperty* parentProp = qobject_cast<QVariantProperty*>(parent);

		if(parentProp != nullptr)
		{
			QObject* head  = parentProp->getObject();

			if(head != nullptr)
			{
				bool written = metaProperty.write(head, value);

				if(written)
				{
					this->value = value;
					emit valueChangedSignal(propertyName,this->value);
					setupChildProperties();
				}

				return written;
			}

		}
	}

	return false;
}

Qt::ItemFlags QVariantQObjectProperty::flags() const
{
	Qt::ItemFlags flags =  Qt::ItemIsSelectable;

	if(metaProperty.isValid() && metaProperty.isWritable())
	{
		flags = flags |Qt::ItemIsEnabled;
	}

	return flags;
}

void QVariantQObjectProperty::setupChildProperties()
{
	if(object != nullptr)
	{
		if(!childPropertiesSet)
		{
			const QMetaObject* current = object->metaObject();

			QList<const QMetaObject*> childClasses ;

			childClasses.append(current);

			while((current = current->superClass()))
			{
				const QMetaObject* temp = current;
				childClasses.insert(0,temp);
			}

			int size  = childClasses.count();

			for(int i = 0; i < size ; i++)
			{
				QVariantProperty* qproperty = new QVariantObjectSuperClassProperty(object,childClasses[i], model, i ,this);
				children.append(qproperty);
			}

			childPropertiesSet = true;
		}
		else
		{

		}
	}
}