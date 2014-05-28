#include "stdafx.h"
#include "qlinevariantproperty.h"
#include "qpointvariantproperty.h"

QLineVariantProperty::QLineVariantProperty(const QLine& value, const QMetaProperty& metaProperty, QVariantProperty *parent )
	: QVariantProperty(value,metaProperty,parent)
{
	setQLinePropertyFunctions["P1"] = & QLine::setP1;
	setQLinePropertyFunctions["P2"] = &  QLine::setP2;

	getQLinePropertyFunctions["P1"] = & QLine::p1;
	getQLinePropertyFunctions["P2"] = & QLine::p2;

}

QLineVariantProperty::~QLineVariantProperty()
{
	setQLinePropertyFunctions.clear();
	getQLinePropertyFunctions.clear();
}

QVariant QLineVariantProperty::getData(Qt::ItemDataRole role , Column column)
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
				QLine temp = qvariant_cast<QLine>(value);
				QPoint p1 = temp.p1();
				QPoint p2 = temp.p2();

				return "[P1 = { X = "+ QString::number(p1.x()) +", Y = "+ QString::number(p1.y())+ "}, P2 = { X = "+ QString::number(p2.x()) +", Y = "+ QString::number(p2.y())+"}]";
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

Qt::ItemFlags QLineVariantProperty::flags() const
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

void QLineVariantProperty::setupChildProperties()
{
	QLine& currentSize = qvariant_cast<QLine>(value);

	if(!propertiesSet)
	{
		qDeleteAll(children);
		children.clear();

		QStringList properties = getQLinePropertyFunctions.keys(); 

		Qt::ItemFlags flagsv = flags();
		if((metaProperty.isValid() && metaProperty.isWritable()) || defaultFlags.testFlag(Qt::ItemIsEditable))
		{
		   flagsv |= Qt::ItemIsEditable;
		}

		for(int i =0 ; i < properties.count() ; i++)
		{
			QString propName = properties[i];
			GetQLineProperty prop =getQLinePropertyFunctions[propName];
			QPoint value = (currentSize.*prop)();
			QVariantProperty* tempProp = new QPointVariantProperty(value,QMetaProperty(),this);
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
		for(int i = 0 ; i < children.count() ; i++)
		{
			QVariantProperty* child =  children[i];
			QString propertyName = child->getPropertyName();

			if(getQLinePropertyFunctions.contains(propertyName))
			{
				child->blockSignals(true);
				GetQLineProperty function = getQLinePropertyFunctions[propertyName];
				QPoint v = (currentSize.*function)();
				child->setData(v);
				child->blockSignals(false);
			}
		}
	}
}

void QLineVariantProperty::childPropertyValueChanged(const QString& propertyName, const QVariant& value)
{
	if(value.isValid())
	{

		QLine currentSize = qvariant_cast<QLine>(this->value);
		if(setQLinePropertyFunctions.contains(propertyName))
		{
			SetQLineProperty method = setQLinePropertyFunctions[propertyName];
		    childPropertyCalledUpdate = true;
   
			(currentSize.*method)(value.toPoint());
		}

		this->value = currentSize;
		emit model->dataChanged(modelIndex , modelIndex);
		emit valueChangedSignal(this->propertyName,this->value);
		emit valueChangedSignal();
	}
}