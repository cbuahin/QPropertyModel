#include "stdafx.h"
#include "qsizevariantproperty.h"


QSizeVariantProperty::QSizeVariantProperty(const QSize& value, const QMetaProperty& metaProperty,QtPropertyModel* const &  model, int row, QVariantProperty *parent )
	: QVariantProperty(value,metaProperty,model,row ,parent)
{
	setQSizePropertyFunctions["Height"] = & QSize::setHeight;
	setQSizePropertyFunctions["Width"] = & QSize::setWidth;

	getQSizePropertyFunctions["Height"] = & QSize::height;
	getQSizePropertyFunctions["Width"] = & QSize::width;
}

QSizeVariantProperty::~QSizeVariantProperty()
{
	setQSizePropertyFunctions.clear();
	getQSizePropertyFunctions.clear();
}

bool QSizeVariantProperty::hasChildren()
{
	return true;
}

QVariant QSizeVariantProperty::getData(Qt::ItemDataRole role , Column column)
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
				QSize temp = qvariant_cast<QSize>(value);
				return "[Height = " +QString::number(temp.height()) + ", Width = " + QString::number(temp.width()) +"]";
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

Qt::ItemFlags QSizeVariantProperty::flags() const
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

void QSizeVariantProperty::setupChildProperties()
{
	QSize& currentSize = qvariant_cast<QSize>(value);
	if(!childPropertiesSet)
	{

		if(children.count() > 0)
		{	
			qDeleteAll(children);
			children.clear();
		}

		QStringList properties = getQSizePropertyFunctions.keys(); 
		Qt::ItemFlags flagsv = flags();
		if((metaProperty.isValid() && metaProperty.isWritable()) || defaultFlags.testFlag(Qt::ItemIsEditable))
		{
			flagsv |= Qt::ItemIsEditable;
		}

		for(int i =0 ; i < properties.count() ; i++)
		{
			QString propName = properties[i];
			GetSizeProperty prop =getQSizePropertyFunctions[propName];
			int value = (currentSize.*prop)();
			QVariantProperty* tempProp = new QVariantProperty(value,QMetaProperty(),model, i, this);
			tempProp->setDefaultFlags(flagsv);

			tempProp->setPropertyName(propName);
			children.append(tempProp);


			connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
				SLOT(childPropertyValueChanged(QString , QVariant)));
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
				GetSizeProperty propf =getQSizePropertyFunctions[propertyName];
				QVariant tval = (currentSize.*propf)(); ;
				prop->blockSignals(true);
				prop->setData(tval);
				prop->blockSignals(false);

			}

			emit this->model->dataChanged(children[0]->getModelIndex(),children[children.count()-1]->getModelIndex());
		}
	}

}

void QSizeVariantProperty::childPropertyValueChanged(const QString& propertyName, const QVariant& value)
{
	if(value.isValid())
	{

		QSize currentSize = qvariant_cast<QSize>(this->value);

		if(setQSizePropertyFunctions.contains(propertyName))
		{
			SetQSizeProperty method = setQSizePropertyFunctions[propertyName];
		    
   
			(currentSize.*method)(value.toInt());
		}

		this->value = currentSize;
		emit model->dataChanged(modelIndex , modelIndex);
		emit valueChangedSignal(this->propertyName,this->value);
		
	}
}