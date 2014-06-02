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
#include "qbrushvariantproperty.h"
#include <qcolorvariantproperty.h>
#include <qenumvariantproperty.h>
#include <qpixmapvariantproperty.h>

QBrushVariantProperty::QBrushVariantProperty(const QBrush& value, const QMetaProperty& metaProperty,QtPropertyModel* const &  model, int row, QVariantProperty *parent)
	: QVariantProperty(value,metaProperty,model,row,parent)
{

}

QBrushVariantProperty::~QBrushVariantProperty()
{

}

 bool QBrushVariantProperty::hasChildren()
 {
	 return true;
 }

QVariant QBrushVariantProperty::getData(Qt::ItemDataRole role , Column column)
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

Qt::ItemFlags QBrushVariantProperty::flags() const
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
			return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
		}
		else
		{
		   return flags  ;
		}
	}

	return flags;
}

void QBrushVariantProperty::setupChildProperties()
{
	QBrush& currentBrush = qvariant_cast<QBrush>(this->value);

	if(!childPropertiesSet)
	{

		int size = children.count();

		if(size > 0)
		{	
			qDeleteAll(children);
			children.clear();
		}

		Qt::ItemFlags flagsv = flags();
		if((metaProperty.isValid() && metaProperty.isWritable()) || defaultFlags.testFlag(Qt::ItemIsEditable))
		{
			flagsv |= Qt::ItemIsEditable;
		}

		for(int i = 0 ; i < 3 ; i++)
		{

			switch (i)	
			{
			case 0:
				{
					QString propName = "Color";
					QColor color = currentBrush.color();
					QVariantProperty* tempProp = new QColorVariantProperty(color,QMetaProperty(),model, i ,this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);
					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 1:
				{
					QString propName = "Brush Style";
					const QMetaObject& globalObject =  StaticQtMetaObject::get();
					int index = globalObject.indexOfEnumerator("BrushStyle");
					QMetaEnum enumeration = globalObject.enumerator(index);
					int bstyle = currentBrush.style();
					QVariantProperty* tempProp = new QEnumVariantProperty(bstyle,enumeration, QMetaProperty(), model, 1 ,this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));

				}
				break;
			case 2:
				{
					QString propName = "Texture Image";
					Qt::BrushStyle bstyle = currentBrush.style();

					QPixmap pixvalue = currentBrush.texture();
					QVariantProperty* tempProp = new QPixmapVariantProperty(pixvalue,QMetaProperty(),model, 2 , this);

					if(bstyle == Qt::BrushStyle::TexturePattern)
					{
						tempProp->setDefaultFlags(flagsv);
					}
					else
					{
						Qt::ItemFlags tempflag = Qt::ItemIsSelectable | Qt::ItemIsEditable;
						tempProp->setDefaultFlags(tempflag);
					}

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

		for(int i = 0 ; i < 3 ; i++)
		{
			QVariantProperty* tempProp =  children[i];

			switch (i)	
			{
			case 0:
				{
					QColor color = currentBrush.color();
					tempProp->blockSignals(true);
					tempProp->setData(color);
					tempProp->blockSignals(false);
				}
				break;
			case 1:
				{
					int bstyle = currentBrush.style();
					tempProp->blockSignals(true);
					tempProp->setData(bstyle);
					tempProp->blockSignals(false);
				}
				break;
			case 2:
				{
					Qt::BrushStyle bstyle = currentBrush.style();
					tempProp->blockSignals(true);
					tempProp->setData((int)bstyle);
					tempProp->blockSignals(false);
				}
				break;
			}
		}
		emit this->model->dataChanged(children[0]->getModelIndex(),children[children.count()-1]->getModelIndex());
	}
}

void QBrushVariantProperty::childPropertyValueChanged(const QString& propertyName, const QVariant& value)
{

	if(value.isValid())
	{
		QBrush currentBrush = qvariant_cast<QBrush>(this->value);

		if(propertyName == "Color")
		{
			currentBrush.setColor(qvariant_cast<QColor>(value)); 
		}
		else if(propertyName == "Brush Style")
		{
			Qt::BrushStyle style = (Qt::BrushStyle)(value.toInt());
			currentBrush.setStyle(style);

			Qt::ItemFlags flagsv = flags();

			if((metaProperty.isValid() && metaProperty.isWritable()) || defaultFlags.testFlag(Qt::ItemIsEditable))
			{
				if(style == Qt::BrushStyle::TexturePattern)
				{
				    flagsv |= Qt::ItemIsEditable;
				}
				else
				{
					flagsv = Qt::ItemIsSelectable | Qt::ItemIsEditable;
				}


				for(int i =0 ; i < children.count() ; i++)
				{
					QVariantProperty* prop =  children[i];

					if(prop->getPropertyName() == "Texture Image")
					{
						prop->setDefaultFlags(flagsv);
						break;
					}
				}
			}

		}
		else if(propertyName == "Texture Image")
		{

			currentBrush.setTexture(qvariant_cast<QPixmap>(value));
		}
		

		this->value = currentBrush;
		emit model->dataChanged(modelIndex , modelIndex);
		emit valueChangedSignal(this->propertyName,this->value);
	}
}