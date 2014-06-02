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
#include "qflagsvariantproperty.h"
#include "qboolvariantproperty.h"


QFlagsVariantProperty::QFlagsVariantProperty(const QVariant& value, const QMetaEnum& metaEnumProperty,const QMetaProperty& metaProperty,QtPropertyModel* const &  model, int row, QVariantProperty *parent)
	: QVariantProperty(value,metaProperty,model, row, parent)
{
	this->enumProperty = metaEnumProperty;
}

QFlagsVariantProperty::~QFlagsVariantProperty()
{

}

bool QFlagsVariantProperty::hasChildren() 
{
	if(enumProperty.isValid() && enumProperty.keyCount() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}

QVariant QFlagsVariantProperty::getData(Qt::ItemDataRole role , Column column)
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
				return propertyName;
			}
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
			return value;
			break;
		case Qt::DisplayRole:
		case Qt::ToolTipRole:
		case Qt::StatusTipRole:
		case Qt::WhatsThisRole:
			{
				QString name = enumProperty.valueToKeys(value.toInt());
				return name;
			}
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

void QFlagsVariantProperty::setupChildProperties()
{
	if(enumProperty.isValid())
	{
		if(!childPropertiesSet)
		{
			if(children.count() > 0)
			{	
				qDeleteAll(children);
				children.clear();
			}

			Qt::ItemFlags flagsv = flags();
			if((metaProperty.isValid() && metaProperty.isWritable()) || defaultFlags.testFlag(Qt::ItemIsEditable))
			{
				flagsv |= Qt::ItemIsEditable;
			}

			int max = enumProperty.keyCount();


			for(int i =0 ; i < max ; i++)
			{
				QString propName = enumProperty.key(i);
				int tval = enumProperty.value(i);

				bool set = (this->value.toInt() & tval) == tval && (tval!= 0 || this->value.toInt() == tval );

				QVariantProperty* tempProp = new QBoolVariantProperty(set,QMetaProperty(),model, i, this);
				tempProp->setDefaultFlags(flagsv);
				tempProp->setPropertyName(propName);
				children.append(tempProp);


				connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
					SLOT(childPropertyValueChanged(QString , QVariant)));
			}

			childPropertiesSet = true;
		}
		else
		{
			if(children.count() > 0)
			{
				for(int i =0 ; i < children.count() ;i++)
				{
					QVariantProperty* prop = children[i];
					int tval = enumProperty.keyToValue(prop->getPropertyName().toStdString().c_str());
					bool set = (this->value.toInt() & tval) == tval && (tval!= 0 || this->value.toInt() == tval );
					prop->blockSignals(true);
					prop->setData(set);
					prop->blockSignals(false);
				}

				emit this->model->dataChanged(children[0]->getModelIndex(),children[children.count()-1]->getModelIndex());
			}
		}
	}
}

Qt::ItemFlags QFlagsVariantProperty::flags() const
{
	Qt::ItemFlags flags = Qt::ItemIsSelectable ;

	if(metaProperty.isValid()) 
	{
		if(metaProperty.isWritable())
			flags = flags| Qt::ItemIsEnabled ;
	}
	else
	{
		if(defaultFlags.testFlag(Qt::ItemIsEditable))
		{
			return Qt::ItemIsSelectable | Qt::ItemIsEnabled  | Qt::ItemIsEditable;
		}
		else
		{
		   return flags  ;
		}
	}

	return flags;
}

void QFlagsVariantProperty::childPropertyValueChanged(const QString& propertyName, const QVariant& value)
{
	if(value.isValid())
	{

		int tvalue = 0;
		bool first = true;

		for (int i = 0; i < children.count() ; i++)
		{
			if(children[i]->getData().toBool())
			{
				QString tempName =children[i]->getPropertyName();
				int valtoapp = enumProperty.keyToValue(tempName.toStdString().c_str());
				tvalue = tvalue | valtoapp;
			}
		}

		this->value = tvalue;
		emit model->dataChanged(modelIndex , modelIndex);
		emit valueChangedSignal(this->propertyName,this->value);
	}
}