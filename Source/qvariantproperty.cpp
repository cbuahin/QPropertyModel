#include "stdafx.h"
#include "qvariantproperty.h"

QVariantProperty::QVariantProperty(const QVariant& value, const QMetaProperty& metaProperty , QVariantProperty *parent)
	: QObject(parent), rowInParent(0), metaProperty(), propertiesSet(false) , canreset(true), childPropertyCalledUpdate(false)
{
	this->value = value;
	this->metaProperty = metaProperty;
	columnCount = 2;
	model = nullptr;
	resetValue= QVariant(value);

	if( this->metaProperty.isValid())
	{
		propertyName = this->metaProperty.name();
		rowInParent = metaProperty.propertyIndex();
		QObject* parentQObject = parent->getObject();

		if(parentQObject != nullptr && metaProperty.hasNotifySignal())
		{
			QMetaMethod notifysignal = metaProperty.notifySignal();

			//update variant with changes outside of model
			QMetaMethod notifyslot = this->metaObject()->method(this->metaObject()->indexOfSlot("getDataFromParentSlot()"));
			connect(parentQObject, notifysignal,this,notifyslot);
		}
	}
	else
	{
		canreset = true;
		
	}
	
	defaultFlags = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

QVariantProperty::~QVariantProperty()
{
	qDeleteAll(children);
	children.clear();
}

QVariant QVariantProperty::getData(Qt::ItemDataRole role , Column column)
{
	switch (column)
	{
	case QVariantProperty::PropertyNameColumn:
		switch (role)
		{
		case Qt::WhatsThisRole:
		case Qt::DisplayRole:
		case Qt::StatusTipRole:
		case Qt::ToolTipRole:
			{
				return propertyName;
			}
			break;
		case Qt::DecorationRole:
			return QVariant();
			break;
		case Qt::EditRole:
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
	case QVariantProperty::PropertyValueColumn:

		switch (role)
		{
	
		case Qt::DecorationRole:
			return QVariant();
			break;
		case Qt::DisplayRole:
		case Qt::EditRole:
		case Qt::ToolTipRole:
		case Qt::StatusTipRole:
		case Qt::WhatsThisRole:
			return value;
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

bool QVariantProperty::setData(const QVariant & value,Qt::ItemDataRole role, Column column)
{
	if(!value.isValid())
	{
		qDebug()<<"test";
	}

	if(column == Column::PropertyValueColumn && role == Qt::EditRole)
	{
		if(metaProperty.isValid())
		{
			QObject* parent = QVariantProperty::parent();
			QVariantProperty* parentProp = qobject_cast<QVariantProperty*>(parent);

			if(parentProp != nullptr)
			{
				QObject* head  = qvariant_cast<QObject*>(parentProp->value);

				if(head != nullptr)
				{
					bool written = metaProperty.write(head, value);

					if(written)
					{
						this->value = value;
						emit valueChangedSignal(propertyName,this->value);
						emit valueChangedSignal();
					}

					return written;
				}

			}
		}
		else
		{
			this->value = value;
			emit valueChangedSignal(propertyName,this->value);
			emit valueChangedSignal();
			return true;
		}
	}
	return false;
}

void QVariantProperty::setData(const QVariant & value)
{
	if(model->setData(modelIndex,value));
	{

		if(!childPropertyCalledUpdate)
		{
			setupChildProperties();
		}

		childPropertyCalledUpdate = false;
		emit valueChangedSignal(propertyName,this->value);
		emit valueChangedSignal();
	}
}

bool QVariantProperty::refreshDataSlot()
{
	if(metaProperty.isValid() && metaProperty.isResettable())
	{
		QObject* parent = QVariantProperty::parent();

		if(parent != nullptr )
		{
			QVariantProperty* parentProp = qobject_cast<QVariantProperty*>(parent);

			if(parentProp != nullptr)
			{
				QObject* head  = parentProp->getObject();

				if(head != nullptr)
				{
					bool reset = metaProperty.reset(head);

					if(reset)
					{
						value = metaProperty.read(head);
						setData(value);
						setupChildProperties();
						emit valueChangedSignal(propertyName,this->value);
					    emit valueChangedSignal();
					}

					return reset;
				}

			}
		}
	}
	else
	{
		setData(resetValue);
		setupChildProperties();
		emit valueChangedSignal(propertyName,this->value);
		emit valueChangedSignal();
		return canreset;
	}

	return false;
}

bool QVariantProperty::canReset()
{
	if(metaProperty.isValid()) 
	{
		if(metaProperty.isResettable())
		{
			return true;
		}
		else
			return false;
	}
	else
	{
		return canreset;
	}
}

void QVariantProperty::setModel(QAbstractItemModel* const& model)
{
	this->model = model;
}

void QVariantProperty::setModelIndex(const QModelIndex& modelIndex)
{
	this->modelIndex = modelIndex;
}

QVariant QVariantProperty::getData() const
{
	return this->value;
}

QObject* QVariantProperty::getObject() const
{
	return qvariant_cast<QObject*>(value);
}

QMetaProperty QVariantProperty::getMetaProperty() const
{
	return metaProperty;
}

int QVariantProperty::getRowInParent() const
{
	return rowInParent;
}

void QVariantProperty::setRowInParent(int row)
{
	if(!metaProperty.isValid())
	{
		rowInParent = row;
	}
}

void QVariantProperty::setPropertyName(const QString& propName)
{
	if(!metaProperty.isValid())
	{
		propertyName = propName;
	}
}

QAbstractItemModel* QVariantProperty::getModel() const
{
	return model;
}

QModelIndex QVariantProperty::getModelIndex() const
{
	return modelIndex;
}

const QList<QVariantProperty*>&  QVariantProperty::childProperties() 
{
	return children;
}

void QVariantProperty::childPropertyValueChangedSlot(const QString& propertyName, const QVariant& value)
{
	if(value.isValid())
	{
		childPropertyCalledUpdate = true;
		

		setData(this->value);

	}
}

void QVariantProperty::getDataFromParentSlot()
{
	QObject* parent = QVariantProperty::parent();

	if(parent != nullptr )
	{
		QVariantProperty* parentProp = qobject_cast<QVariantProperty*>(parent);

		if(parentProp != nullptr)
		{
			QObject* head  = qvariant_cast<QObject*>(parentProp->value);

			if(head != nullptr)
			{
				value = metaProperty.read(head);
		     	model->dataChanged(modelIndex,modelIndex);
				emit valueChangedSignal();
			}

		}
	}

}

bool QVariantProperty::hasChildren()
{
	if(!propertiesSet)
	{
		setupChildProperties();
	}

	if(children.count() > 0)
		return true;
	else
		return false;
}

void QVariantProperty::setupChildProperties()
{
	if(!propertiesSet)
	{
		propertiesSet = true;
	}
	else
	{

	}
}

int QVariantProperty::getRowCount() const
{
	return children.count();
}

int QVariantProperty::getColumnCount() const
{
	return columnCount;
}

Qt::ItemFlags QVariantProperty::flags() const
{
	Qt::ItemFlags flags = Qt::ItemIsSelectable;

	if(metaProperty.isValid())
	{
		if(metaProperty.isWritable())
		flags = flags |Qt::ItemIsEnabled | Qt::ItemIsEditable;
	}
	else
	{
		return defaultFlags;
	}

	return flags;
}

void QVariantProperty::setDefaultFlags(Qt::ItemFlags flags)
{
	defaultFlags = flags;
}

QString QVariantProperty::getPropertyName() const
{
	return propertyName;
}

QString QVariantProperty::getQualifiedVariantPropertyName() const
{
	if(metaProperty.isValid())
	{
		const QMetaObject* enclosing = metaProperty.enclosingMetaObject();
		QString name = enclosing->className();
		name.append("::");
		name.append(metaProperty.name());

		return name;
	}
	else
	{
		QObject* parent = QVariantProperty::parent();

		if(parent != nullptr )
		{
			QVariantProperty* parentProp = qobject_cast<QVariantProperty*>(parent);

			if(parentProp != nullptr)
			{
				return parentProp->getPropertyName() + "::" + propertyName;

			}
		}
	}

	return QString();
}

