#include "stdafx.h"
#include "qlinefvariantproperty.h"
#include "qpointfvariantproperty.h"

QLineFVariantProperty::QLineFVariantProperty(const QLineF& value, const QMetaProperty& metaProperty, QVariantProperty *parent )
	: QVariantProperty(value,metaProperty,parent)
{
	setQLineFPropertyFunctions["P1"] = & QLineF::setP1;
	setQLineFPropertyFunctions["P2"] = &  QLineF::setP2;

	getQLineFPropertyFunctions["P1"] = & QLineF::p1;
	getQLineFPropertyFunctions["P2"] = & QLineF::p2;

}

QLineFVariantProperty::~QLineFVariantProperty()
{
	setQLineFPropertyFunctions.clear();
	getQLineFPropertyFunctions.clear();
}

QVariant QLineFVariantProperty::getData(Qt::ItemDataRole role , Column column)
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
				QLineF temp = qvariant_cast<QLineF>(value);
				QPointF p1 = temp.p1();
				QPointF p2 = temp.p2();

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

Qt::ItemFlags QLineFVariantProperty::flags() const
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

void QLineFVariantProperty::setupChildProperties()
{
	QLineF& currentSize = qvariant_cast<QLineF>(value);

	if(!propertiesSet)
	{
		qDeleteAll(children);
		children.clear();

		QStringList properties = getQLineFPropertyFunctions.keys(); 
		
		Qt::ItemFlags flagsv = flags();
		if((metaProperty.isValid() && metaProperty.isWritable()) || defaultFlags.testFlag(Qt::ItemIsEditable))
		{
		   flagsv |= Qt::ItemIsEditable;
		}

		for(int i =0 ; i < properties.count() ; i++)
		{
			QString propName = properties[i];
			GetQLineFProperty prop =getQLineFPropertyFunctions[propName];
			QPointF value = (currentSize.*prop)();
			QVariantProperty* tempProp = new QPointFVariantProperty(value,QMetaProperty(),this);
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

			if(getQLineFPropertyFunctions.contains(propertyName))
			{
				child->blockSignals(true);
				GetQLineFProperty function = getQLineFPropertyFunctions[propertyName];
				QPointF v = (currentSize.*function)();
				child->setData(v);
				child->blockSignals(false);
			}
		}
	}
}

void QLineFVariantProperty::childPropertyValueChanged(const QString& propertyName, const QVariant& value)
{
	if(value.isValid())
	{

		QLineF currentSize = qvariant_cast<QLineF>(this->value);
		if(setQLineFPropertyFunctions.contains(propertyName))
		{
			SetQLineFProperty method = setQLineFPropertyFunctions[propertyName];
		    childPropertyCalledUpdate = true;
   
			(currentSize.*method)(value.toPointF());
		}

		this->value = currentSize;
		emit model->dataChanged(modelIndex , modelIndex);
		emit valueChangedSignal(this->propertyName,this->value);
		emit valueChangedSignal();
	}
}