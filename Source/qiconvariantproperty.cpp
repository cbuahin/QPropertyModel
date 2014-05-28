#include "stdafx.h"
#include "qiconvariantproperty.h"
#include "qpixmapvariantproperty.h"

QIconVariantProperty::QIconVariantProperty(const QIcon& value, const QMetaProperty& metaProperty, QVariantProperty *parent)
	: QVariantProperty(value,metaProperty,parent)
{

}

QIconVariantProperty::~QIconVariantProperty()
{

}

QVariant QIconVariantProperty::getData(Qt::ItemDataRole role , Column column)
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
			return QVariant();
			break;
		case Qt::DecorationRole:
			return value;
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

Qt::ItemFlags QIconVariantProperty::flags() const
{
	Qt::ItemFlags flags = Qt::ItemIsSelectable ;

	if(metaProperty.isValid()) 
	{
		if(metaProperty.isWritable())
			flags = flags| Qt::ItemIsEnabled | Qt::ItemIsEditable;
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

void QIconVariantProperty::setupChildProperties()
{
	QIcon& currentIcon = qvariant_cast<QIcon>(this->value);
		QSize outrageousSize = QSize(5000,5000);

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
		
		for(int i =0 ; i < 8 ; i++)
		{

			switch (i)	
			{
			case 0:
				{
					QString propName = "Normal On";
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Normal, QIcon::State::On);
					QVariantProperty* tempProp = new QPixmapVariantProperty(pixvalue,QMetaProperty(),this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setModel(model);
					tempProp->setPropertyName(propName);
					tempProp->setRowInParent(i);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 1:
				{
					QString propName = "Normal Off";
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Normal, QIcon::State::Off);
					QVariantProperty* tempProp = new QPixmapVariantProperty(pixvalue,QMetaProperty(),this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setModel(model);
					tempProp->setPropertyName(propName);
					tempProp->setRowInParent(i);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 2:
				{
					QString propName = "Active On";
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Active, QIcon::State::On);
					QVariantProperty* tempProp = new QPixmapVariantProperty(pixvalue,QMetaProperty(),this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setModel(model);
					tempProp->setPropertyName(propName);
					tempProp->setRowInParent(i);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 3:
				{
					QString propName = "Active Off";
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Active, QIcon::State::Off);
					QVariantProperty* tempProp = new QPixmapVariantProperty(pixvalue,QMetaProperty(),this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setModel(model);
					tempProp->setPropertyName(propName);
					tempProp->setRowInParent(i);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 4:
				{
					QString propName = "Selected On";
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Selected, QIcon::State::On);
					QVariantProperty* tempProp = new QPixmapVariantProperty(pixvalue,QMetaProperty(),this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setModel(model);
					tempProp->setPropertyName(propName);
					tempProp->setRowInParent(i);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 5:
				{
					QString propName = "Selected Off";
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Selected, QIcon::State::Off);
					QVariantProperty* tempProp = new QPixmapVariantProperty(pixvalue,QMetaProperty(),this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setModel(model);
					tempProp->setPropertyName(propName);
					tempProp->setRowInParent(i);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 6:
				{
					QString propName = "Disabled On";
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Disabled, QIcon::State::On);
					QVariantProperty* tempProp = new QPixmapVariantProperty(pixvalue,QMetaProperty(),this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setModel(model);
					tempProp->setPropertyName(propName);
					tempProp->setRowInParent(i);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			case 7:
				{
					QString propName = "Disabled Off";
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Disabled, QIcon::State::Off);
					QVariantProperty* tempProp = new QPixmapVariantProperty(pixvalue,QMetaProperty(),this);
					tempProp->setDefaultFlags(flagsv);
					tempProp->setModel(model);
					tempProp->setPropertyName(propName);
					tempProp->setRowInParent(i);
					children.append(tempProp);

					connect(tempProp ,SIGNAL(valueChangedSignal(QString,QVariant)),this, 
						SLOT(childPropertyValueChanged(QString , QVariant)));
				}
				break;
			}

		}

		propertiesSet = true;
	}
	else
	{

		for(int i =0 ; i < 8 ; i++)
		{
			QVariantProperty* tempProp = this->children[i];


			switch (tempProp->getRowInParent())	
			{
			case 0:
				{
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Normal, QIcon::State::On);
					tempProp->setData(pixvalue);
				}
				break;
			case 1:
				{
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Normal, QIcon::State::Off);
					tempProp->setData(pixvalue);
				}
				break;
			case 2:
				{

					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Active, QIcon::State::On);
					tempProp->setData(pixvalue);
				}
				break;
			case 3:
				{

					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Active, QIcon::State::Off);
					tempProp->setData(pixvalue);
				}
				break;
			case 4:
				{

					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Selected, QIcon::State::On);
					tempProp->setData(pixvalue);
				}
				break;
			case 5:
				{
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Selected, QIcon::State::Off);
					tempProp->setData(pixvalue);
				}
				break;
			case 6:
				{
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Disabled, QIcon::State::On);
					tempProp->setData(pixvalue);
				}
				break;
			case 7:
				{
					QPixmap pixvalue = currentIcon.pixmap(outrageousSize, QIcon::Mode::Disabled, QIcon::State::Off);
					tempProp->setData(pixvalue);
				}
				break;
			}

		}
	}
}

void QIconVariantProperty::childPropertyValueChanged(const QString& propertyName, const QVariant& value)
{

	if(value.isValid())
	{
		QIcon& currentIcon = qvariant_cast<QIcon>(this->value);
		QPixmap pixvalue = qvariant_cast<QPixmap>(value);

		if(propertyName == "Normal On")
		{
			currentIcon.addPixmap(pixvalue , QIcon::Mode::Normal, QIcon::State::On);
		}
		else if(propertyName == "Normal Off")
		{
			currentIcon.addPixmap(pixvalue , QIcon::Mode::Normal, QIcon::State::Off);
		}
		else if(propertyName == "Active On")
		{
			currentIcon.addPixmap(pixvalue, QIcon::Mode::Active, QIcon::State::On);
		}
		else if(propertyName == "Active Off")
		{
			currentIcon.addPixmap(pixvalue, QIcon::Mode::Active, QIcon::State::Off);
		}
		else if(propertyName == "Selected On")
		{
			currentIcon.addPixmap(pixvalue, QIcon::Mode::Selected, QIcon::State::On);
		}
		else if(propertyName == "Selected Off")
		{
			currentIcon.addPixmap(pixvalue, QIcon::Mode::Selected, QIcon::State::Off);
		}
		else if(propertyName == "Disabled On")
		{
			currentIcon.addPixmap(pixvalue, QIcon::Mode::Disabled, QIcon::State::On);
		}
		else if(propertyName == "Disabled Off")
		{
			currentIcon.addPixmap(pixvalue, QIcon::Mode::Disabled, QIcon::State::Off);
		}

		childPropertyCalledUpdate = true;
		this->value = currentIcon;
		emit model->dataChanged(modelIndex , modelIndex);
		emit valueChangedSignal(this->propertyName,this->value);
		emit valueChangedSignal();
	}
}