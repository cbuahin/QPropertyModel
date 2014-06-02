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
#include "qpointfvariantproperty.h"

QPointFVariantProperty::QPointFVariantProperty(const QPointF& value, const QMetaProperty& metaProperty,QtPropertyModel* const &  model, int row, QVariantProperty *parent )
	: QVariantProperty(value,metaProperty,model,row ,parent)
{
	setQPointFPropertyFunctions["X"] = & QPointF::setX;
	setQPointFPropertyFunctions["Y"] = &  QPointF::setY;

	getQPointFPropertyFunctions["X"] = & QPointF::x;
	getQPointFPropertyFunctions["Y"] = & QPointF::y;

}

QPointFVariantProperty::~QPointFVariantProperty()
{
	setQPointFPropertyFunctions.clear();
	getQPointFPropertyFunctions.clear();
}

bool QPointFVariantProperty::hasChildren()
{
	return true;
}

QVariant QPointFVariantProperty::getData(Qt::ItemDataRole role , Column column)
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
			return QVariant();
			break;
		case Qt::DisplayRole:
		case Qt::ToolTipRole:
		case Qt::StatusTipRole:
		case Qt::WhatsThisRole:
			{
				QPointF temp = qvariant_cast<QPointF>(value);
				return "[X = "+ QString::number(temp.x()) +", Y = "+  QString::number(temp.y()) +"]";
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

Qt::ItemFlags QPointFVariantProperty::flags() const
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

void QPointFVariantProperty::setupChildProperties()
{
	QPointF& currentSize = qvariant_cast<QPointF>(value);

	if(!childPropertiesSet)
	{
		if(children.count() > 0)
		{	
			qDeleteAll(children);
			children.clear();
		}

		QStringList properties = getQPointFPropertyFunctions.keys(); 

		Qt::ItemFlags flagsv = flags();
		if((metaProperty.isValid() && metaProperty.isWritable()) || defaultFlags.testFlag(Qt::ItemIsEditable))
		{
			flagsv |= Qt::ItemIsEditable;
		}

		for(int i =0 ; i < properties.count() ; i++)
		{
			QString propName = properties[i];
			GetQPointFProperty prop =getQPointFPropertyFunctions[propName];
			qreal value = (currentSize.*prop)();
			QVariantProperty* tempProp = new QVariantProperty(value,QMetaProperty(),model, i, this);
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
				QString propertyName = prop->getPropertyName();
				GetQPointFProperty propf =getQPointFPropertyFunctions[propertyName];
				QVariant tval = (currentSize.*propf)(); ;
				prop->blockSignals(true);
				prop->setData(tval);
				prop->blockSignals(false);

			}

			emit this->model->dataChanged(children[0]->getModelIndex(),children[children.count()-1]->getModelIndex());
		}
	}
}

void QPointFVariantProperty::childPropertyValueChanged(const QString& propertyName, const QVariant& value)
{
	if(value.isValid())
	{

		QPointF currentSize = qvariant_cast<QPointF>(this->value);
		if(setQPointFPropertyFunctions.contains(propertyName))
		{
			SetQPointFProperty method = setQPointFPropertyFunctions[propertyName];
   
			(currentSize.*method)(value.toReal());
		}

		this->value = currentSize;
		emit model->dataChanged(modelIndex , modelIndex);
		emit valueChangedSignal(this->propertyName,this->value);
	}
}