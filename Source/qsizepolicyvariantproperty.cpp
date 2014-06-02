#include "stdafx.h"
#include "qsizepolicyvariantproperty.h"
#include "qenumvariantproperty.h"

QSizePolicyVariantProperty::QSizePolicyVariantProperty(const QSizePolicy& value, const QMetaProperty& metaProperty,QtPropertyModel* const &  model, int row, QVariantProperty *parent)
	: QVariantProperty(value,metaProperty,model, row, parent)
{
	const QMetaObject& globalObject =  QSizePolicy::staticMetaObject;
	int index = globalObject.indexOfEnumerator("Policy");
	policyMetaEnum = globalObject.enumerator(index);
}

QSizePolicyVariantProperty::~QSizePolicyVariantProperty()
{

}

bool QSizePolicyVariantProperty::hasChildren()
{
	return true;
}

QVariant QSizePolicyVariantProperty::getData(Qt::ItemDataRole role , Column column)
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
				QSizePolicy& policy = qvariant_cast<QSizePolicy>(value);
				QString hor = policyMetaEnum.valueToKey(policy.horizontalPolicy());
				QString ver = policyMetaEnum.valueToKey(policy.verticalPolicy());
				QString retval = "["+hor+", "+ ver+" ,"+ QString::number(policy.horizontalStretch())+", "+QString::number(policy.verticalStretch()) +"]";
				return retval;
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

Qt::ItemFlags QSizePolicyVariantProperty::flags() const
{
	Qt::ItemFlags flags = Qt::ItemIsSelectable ;

	if(metaProperty.isValid()) 
	{
		if(metaProperty.isWritable())
			flags = flags| Qt::ItemIsEnabled;
	}
	else
	{
		if(defaultFlags.testFlag(Qt::ItemIsEditable))
		{
			return Qt::ItemIsSelectable | Qt::ItemIsEnabled ;
		}
		else
		{
			return flags  ;
		}
	}

	return flags;
}

void QSizePolicyVariantProperty::setupChildProperties()
{
	QSizePolicy currentPolicy = qvariant_cast<QSizePolicy>(this->value);

	if(!childPropertiesSet)
	{

		if(children.count() > 0)
		{	
			qDeleteAll(children);
			children.clear();
		}

		Qt::ItemFlags flagsv = flags();
		if((metaProperty.isValid() && metaProperty.isWritable()) || defaultFlags.testFlag(Qt::ItemIsEditable))
		{
			flagsv |= Qt::ItemIsEditable;
		}

		for(int i = 0 ; i < 4 ; i++)
		{

			switch (i)	
			{
			case 0:
				{
					QString propName = "Horizontal Policy";
					int hor = currentPolicy.horizontalPolicy();
					QVariantProperty* tempProp = new QEnumVariantProperty(hor,policyMetaEnum, QMetaProperty(),model, i, this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 1:
				{
					QString propName = "Vertical Policy";
					int ver = currentPolicy.horizontalPolicy();
					QVariantProperty* tempProp = new QEnumVariantProperty(ver,policyMetaEnum, QMetaProperty(),model, i, this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 2:
				{
					QString propName = "Horizontal Stretch";
					int hor = currentPolicy.horizontalStretch();
					QVariantProperty* tempProp = new QVariantProperty(hor, QMetaProperty(),model, i, this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 3:
				{
					QString propName = "Vertical Stretch";
					int ver = currentPolicy.verticalStretch();
					QVariantProperty* tempProp = new QVariantProperty(ver, QMetaProperty(),model, i, this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setPropertyName(propName);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;

			}
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
				QVariant tval;
				if(propertyName == "Horizontal Policy")
				{
					tval = currentPolicy.horizontalPolicy();
				}
				else if(propertyName == "Vertical Policy")
				{
					tval = currentPolicy.verticalPolicy();
				}
				else if(propertyName == "Horizontal Stretch")
				{
					tval = currentPolicy.horizontalStretch();
				}		
				else if(propertyName == "Vertical Stretch")
				{
					tval = currentPolicy.verticalStretch();
				}


				prop->blockSignals(true);
				prop->setData(tval);
				prop->blockSignals(false);


				emit this->model->dataChanged(children[0]->getModelIndex(),children[children.count()-1]->getModelIndex());
			}
		}
	}

}

void QSizePolicyVariantProperty::childPropertyValueChanged(const QString& propertyName, const QVariant& value)
{

	if(value.isValid())
	{
		QSizePolicy& currentP = qvariant_cast<QSizePolicy>(this->value);

		if(propertyName == "Horizontal Policy")
		{
			QSizePolicy::Policy hor = (QSizePolicy::Policy)value.toInt();
			currentP.setHorizontalPolicy(hor);

		}
		else if(propertyName == "Vertical Policy")
		{
			QSizePolicy::Policy ver = (QSizePolicy::Policy)value.toInt();
			currentP.setVerticalPolicy(ver);
		}
		else if(propertyName == "Horizontal Stretch")
		{
			bool cosmetic = value.toBool();
			currentP.setHorizontalStretch(value.toInt());
		}		
		else if(propertyName == "Vertical Stretch")
		{
			currentP.setVerticalStretch(value.toInt());
		}	


		this->value = currentP;
		emit model->dataChanged(modelIndex , modelIndex);
		emit valueChangedSignal(this->propertyName,this->value);

	}
}