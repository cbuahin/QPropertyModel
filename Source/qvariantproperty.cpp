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
#include "qvariantproperty.h"

QVariantProperty::QVariantProperty(const QVariant& invalue, const QMetaProperty& metaprop , QtPropertyModel* const & model, int row, QVariantProperty *parent)
	: QObject(parent), canreset(true), rowInParent(row), columnCount(2), resetValue(invalue), value(invalue), 
	parentProperty(parent), metaProperty(metaprop), model(nullptr),rowCount(0),childPropertiesSet(false)
{

	this->model = model;

	if( this->metaProperty.isValid())
	{
		propertyName = this->metaProperty.name();
		QObject* parentQObject = parent->getObject();

		//notify change signal from parent
		if(parentQObject != nullptr && metaProperty.hasNotifySignal() )
		{
			QMetaMethod notifysignal = metaProperty.notifySignal();
			QMetaMethod notifyslot = this->metaObject()->method(this->metaObject()->indexOfSlot("getDataFromParentSlot()"));
			connect(parentQObject, notifysignal,this,notifyslot);
		}

		//set item flags
		if(this->metaProperty.isWritable())
		{
			defaultFlags = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
		}
		else
		{
			defaultFlags = Qt::ItemIsSelectable ;
		}
	}
	else
	{
		//variant with no parent on non QObject parent*-
		canreset = true;
		defaultFlags = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	}

}

QVariantProperty::~QVariantProperty()
{
	qDeleteAll(children);
	children.clear();
}

QVariant QVariantProperty::getData(Qt::ItemDataRole role , Column column)
{
	switch (column)
	{
	case QVariantProperty::PropertyNameColumn:
		switch (role)
		{
		case Qt::WhatsThisRole:
		case Qt::DisplayRole:
		case Qt::StatusTipRole:
		case Qt::ToolTipRole:
			{
				return propertyName;
			}
			break;
		case Qt::DecorationRole:
			return QVariant();
			break;
		case Qt::EditRole:
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
	case QVariantProperty::PropertyValueColumn:

		switch (role)
		{
	
		case Qt::DecorationRole:
			return QVariant();
			break;
		case Qt::DisplayRole:
		case Qt::EditRole:
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

bool QVariantProperty::setData(const QVariant & value,Qt::ItemDataRole role, Column column)
{
	if(column == Column::PropertyValueColumn && role == Qt::EditRole)
	{
		if(metaProperty.isValid())
		{
			QObject* parent = QVariantProperty::parent();
			QVariantProperty* parentProp = qobject_cast<QVariantProperty*>(parent);

			if(parentProp != nullptr)
			{
				QObject* head  = qvariant_cast<QObject*>(parentProp->value);

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
		else
		{
			this->value = value;
			emit valueChangedSignal(propertyName,this->value);
			setupChildProperties();
			return true;
		}
	}
	return false;
}

bool QVariantProperty::refreshDataSlot()
{
	if(metaProperty.isValid() && metaProperty.isResettable())
	{
		QObject* parent = QVariantProperty::parent();

		if(parent != nullptr )
		{
			QVariantProperty* parentProp = qobject_cast<QVariantProperty*>(parent);

			if(parentProp != nullptr)
			{
				QObject* head  = parentProp->getObject();

				if(head != nullptr)
				{
					bool reset = metaProperty.reset(head);

					if(reset)
					{
						value = metaProperty.read(head);
						setData(value);
						

						emit valueChangedSignal(propertyName,this->value);
					    
						setupChildProperties();
					}

					return reset;
				}
			}
		}
	}
	else
	{
		setData(resetValue);
		emit valueChangedSignal(propertyName,this->value);
		
		setupChildProperties();
		return canreset;
	}

	return false;
}

bool QVariantProperty::canReset()
{
	if(metaProperty.isValid()) 
	{
		if(metaProperty.isResettable())
		{
			return true;
		}
		else
			return false;
	}
	else
	{
		return canreset;
	}
}

void QVariantProperty::setModelIndex(const QModelIndex& index)
{
	this->modelIndex = index;
}

QVariant QVariantProperty::getData() const
{
	return this->value;
}

QObject* QVariantProperty::getObject() const
{
	if (value.canConvert<QObject*>())
	{
		return qvariant_cast<QObject*>(value);
	}
	else
	{
		return nullptr;
	}
}

QMetaProperty QVariantProperty::getMetaProperty() const
{
	return metaProperty;
}

int QVariantProperty::getRowInParent() const
{  
	return rowInParent;
}

void QVariantProperty::setPropertyName(const QString& propName)
{
	if(!metaProperty.isValid())
	{
		propertyName = propName;
	}
}

QtPropertyModel* QVariantProperty::getModel() const
{
	return model;
}

QModelIndex QVariantProperty::getModelIndex() const
{
	return modelIndex;
}

const QList<QVariantProperty*>&  QVariantProperty::childProperties() 
{
	return children;
}

void QVariantProperty::childPropertyValueChangedSlot(const QString& propertyName, const QVariant& value)
{
	if(value.isValid())
	{
		
		setData(this->value);
	}
}

void QVariantProperty::getDataFromParentSlot()
{
	QObject* parent = QVariantProperty::parent();

	if(parent != nullptr && metaProperty.isValid() )
	{
		QVariantProperty* parentProp = qobject_cast<QVariantProperty*>(parent);

		if(parentProp != nullptr)
		{
			QObject* head  = qvariant_cast<QObject*>(parentProp->value);

			if(head != nullptr)
			{
				value = metaProperty.read(head);

				if(model != nullptr && modelIndex.isValid())
				{
					emit model->dataChanged(modelIndex,modelIndex);
				}

				emit valueChangedSignal(propertyName,this->value);
				
				setupChildProperties();

				emit model->dataChanged(this->modelIndex , this->modelIndex);
			}
		}
	}

}

bool QVariantProperty::hasChildren()
{
	return false;
}

int QVariantProperty::getRowCount() 
{
	if(!childPropertiesSet)
	setupChildProperties();
	return children.count();
}

void QVariantProperty::setupChildProperties()
{
	if(!childPropertiesSet)
	{
		childPropertiesSet = true;
	}
}

int QVariantProperty::getColumnCount() const
{
	return columnCount;
}

Qt::ItemFlags QVariantProperty::flags() const
{
	Qt::ItemFlags flags = Qt::ItemIsSelectable;

	if(metaProperty.isValid())
	{
		if(metaProperty.isWritable())
		flags = flags |Qt::ItemIsEnabled | Qt::ItemIsEditable;
	}
	else
	{
		return defaultFlags;
	}

	return flags;
}

void QVariantProperty::setDefaultFlags(Qt::ItemFlags flags)
{
	defaultFlags = flags;
}

QString QVariantProperty::getPropertyName() const
{
	return propertyName;
}

QString QVariantProperty::getQualifiedVariantPropertyName() const
{
	if(metaProperty.isValid())
	{
		const QMetaObject* enclosing = metaProperty.enclosingMetaObject();
		QString name = enclosing->className();
		name.append("::");
		name.append(metaProperty.name());

		return name;
	}
	else
	{
		QObject* parent = QVariantProperty::parent();

		if(parent != nullptr )
		{
			QVariantProperty* parentProp = qobject_cast<QVariantProperty*>(parent);

			if(parentProp != nullptr)
			{
				return parentProp->getPropertyName() + "::" + propertyName;

			}
		}
	}

	return QString();
}

