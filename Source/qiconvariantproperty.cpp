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
#include "qiconvariantproperty.h"
#include "qpixmapvariantproperty.h"

QIconVariantProperty::QIconVariantProperty(const QIcon& value, const QMetaProperty& metaProperty,QtPropertyModel* const &  model, int row,  QVariantProperty *parent)
	: QVariantProperty(value , metaProperty , model, row , parent)
{

}

QIconVariantProperty::~QIconVariantProperty()
{

}

bool QIconVariantProperty::hasChildren() 
{
	return true;
}

QVariant QIconVariantProperty::getData(Qt::ItemDataRole role , Column column)
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
			return value;
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

Qt::ItemFlags QIconVariantProperty::flags() const
{
	Qt::ItemFlags flags = Qt::ItemIsSelectable ;

	if(metaProperty.isValid()) 
	{
		if(metaProperty.isWritable())
			flags = flags| Qt::ItemIsEnabled | Qt::ItemIsEditable;
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

void QIconVariantProperty::setupChildProperties()
{
	QIcon& currentIcon = qvariant_cast<QIcon>(this->value);
	QSize outrageousSize = QSize(15000,15000);

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

		for(int i =0 ; i < 8 ; i++)
		{

			switch (i)	
			{
			case 0:
				{
					QString propName = "Normal On";
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Normal, QIcon::State::On);
					QVariantProperty* tempProp = new QPixmapVariantProperty(pixvalue,QMetaProperty(),model, i, this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 1:
				{
					QString propName = "Normal Off";
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Normal, QIcon::State::Off);
					QVariantProperty* tempProp = new QPixmapVariantProperty(pixvalue,QMetaProperty(),model, i, this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 2:
				{
					QString propName = "Active On";
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Active, QIcon::State::On);
					QVariantProperty* tempProp = new QPixmapVariantProperty(pixvalue,QMetaProperty(),model, i, this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 3:
				{
					QString propName = "Active Off";
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Active, QIcon::State::Off);
					QVariantProperty* tempProp = new QPixmapVariantProperty(pixvalue,QMetaProperty(),model, i, this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 4:
				{
					QString propName = "Selected On";
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Selected, QIcon::State::On);
					QVariantProperty* tempProp = new QPixmapVariantProperty(pixvalue,QMetaProperty(),model, i, this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 5:
				{
					QString propName = "Selected Off";
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Selected, QIcon::State::Off);
					QVariantProperty* tempProp = new QPixmapVariantProperty(pixvalue,QMetaProperty(),model, i, this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 6:
				{
					QString propName = "Disabled On";
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Disabled, QIcon::State::On);
					QVariantProperty* tempProp = new QPixmapVariantProperty(pixvalue,QMetaProperty(),model, i, this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 7:
				{
					QString propName = "Disabled Off";
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Disabled, QIcon::State::Off);
					QVariantProperty* tempProp = new QPixmapVariantProperty(pixvalue,QMetaProperty(),model, i, this);
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

				if(propertyName == "Normal On")
				{
					tval = currentIcon.pixmap(outrageousSize , QIcon::Mode::Normal, QIcon::State::On);
				}
				else if(propertyName == "Normal Off")
				{
					tval = currentIcon.pixmap(outrageousSize , QIcon::Mode::Normal, QIcon::State::Off);
				}
				else if(propertyName == "Active On")
				{
					tval = currentIcon.pixmap(outrageousSize , QIcon::Mode::Active, QIcon::State::On);
				}
				else if(propertyName == "Active Off")
				{
					tval = currentIcon.pixmap(outrageousSize , QIcon::Mode::Active, QIcon::State::Off);
				}
				else if(propertyName == "Selected On")
				{
					tval = currentIcon.pixmap(outrageousSize , QIcon::Mode::Selected, QIcon::State::On);
				}
				else if(propertyName == "Selected Off")
				{
					tval = currentIcon.pixmap(outrageousSize , QIcon::Mode::Selected, QIcon::State::Off);
				}
				else if(propertyName == "Disabled On")
				{
					tval = currentIcon.pixmap(outrageousSize , QIcon::Mode::Disabled, QIcon::State::On);
				}
				else if(propertyName == "Disabled Off")
				{
					tval = currentIcon.pixmap(outrageousSize , QIcon::Mode::Disabled, QIcon::State::Off);
				}

				prop->blockSignals(true);
				prop->setData(tval);
				prop->blockSignals(false);
			}

			emit this->model->dataChanged(children[0]->getModelIndex(),children[children.count()-1]->getModelIndex());
		}
				}
}

void QIconVariantProperty::childPropertyValueChanged(const QString& propertyName, const QVariant& value)
{
	if(value.isValid())
	{
		QIcon& currentIcon = qvariant_cast<QIcon>(this->value);
		QPixmap pixvalue = qvariant_cast<QPixmap>(value);

		if(propertyName == "Normal On")
		{
			currentIcon.addPixmap(pixvalue , QIcon::Mode::Normal, QIcon::State::On);
		}
		else if(propertyName == "Normal Off")
		{
			currentIcon.addPixmap(pixvalue , QIcon::Mode::Normal, QIcon::State::Off);
		}
		else if(propertyName == "Active On")
		{
			currentIcon.addPixmap(pixvalue, QIcon::Mode::Active, QIcon::State::On);
		}
		else if(propertyName == "Active Off")
		{
			currentIcon.addPixmap(pixvalue, QIcon::Mode::Active, QIcon::State::Off);
		}
		else if(propertyName == "Selected On")
		{
			currentIcon.addPixmap(pixvalue, QIcon::Mode::Selected, QIcon::State::On);
		}
		else if(propertyName == "Selected Off")
		{
			currentIcon.addPixmap(pixvalue, QIcon::Mode::Selected, QIcon::State::Off);
		}
		else if(propertyName == "Disabled On")
		{
			currentIcon.addPixmap(pixvalue, QIcon::Mode::Disabled, QIcon::State::On);
		}
		else if(propertyName == "Disabled Off")
		{
			currentIcon.addPixmap(pixvalue, QIcon::Mode::Disabled, QIcon::State::Off);
		}

		this->value = currentIcon;
		emit model->dataChanged(modelIndex , modelIndex);
		emit valueChangedSignal(this->propertyName,this->value);
	}
}