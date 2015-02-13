#include "stdafx.h"
#include "qvariantpropertyitem.h"

QVariantPropertyItem::QVariantPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
	: QPropertyItem(value, metaProperty.name(), parent)
{
 
	m_metaProperty = metaProperty;
	m_parent = parent;
	m_isEnabled = m_metaProperty.isReadable();
	m_isEditable = m_metaProperty.isWritable();
	m_isSelectable = m_metaProperty.isReadable();
	m_canReset = m_metaProperty.isResettable();
		
}

QVariantPropertyItem::~QVariantPropertyItem()
{

}

QVariant QVariantPropertyItem::data(int column, Qt::ItemDataRole  role) const
{

	switch (column)
	{
	case QPropertyItem::Property:
		switch (role)
		{
		case Qt::DisplayRole:
			return m_name;
			break;
		}

		break;
	case QPropertyItem::Value:
		switch (role)
		{
		case Qt::DisplayRole:
		case Qt::EditRole:
		case Qt::ToolTipRole:
		case Qt::StatusTipRole:
		case Qt::WhatsThisRole:
			return m_metaProperty.read(m_parent->qObject());
			break;
		}

		break;
	}
	return QVariant();
}

bool QVariantPropertyItem::setData(const QVariant & value, Qt::ItemDataRole role)
{
	switch (role)
	{
	case Qt::EditRole:
		if ( m_metaProperty.write(m_parent->qObject(), value))
		{
			m_value = value;

			setChildValues();

			emit valueChanged(m_name, m_value);

			return true;
		}
		break;
	}

	return false;
}



void QVariantPropertyItem::resetData()
{
	if (m_canReset)
	{
		m_metaProperty.reset(m_parent->qObject());
		m_value = m_metaProperty.read(m_parent->qObject());
	}
}
