#include "stdafx.h"
#include "qflagsvariantproperty.h"
#include "qboolvariantproperty.h"


QFlagsVariantProperty::QFlagsVariantProperty(const QVariant& value, const QMetaEnum& metaEnumProperty,const QMetaProperty& metaProperty, QVariantProperty *parent)
	: QVariantProperty(value,metaProperty,parent)
{
	this->enumProperty = metaEnumProperty;
}

QFlagsVariantProperty::~QFlagsVariantProperty()
{

}

QVariant QFlagsVariantProperty::getData(Qt::ItemDataRole role , Column column)
{
	switch (column)
	{
	case QVariantProperty::PropertyNameColumn:
		switch (role)
		{
			break;
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
	if(!propertiesSet)
	{
		model->removeRows(0,children.count()-1,this->modelIndex);
		qDeleteAll(children);
		children.clear();
	
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
		
		    QVariantProperty* tempProp = new QBoolVariantProperty(set,QMetaProperty(),this);
			tempProp->setDefaultFlags(flagsv);
			tempProp->setModel(model);
			tempProp->setPropertyName(propName);
			tempProp->setRowInParent(i);
			children.append(tempProp);


			connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
				SLOT(childPropertyValueChanged(QString , QVariant)));
		}

		propertiesSet = true;
	}
	else
	{
		//for(int i = 0 ; i < children.count() ; i++)
		//{
		//	QVariantProperty* child =  children[i];
		//	QString propertyName = child->getPropertyName();

		//	if(getQLineFPropertyFunctions.contains(propertyName))
		//	{
		//		child->blockSignals(true);
		//		GetQLineFProperty function = getQLineFPropertyFunctions[propertyName];
		//		QPointF v = (currentSize.*function)();
		//		child->setData(v);
		//		child->blockSignals(false);
		//	}
		//}
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
		emit valueChangedSignal();
	}
}