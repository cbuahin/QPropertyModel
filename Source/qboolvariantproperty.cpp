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
#include "qboolvariantproperty.h"

QBoolVariantProperty::QBoolVariantProperty(const QVariant& value, const QMetaProperty& metaProperty, QVariantProperty *parent)
	: QVariantProperty(value,metaProperty,parent)
{

}

QBoolVariantProperty::~QBoolVariantProperty()
{

}

QVariant QBoolVariantProperty::getData(Qt::ItemDataRole role , Column column)
{
	if(column ==  Column::PropertyValueColumn)
	{
		switch (role)
		{
		case Qt::DecorationRole:
			return QVariant();
			break;
		case Qt::DisplayRole:
			return QVariant();
			break;
		case Qt::EditRole:
			return QVariant();
			break;
		case Qt::ToolTipRole:
		case Qt::StatusTipRole:
		case Qt::WhatsThisRole:
		return value;
			break;
		case Qt::FontRole:
			return QVariant();
			break;
		case Qt::TextAlignmentRole:
			return QVariant();
			break;
		case Qt::BackgroundRole:
			return QVariant();
			break;
		case Qt::ForegroundRole:
			return QVariant();
			break;
		case Qt::CheckStateRole:
			if(value.toBool())
			{
				return Qt::CheckState::Checked;

			}
			else
			{
				return Qt::CheckState::Unchecked;
			}
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
		return QVariant();
	}
	else
	{
		return QVariantProperty::getData(role,column);
	}
}

bool QBoolVariantProperty::setData(const QVariant & value,Qt::ItemDataRole role, Column column)
{

	if(metaProperty.isValid())
	{

		QObject* parent = QVariantProperty::parent();

		if(parent != nullptr && (role == Qt::CheckStateRole || role == Qt::EditRole) && column == Column::PropertyValueColumn)
		{
			QVariantProperty* parentProp = qobject_cast<QVariantProperty*>(parent);

			QVariant temp = value.toInt() == 0 ? QVariant(false) : QVariant(true);

			if(parentProp != nullptr)
			{
				QObject* head  = qvariant_cast<QObject*>(parentProp->getData());

				if(head != nullptr)
				{
					bool written = metaProperty.write(head, temp);
					this->value = temp;
					return written;
				}
			}
		}
	}
	else
	{
		this->value = value;
		emit valueChangedSignal(propertyName,value);
		emit valueChangedSignal();
		return true;
	}

	return false;
}

Qt::ItemFlags QBoolVariantProperty::flags() const
{
	Qt::ItemFlags flags = Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled ;

	if(metaProperty.isValid() && metaProperty.isWritable())
	{
		flags = flags |Qt::ItemIsEnabled | Qt::ItemIsEditable;
	}
	return flags;
}