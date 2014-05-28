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

QFontVariantProperty::QFontVariantProperty(const QFont& value, const QMetaProperty& metaProperty, QVariantProperty *parent)
  : QVariantProperty(value,metaProperty,parent)
{

}

QFontVariantProperty::~QFontVariantProperty()
{

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

void QFontVariantProperty::childPropertyValueChanged(const QString& propertyName, const QVariant& value)
{
	
	if(value.isValid())
	{
		childPropertyCalledUpdate = true;
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

void QFontVariantProperty::setupChildProperties()
{
	QFont& currentFont = qvariant_cast<QFont>(value);
	
	if(!propertiesSet)
	{
		qDeleteAll(children);
		children.clear();

		QVariantProperty* fam = new QFontFamilyProperty("Family",1,currentFont.family(),this);
		fam->setModel(model);
		fam->setDefaultFlags(flags());
		children.append(fam);
		connect(fam ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
		SLOT(childPropertyValueChanged(QString , QVariant)));

		int p = currentFont.pointSize();
		QVariantProperty* psize = new QVariantProperty(p,QMetaProperty(),this);
		psize->setModel(model);
		psize->setRowInParent(2);
		psize->setDefaultFlags(flags());
		psize->setPropertyName("Point Size");
		children.append(psize);
		connect(psize ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
		SLOT(childPropertyValueChanged(QString , QVariant)));

		QVariantProperty* bold = new QBoolVariantProperty(currentFont.bold(),QMetaProperty(),this);
		bold->setModel(model);
		bold->setRowInParent(3);
		bold->setPropertyName("Bold");
		bold->setDefaultFlags(flags());
		children.append(bold);
		connect(bold ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
		SLOT(childPropertyValueChanged(QString , QVariant)));

		QVariantProperty* italic = new QBoolVariantProperty(currentFont.italic(),QMetaProperty(),this);
		italic->setModel(model);
		italic->setRowInParent(4);
		italic->setDefaultFlags(flags());
		italic->setPropertyName("Italic");
		children.append(italic);
		connect(italic ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
		SLOT(childPropertyValueChanged(QString , QVariant)));
		
		QVariantProperty* underline = new QBoolVariantProperty(currentFont.underline(),QMetaProperty(),this);
		underline->setModel(model);
		underline->setRowInParent(5);
		underline->setDefaultFlags(flags());
		underline->setPropertyName("Underline");
		children.append(underline);
		connect(underline ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
		SLOT(childPropertyValueChanged(QString , QVariant)));

		QVariantProperty* strikeout = new QBoolVariantProperty(currentFont.strikeOut(),QMetaProperty(),this);
		strikeout->setModel(model);
		strikeout->setRowInParent(6);
		strikeout->setDefaultFlags(flags());
		strikeout->setPropertyName("Strikeout");
		children.append(strikeout);
		connect(strikeout ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
			SLOT(childPropertyValueChanged(QString , QVariant)));

		QVariantProperty* Kerning = new QBoolVariantProperty(currentFont.kerning(),QMetaProperty(),this);
	    Kerning->setModel(model);	Kerning->setRowInParent(7);
		Kerning->setPropertyName("Kerning");
		Kerning->setDefaultFlags(flags());
		children.append(Kerning);
		connect(Kerning ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
			SLOT(childPropertyValueChanged(QString , QVariant)));


		propertiesSet = true;
	}
	else 
	{
		QVariantProperty* ch = children[0];
		ch->blockSignals(true);
		ch->setData(currentFont.family());
		ch->blockSignals(false);
		QModelIndex index = ch->getModelIndex();
		

		ch = children[1];
		ch->blockSignals(true);
		int p = currentFont.pointSize();
		ch->setData(p);
		ch->blockSignals(false);
		index = ch->getModelIndex();
		//emit model->dataChanged(index , index);


		ch = children[2];
		ch->blockSignals(true);
		ch->setData(currentFont.bold());
		ch->blockSignals(false);
		index = ch->getModelIndex();
		//emit model->dataChanged(index , index);

	    ch = children[3];
		ch->blockSignals(true);
		ch->setData(currentFont.italic());
		ch->blockSignals(false);
		index = ch->getModelIndex();
		//emit model->dataChanged(index , index);


	    ch = children[4];
		ch->blockSignals(true);
		ch->setData(currentFont.underline());
		ch->blockSignals(false);
		index = ch->getModelIndex();
		//emit model->dataChanged(index , index);


	    ch = children[5];
		ch->blockSignals(true);
		ch->setData(currentFont.strikeOut());
		ch->blockSignals(false);
		index = ch->getModelIndex();
		//emit model->dataChanged(index , index);


		ch = children[6];
		ch->blockSignals(true);
		ch->setData(currentFont.kerning());
		ch->blockSignals(false);
		index = ch->getModelIndex();
		//emit model->dataChanged(index , index);

	}
}