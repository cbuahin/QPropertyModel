#include "stdafx.h"
#include "qpointfvariantproperty.h"

QPointFVariantProperty::QPointFVariantProperty(const QPointF& value, const QMetaProperty& metaProperty, QVariantProperty *parent )
	: QVariantProperty(value,metaProperty,parent)
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

	if(!propertiesSet)
	{
		qDeleteAll(children);
		children.clear();

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
			QVariantProperty* tempProp = new QVariantProperty(value,QMetaProperty(),this);
			
			
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

			if(getQPointFPropertyFunctions.contains(propertyName))
			{
				child->blockSignals(true);
				GetQPointFProperty function = getQPointFPropertyFunctions[propertyName];
				qreal v = (currentSize.*function)();
				child->setData(v);
				child->blockSignals(false);
			}
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
		    childPropertyCalledUpdate = true;
   
			(currentSize.*method)(value.toReal());
		}

		this->value = currentSize;
		emit model->dataChanged(modelIndex , modelIndex);
		emit valueChangedSignal(this->propertyName,this->value);
		emit valueChangedSignal();
	}
}