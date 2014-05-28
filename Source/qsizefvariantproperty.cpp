#include "stdafx.h"
#include "qsizefvariantproperty.h"


QSizeFVariantProperty::QSizeFVariantProperty(const QSizeF& value, const QMetaProperty& metaProperty, QVariantProperty *parent )
	: QVariantProperty(value,metaProperty,parent)
{
	setQSizeFPropertyFunctions["Height"] = & QSizeF::setHeight;
	setQSizeFPropertyFunctions["Width"] = & QSizeF::setWidth;

	getQSizeFPropertyFunctions["Height"] = & QSizeF::height;
	getQSizeFPropertyFunctions["Width"] = & QSizeF::width;
}

QSizeFVariantProperty::~QSizeFVariantProperty()
{
	setQSizeFPropertyFunctions.clear();
	getQSizeFPropertyFunctions.clear();
}

QVariant QSizeFVariantProperty::getData(Qt::ItemDataRole role , Column column)
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
				QSizeF temp = qvariant_cast<QSizeF>(value);
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

Qt::ItemFlags QSizeFVariantProperty::flags() const
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

void QSizeFVariantProperty::setupChildProperties()
{
	QSizeF& currentSize = qvariant_cast<QSizeF>(value);

	if(!propertiesSet)
	{
		qDeleteAll(children);
		children.clear();

		QStringList properties = getQSizeFPropertyFunctions.keys(); 
		Qt::ItemFlags flagsv = flags();
		if((metaProperty.isValid() && metaProperty.isWritable()) || defaultFlags.testFlag(Qt::ItemIsEditable))
		{
		   flagsv |= Qt::ItemIsEditable;
		}
		for(int i =0 ; i < properties.count() ; i++)
		{
			QString propName = properties[i];
			GetQSizeFProperty prop =getQSizeFPropertyFunctions[propName];
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

			if(getQSizeFPropertyFunctions.contains(propertyName))
			{
				child->blockSignals(true);
				GetQSizeFProperty function = getQSizeFPropertyFunctions[propertyName];
				qreal v = (currentSize.*function)();
				child->setData(v);
				child->blockSignals(false);
			}
		}
	}
}

void QSizeFVariantProperty::childPropertyValueChanged(const QString& propertyName, const QVariant& value)
{
	if(value.isValid())
	{

		QSizeF currentSize = qvariant_cast<QSizeF>(this->value);
		if(setQSizeFPropertyFunctions.contains(propertyName))
		{
			SetQSizeFProperty method = setQSizeFPropertyFunctions[propertyName];
		    childPropertyCalledUpdate = true;
   
			(currentSize.*method)(value.toReal());
			
		}

		this->value = currentSize;
		emit model->dataChanged(modelIndex , modelIndex);
		emit valueChangedSignal(this->propertyName,this->value);
		emit valueChangedSignal();
	}
}