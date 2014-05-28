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

QBoolVariantProperty::QBoolVariantProperty(const bool& value, const QMetaProperty& metaProperty, QVariantProperty *parent)
	: QVariantProperty(value,metaProperty,parent)
{
	defaultFlags = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
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
		case Qt::DisplayRole:
		case Qt::EditRole:
			return QVariant();
			break;
		case Qt::ToolTipRole:
		case Qt::StatusTipRole:
		case Qt::WhatsThisRole:
		     return value;
			break;
		case Qt::DecorationRole:
			return QVariant();
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
			if(value.toInt() == 0)
				return Qt::CheckState::Unchecked;
			else
				return Qt::CheckState::Checked;
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

		if(parent != nullptr && column == Column::PropertyValueColumn)
		{
			switch(role)
			{
			case Qt::EditRole:
				{
					QVariantProperty* parentProp = qobject_cast<QVariantProperty*>(parent);

					if(parentProp != nullptr)
					{
						QObject* head  = parentProp->getObject();

						if(head != nullptr)
						{
							bool written = metaProperty.write(head, qvariant_cast<bool>(value));
							
							if(written)
							{
								this->value = value.toBool();
								emit valueChangedSignal(propertyName,this->value);
								emit valueChangedSignal();
							}
							
							return written;
						}
					}
				}
				break;
			case Qt::CheckStateRole:
				{
					QVariantProperty* parentProp = qobject_cast<QVariantProperty*>(parent);

					if(parentProp != nullptr)
					{
						QObject* head  = parentProp->getObject();

						if(head != nullptr)
						{
							bool v = value.toInt() == 0 ? false : true;
							bool written = metaProperty.write(head, v);

							if(written)
							{
								this->value = v;
								emit valueChangedSignal(propertyName,this->value);
								emit valueChangedSignal();
							}

							return written;
						}
					}
				}
			}
		}

		return false;
	}
	else
	{
		switch(role)
		{
		case Qt::EditRole:
			{
				this->value = value.toBool();
			}
			break;
		case Qt::CheckStateRole:
			{
				bool v = value.toInt() == 0 ? false : true;
				this->value = v;
				emit valueChangedSignal(propertyName,this->value);
			}
		}

		emit valueChangedSignal(propertyName,this->value);
		emit valueChangedSignal();
		return true;
	}

}

void QBoolVariantProperty::setDefaultFlags(Qt::ItemFlags flags)
{

	defaultFlags = Qt::ItemIsSelectable;

	if(flags.testFlag(Qt::ItemIsEditable))
		defaultFlags |= Qt::ItemIsEnabled| Qt::ItemIsUserCheckable;
}

Qt::ItemFlags QBoolVariantProperty::flags() const
{
	Qt::ItemFlags flags = Qt::ItemIsSelectable ;

	if(metaProperty.isValid()) 
	{
		if(metaProperty.isWritable())
			flags = flags | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable   ;
	}
	else
	{
		return defaultFlags ;
	}

	return flags;
}