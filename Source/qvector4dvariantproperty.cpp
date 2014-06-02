#include "stdafx.h"
#include "qvector4dvariantproperty.h"

QVector4DVariantProperty::QVector4DVariantProperty(const QVector4D& value, const QMetaProperty& metaProperty,QtPropertyModel* const &  model, int row, QVariantProperty *parent )
	: QVariantProperty(value,metaProperty, model , row , parent)
{
	setPropertyValueFunctions["X"] = & QVector4D::setX;
	setPropertyValueFunctions["Y"] = &  QVector4D::setY;
	setPropertyValueFunctions["Z"] = &  QVector4D::setZ;
	setPropertyValueFunctions["W"] = &  QVector4D::setW;

	getPropertyValueFunctions["X"] = & QVector4D::x;
	getPropertyValueFunctions["Y"] = & QVector4D::y;
	getPropertyValueFunctions["Z"] = & QVector4D::z;
	getPropertyValueFunctions["W"] = & QVector4D::w;

}

QVector4DVariantProperty::~QVector4DVariantProperty()
{
	setPropertyValueFunctions.clear();
	getPropertyValueFunctions.clear();
}

bool QVector4DVariantProperty::hasChildren()
{
	return true;
}

QVariant QVector4DVariantProperty::getData(Qt::ItemDataRole role , Column column)
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
				QVector4D temp = qvariant_cast<QVector4D>(value);
				return "[X = "+ QString::number(temp.x()) +", Y = "+  QString::number(temp.y()) +", Z = "+  QString::number(temp.z()) +", W = "+  QString::number(temp.w()) +"]";
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

Qt::ItemFlags QVector4DVariantProperty::flags() const
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

void QVector4DVariantProperty::setupChildProperties()
{
	QVector4D& currentSize = qvariant_cast<QVector4D>(value);

	if(!childPropertiesSet)
	{

		if(children.count() > 0)
		{	
			qDeleteAll(children);
			children.clear();
		}

		QStringList properties = getPropertyValueFunctions.keys(); 
		Qt::ItemFlags flagsv = flags();

		if((metaProperty.isValid() && metaProperty.isWritable()) || defaultFlags.testFlag(Qt::ItemIsEditable))
		{
			flagsv |= Qt::ItemIsEditable;
		}

		for(int i =0 ; i < properties.count() ; i++)
		{
			QString propName = properties[i];
			GetQVector4DProperty prop =getPropertyValueFunctions[propName];
			float value = (currentSize.*prop)();
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
				GetQVector4DProperty propf = getPropertyValueFunctions[propertyName];
				QVariant tval = (currentSize.*propf)(); ;
				prop->blockSignals(true);
				prop->setData(tval);
				prop->blockSignals(false);

			}

			emit this->model->dataChanged(children[0]->getModelIndex(),children[children.count()-1]->getModelIndex());
		}
	}
}

void QVector4DVariantProperty::childPropertyValueChanged(const QString& propertyName, const QVariant& value)
{
	if(value.isValid())
	{

		QVector4D currentSize = qvariant_cast<QVector4D>(this->value);
		if(setPropertyValueFunctions.contains(propertyName))
		{
			SetQVector4DProperty method = setPropertyValueFunctions[propertyName];
		    
   
			(currentSize.*method)(value.toFloat());
		}

		this->value = currentSize;
		emit model->dataChanged(modelIndex , modelIndex);
		emit valueChangedSignal(this->propertyName,this->value);
		
	}
}