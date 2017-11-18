#include "stdafx.h"
#include "qenumpropertyitem.h"

QEnumPropertyItem::QEnumPropertyItem(const QVariant& value, const QMetaEnum& metaEnumProperty, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
	: QVariantPropertyItem(value, metaProperty, parent)
{
	m_metaEnumProperty = metaEnumProperty;
}

QEnumPropertyItem::~QEnumPropertyItem()
{

}

QVariant QEnumPropertyItem::data(int column , Qt::ItemDataRole  role) const
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
		case Qt::ToolTipRole:
		case Qt::StatusTipRole:
		case Qt::WhatsThisRole:
		{
			QVariant v = m_metaProperty.read(m_parent->qObject());
			QString name = m_metaEnumProperty.valueToKey(v.toInt());
			return name;
		}
			break;
		case Qt::EditRole:
			return m_metaProperty.read(m_parent->qObject());
			break;
		}

		break;
	}
	return QVariant();
}

QMetaEnum QEnumPropertyItem::enumerator() const
{
	return m_metaEnumProperty;
}
