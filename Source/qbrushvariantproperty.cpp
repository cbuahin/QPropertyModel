#include "stdafx.h"
#include "qbrushvariantproperty.h"
#include <qcolorvariantproperty.h>
#include <qenumvariantproperty.h>
#include <qpixmapvariantproperty.h>

QBrushVariantProperty::QBrushVariantProperty(const QBrush& value, const QMetaProperty& metaProperty, QVariantProperty *parent)
	: QVariantProperty(value,metaProperty,parent)
{

}

QBrushVariantProperty::~QBrushVariantProperty()
{

}

QVariant QBrushVariantProperty::getData(Qt::ItemDataRole role , Column column)
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

Qt::ItemFlags QBrushVariantProperty::flags() const
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
			return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
		}
		else
		{
		   return flags  ;
		}
	}

	return flags;
}

void QBrushVariantProperty::setupChildProperties()
{
	QBrush& currentBrush = qvariant_cast<QBrush>(this->value);

	if(!propertiesSet)
	{
		//(0,children.count()-1,this->modelIndex);
		qDeleteAll(children);
		children.clear();

		
		Qt::ItemFlags flagsv = flags();
		if((metaProperty.isValid() && metaProperty.isWritable()) || defaultFlags.testFlag(Qt::ItemIsEditable))
		{
		   flagsv |= Qt::ItemIsEditable;
		}
		
		for(int i = 0 ; i < 3 ; i++)
		{

			switch (i)	
			{
			case 0:
				{
					QString propName = "Color";
					QColor color = currentBrush.color();
					QVariantProperty* tempProp = new QColorVariantProperty(color,QMetaProperty(),this);
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
					QString propName = "Brush Style";
					const QMetaObject& globalObject =  StaticQtMetaObject::get();
					int index = globalObject.indexOfEnumerator("BrushStyle");
					QMetaEnum enumeration = globalObject.enumerator(index);
					int bstyle = currentBrush.style();
					QVariantProperty* tempProp = new QEnumVariantProperty(bstyle,enumeration, QMetaProperty(),this);
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
					QString propName = "Texture Image";
					Qt::BrushStyle bstyle = currentBrush.style();

					QPixmap pixvalue = currentBrush.texture();
					QVariantProperty* tempProp = new QPixmapVariantProperty(pixvalue,QMetaProperty(),this);
					
					if(bstyle == Qt::BrushStyle::TexturePattern)
					{
						tempProp->setDefaultFlags(flagsv);
					}
					else
					{
						Qt::ItemFlags tempflag = Qt::ItemIsSelectable | Qt::ItemIsEditable;
						tempProp->setDefaultFlags(tempflag);
					}
					
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

		for(int i =0 ; i < 3 ; i++)
		{
			QVariantProperty* tempProp = this->children[i];


			switch (tempProp->getRowInParent())	
			{
			case 0:
				{
					QColor color = currentBrush.color();
					tempProp->setData(color);
				}
				break;
			case 1:
				{
					int style = currentBrush.style();
					tempProp->setData(style);
				}
				break;
			case 2:
				{

					QPixmap pixmap = currentBrush.texture();
					tempProp->setData(pixmap);
				}
				break;
			}

		}
	}
}

void QBrushVariantProperty::childPropertyValueChanged(const QString& propertyName, const QVariant& value)
{

	if(value.isValid())
	{
		QBrush currentBrush = qvariant_cast<QBrush>(this->value);

		if(propertyName == "Color")
		{
			currentBrush.setColor(qvariant_cast<QColor>(value)); 
		}
		else if(propertyName == "Brush Style")
		{
			Qt::BrushStyle style = (Qt::BrushStyle)(value.toInt());
			currentBrush.setStyle(style);

			Qt::ItemFlags flagsv = flags();

			if((metaProperty.isValid() && metaProperty.isWritable()) || defaultFlags.testFlag(Qt::ItemIsEditable))
			{
				if(style == Qt::BrushStyle::TexturePattern)
				{
				    flagsv |= Qt::ItemIsEditable;
				}
				else
				{
					flagsv = Qt::ItemIsSelectable | Qt::ItemIsEditable;
				}


				for(int i =0 ; i < children.count() ; i++)
				{
					QVariantProperty* prop =  children[i];

					if(prop->getPropertyName() == "Texture Image")
					{
						prop->setDefaultFlags(flagsv);
						break;
					}
				}
			}

		}
		else if(propertyName == "Texture Image")
		{

			currentBrush.setTexture(qvariant_cast<QPixmap>(value));
		}
		

		childPropertyCalledUpdate = true;
		this->value = currentBrush;
		emit model->dataChanged(modelIndex , modelIndex);
		emit valueChangedSignal(this->propertyName,this->value);
		emit valueChangedSignal();
	}
}