#include "stdafx.h"
#include "qrectvariantproperty.h"


QRectVariantProperty::QRectVariantProperty(const QRect& value, const QMetaProperty& metaProperty, QVariantProperty *parent )
	: QVariantProperty(value,metaProperty,parent)
{
	  
	setQRectPropertyFunctions["X"] = & QRect::setX;
	setQRectPropertyFunctions["Y"] = &  QRect::setY;
	setQRectPropertyFunctions["Height"] = &  QRect::setHeight;
	setQRectPropertyFunctions["Width"] = &  QRect::setWidth;

	getQRectPropertyFunctions["X"] = & QRect::x;
	getQRectPropertyFunctions["Y"] = & QRect::y;
	getQRectPropertyFunctions["Height"] = & QRect::height;
	getQRectPropertyFunctions["Width"] = & QRect::width;

}

QRectVariantProperty::~QRectVariantProperty()
{
	setQRectPropertyFunctions.clear();
	getQRectPropertyFunctions.clear();
}

QVariant QRectVariantProperty::getData(Qt::ItemDataRole role , Column column)
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
				QRect temp = qvariant_cast<QRect>(value);
				return "[X = "+ QString::number(temp.x()) +", Y = "+  QString::number(temp.y())+", Height = " +QString::number(temp.height()) + ", Width = " + QString::number(temp.width()) +"]";
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

Qt::ItemFlags QRectVariantProperty::flags() const
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

void QRectVariantProperty::setupChildProperties()
{
	QRect& currentSize = qvariant_cast<QRect>(value);

	if(!propertiesSet)
	{
		qDeleteAll(children);
		children.clear();

		QStringList properties = getQRectPropertyFunctions.keys(); 
		Qt::ItemFlags flagsv = flags();
		if((metaProperty.isValid() && metaProperty.isWritable()) || defaultFlags.testFlag(Qt::ItemIsEditable))
		{
		   flagsv |= Qt::ItemIsEditable;
		}

		for(int i =0 ; i < properties.count() ; i++)
		{
			QString propName = properties[i];
			GetQRectProperty prop =getQRectPropertyFunctions[propName];
			int value = (currentSize.*prop)();
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

			if(getQRectPropertyFunctions.contains(propertyName))
			{
				child->blockSignals(true);
				GetQRectProperty function = getQRectPropertyFunctions[propertyName];
				int v = (currentSize.*function)();
				child->setData(v);
				child->blockSignals(false);
			}
		}
	}
}

void QRectVariantProperty::childPropertyValueChanged(const QString& propertyName, const QVariant& value)
{
	if(value.isValid())
	{

		QRect currentSize = qvariant_cast<QRect>(this->value);
		if(setQRectPropertyFunctions.contains(propertyName))
		{
			SetQRectProperty method = setQRectPropertyFunctions[propertyName];
		    childPropertyCalledUpdate = true;
   
			(currentSize.*method)(value.toInt());
		}

		this->value = currentSize;
		emit model->dataChanged(modelIndex , modelIndex);
		emit valueChangedSignal(this->propertyName,this->value);
		emit valueChangedSignal();
	}
}