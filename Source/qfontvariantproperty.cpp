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
#include "qfontvariantproperty.h"
#include <qfontfamilyproperty.h>
#include <qboolvariantproperty.h>

QFontVariantProperty::QFontVariantProperty(const QFont& value, const QMetaProperty& metaProperty,QtPropertyModel* const &  model, int row, QVariantProperty *parent)
  : QVariantProperty(value,metaProperty,model,row, parent)
{

}

QFontVariantProperty::~QFontVariantProperty()
{

}

bool QFontVariantProperty::hasChildren() 
{
	return true;
}

QVariant QFontVariantProperty::getData(Qt::ItemDataRole role , Column column)
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
			{
				QFont temp = qvariant_cast<QFont>(value);
				QString name = "[" + temp.family() +", "+ QString::number(temp.pointSize()) + " ]";
				return name;
			}
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
			{
				QFont temp = qvariant_cast<QFont>(value);
				if(temp.italic())
				{
					qDebug()<<"";
				}
				
				return temp;
			}
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

void QFontVariantProperty::setupChildProperties()
{
	QFont& currentFont = qvariant_cast<QFont>(value);

	if(!childPropertiesSet)
	{
		if(children.count() > 0)
		{	
			qDeleteAll(children);
			children.clear();
		}

		QVariantProperty* fam = new QFontFamilyProperty("Family",currentFont.family(),model, 0,this);
		fam->setDefaultFlags(flags());
		children.append(fam);
		connect(fam ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
			SLOT(childPropertyValueChanged(QString , QVariant)));

		int p = currentFont.pointSize();
		QVariantProperty* psize = new QVariantProperty(p,QMetaProperty(),model, 1,this);
		psize->setDefaultFlags(flags());
		psize->setPropertyName("Point Size");
		children.append(psize);
		connect(psize ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
			SLOT(childPropertyValueChanged(QString , QVariant)));

		QVariantProperty* bold = new QBoolVariantProperty(currentFont.bold(),QMetaProperty(),model,2,this);
		bold->setPropertyName("Bold");
		bold->setDefaultFlags(flags());
		children.append(bold);
		connect(bold ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
			SLOT(childPropertyValueChanged(QString , QVariant)));

		QVariantProperty* italic = new QBoolVariantProperty(currentFont.italic(),QMetaProperty(),model,3,this);
		italic->setDefaultFlags(flags());
		italic->setPropertyName("Italic");
		children.append(italic);
		connect(italic ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
			SLOT(childPropertyValueChanged(QString , QVariant)));

		QVariantProperty* underline = new QBoolVariantProperty(currentFont.underline(),QMetaProperty(),model,4,this);
		underline->setDefaultFlags(flags());
		underline->setPropertyName("Underline");
		children.append(underline);
		connect(underline ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
			SLOT(childPropertyValueChanged(QString , QVariant)));

		QVariantProperty* strikeout = new QBoolVariantProperty(currentFont.strikeOut(),QMetaProperty(),model,5,this);
		strikeout->setDefaultFlags(flags());
		strikeout->setPropertyName("Strikeout");
		children.append(strikeout);
		connect(strikeout ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
			SLOT(childPropertyValueChanged(QString , QVariant)));

		QVariantProperty* Kerning = new QBoolVariantProperty(currentFont.kerning(),QMetaProperty(),model,6,this);
		Kerning->setPropertyName("Kerning");
		Kerning->setDefaultFlags(flags());
		children.append(Kerning);
		connect(Kerning ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
			SLOT(childPropertyValueChanged(QString , QVariant)));

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

				if(propertyName == "Family")
				{
					tval =	currentFont.family();
				}
				else if(propertyName == "Point Size")
				{
					tval =	currentFont.pointSize();
				}
				else if(propertyName == "Bold")
				{
					tval =	currentFont.bold();
				}
				else if(propertyName == "Italic")
				{
					tval =	currentFont.italic();
				}
				else if(propertyName == "Underline")
				{
					tval =	currentFont.underline();
				}
				else if(propertyName == "Strikeout")
				{
					tval =	currentFont.strikeOut();
				}
				else if(propertyName == "Kerning")
				{
					tval =	currentFont.kerning();
				}

				prop->blockSignals(true);
				prop->setData(tval);
				prop->blockSignals(false);
			}

			emit this->model->dataChanged(children[0]->getModelIndex(),children[children.count()-1]->getModelIndex());
		}
	}
}

void QFontVariantProperty::childPropertyValueChanged(const QString& propertyName, const QVariant& value)
{
	
	if(value.isValid())
	{
		QFont currentFont = qvariant_cast<QFont>(this->value);

		if(propertyName == "Family")
		{
			currentFont.setFamily(value.toString());
		}
		else if(propertyName == "Point Size")
		{
			currentFont.setPointSize(value.toInt());
		}
		else if(propertyName == "Bold")
		{
			currentFont.setBold(value.toBool());
		}
		else if(propertyName == "Italic")
		{
			currentFont.setItalic(value.toBool());
		}
		else if(propertyName == "Underline")
		{
			currentFont.setUnderline(value.toBool());
		}
		else if(propertyName == "Strikeout")
		{
			currentFont.setStrikeOut(value.toBool());
		}
		else if(propertyName == "Kerning")
		{
			currentFont.setKerning(value.toBool());
		}

		QVariantProperty::setData(currentFont);

	}

}
