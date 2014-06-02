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
#include "qpenvariantproperty.h"
#include <qenumvariantproperty.h>
#include <qcolorvariantproperty.h>
#include <qbrushvariantproperty.h>
#include <qboolvariantproperty.h>

QPenVariantProperty::QPenVariantProperty(const QPen& value, const QMetaProperty& metaProperty,QtPropertyModel* const &  model, int row, QVariantProperty *parent)
	: QVariantProperty(value,metaProperty,model, row,parent)
{

}

QPenVariantProperty::~QPenVariantProperty()
{

}

bool QPenVariantProperty::hasChildren()
{
	return true;
}

QVariant QPenVariantProperty::getData(Qt::ItemDataRole role , Column column)
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
		case Qt::DisplayRole:
			return QVariant();
			break;
		case Qt::DecorationRole:
			return QVariant();
			break;
		case Qt::EditRole:
			return value;
			break;
		case Qt::ToolTipRole:
			return QVariant();
			break;
		case Qt::StatusTipRole:
			return QVariant();
			break;
		case Qt::WhatsThisRole:
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

Qt::ItemFlags QPenVariantProperty::flags() const
{
	Qt::ItemFlags flags = Qt::ItemIsSelectable ;

	if(metaProperty.isValid()) 
	{
		if(metaProperty.isWritable())
			flags = flags| Qt::ItemIsEnabled;
	}
	else
	{
		if(defaultFlags.testFlag(Qt::ItemIsEditable))
		{
			return Qt::ItemIsSelectable | Qt::ItemIsEnabled ;
		}
		else
		{
			return flags  ;
		}
	}

	return flags;
}

void QPenVariantProperty::setupChildProperties()
{
	QPen currentPen = qvariant_cast<QPen>(this->value);

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

		for(int i = 0 ; i < 7 ; i++)
		{

			switch (i)	
			{
			case 0:
				{
					QString propName = "Width";
					qreal width = currentPen.widthF();
					QVariantProperty* tempProp = new QVariantProperty(width, QMetaProperty(),model, i, this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 1:
				{
					QString propName = "Miter Limit";
					qreal mlimit = currentPen.miterLimit();
					QVariantProperty* tempProp = new QVariantProperty(mlimit, QMetaProperty(),model, i, this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 2:
				{
					QString propName = "Cosmetic";
					bool cosmetic = currentPen.isCosmetic();
					QVariantProperty* tempProp = new QBoolVariantProperty(cosmetic, QMetaProperty(),model, i, this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 3:
				{
					QString propName = "Brush";
					QBrush brush = currentPen.brush();
					QVariantProperty* tempProp = new QBrushVariantProperty(brush, QMetaProperty(),model, i, this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 4:
				{
					QString propName = "Pen Style";
					const QMetaObject& globalObject =  StaticQtMetaObject::get();
					int index = globalObject.indexOfEnumerator("PenStyle");
					QMetaEnum enumeration = globalObject.enumerator(index);
					int pstyle = currentPen.style();

					QVariantProperty* tempProp = new QEnumVariantProperty(pstyle,enumeration,QMetaProperty(),model, i, this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 5:
				{
					QString propName = "Pen Cap Style";
					const QMetaObject& globalObject =  StaticQtMetaObject::get();
					int index = globalObject.indexOfEnumerator("PenCapStyle");
					QMetaEnum enumeration = globalObject.enumerator(index);
					int capstyle = currentPen.style();

					QVariantProperty* tempProp = new QEnumVariantProperty(capstyle,enumeration,QMetaProperty(),model, i, this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 6:
				{
					QString propName = "Pen Join Style ";
					const QMetaObject& globalObject =  StaticQtMetaObject::get();
					int index = globalObject.indexOfEnumerator("PenJoinStyle");
					QMetaEnum enumeration = globalObject.enumerator(index);
					int pjoinstyle = currentPen.style();

					QVariantProperty* tempProp = new QEnumVariantProperty(pjoinstyle,enumeration,QMetaProperty(),model, i, this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			}
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
				QVariant tval ;


				if(propertyName == "Width")
				{
					tval = currentPen.widthF();

				}
				else if(propertyName == "Miter Limit")
				{
					tval = currentPen.miterLimit();
				}
				else if(propertyName == "Cosmetic")
				{
					tval = currentPen.isCosmetic();
				}		
				else if(propertyName == "Brush")
				{
					tval = currentPen.brush();
				}	
				else if(propertyName == "Pen Style")
				{
					tval = (int)currentPen.style();
				}
				else if(propertyName == "Pen Cap Style")
				{
					tval = currentPen.capStyle();
				}
				else if(propertyName == "Pen Join Style")
				{
					tval = currentPen.joinStyle();
				}

				prop->blockSignals(true);
				prop->setData(tval);
				prop->blockSignals(false);
			}

			emit this->model->dataChanged(children[0]->getModelIndex(),children[children.count()-1]->getModelIndex());
		}
	}
}

void QPenVariantProperty::childPropertyValueChanged(const QString& propertyName, const QVariant& value)
{

	if(value.isValid())
	{
		QPen& currentPen = qvariant_cast<QPen>(this->value);

		if(propertyName == "Width")
		{
			qreal width = value.toReal();
			currentPen.setWidthF(width);

		}
		else if(propertyName == "Miter Limit")
		{
			qreal mlimit = value.toReal();
			currentPen.setMiterLimit(mlimit);
		}
		else if(propertyName == "Cosmetic")
		{
			bool cosmetic = value.toBool();
			currentPen.setCosmetic(cosmetic);
		}		
		else if(propertyName == "Brush")
		{
			QBrush brush = qvariant_cast<QBrush>(value);
			currentPen.setBrush(brush);
		}	
		else if(propertyName == "Pen Style")
		{
			Qt::PenStyle pstyle = (Qt::PenStyle)(value.toInt());
			currentPen.setStyle(pstyle);
		}
		else if(propertyName == "Pen Cap Style")
		{
			Qt::PenCapStyle pcapstyle = (Qt::PenCapStyle)(value.toInt());
			currentPen.setCapStyle(pcapstyle);
		}
		else if(propertyName == "Pen Join Style")
		{
			Qt::PenJoinStyle pjoinstyle = (Qt::PenJoinStyle)(value.toInt());
			currentPen.setJoinStyle(pjoinstyle);
		}

		this->value = currentPen;
		emit model->dataChanged(modelIndex , modelIndex);
		emit valueChangedSignal(this->propertyName,this->value);
	}
}