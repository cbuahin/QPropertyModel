#include "stdafx.h"
#include "qchildboolpropertyitem.h"

QChildBoolPropertyItem::QChildBoolPropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent)
	: QPropertyItem(value,name,parent)
{
	m_isEditable = false;
	m_isCheckable = true;
	m_isTristate = false;
}

QChildBoolPropertyItem::~QChildBoolPropertyItem()
{

}

QVariant QChildBoolPropertyItem::data(int column, Qt::ItemDataRole  role) const
{
	switch (column)
	{
	case QPropertyItem::Property:
	{
		switch (role)
		{
		case Qt::DisplayRole:
			return m_name;
			break;
		}
	}
	break;
	case QPropertyItem::Value:
	{
		switch (role)
		{
		case Qt::CheckStateRole:
		{
			if (m_value.toInt() == 0)
				return Qt::CheckState::Unchecked;
			else
				return Qt::CheckState::Checked;
		}
		break;
		}
	}
	break;
	}
	return QVariant();
}

bool QChildBoolPropertyItem::setData(const QVariant & value, Qt::ItemDataRole role)
{
	switch (role)
	{
	case Qt::CheckStateRole:
	case Qt::EditRole:
		
		m_value = qvariant_cast<bool>(value);

		emit valueChanged(m_name, m_value);

		break;
	}

	return false;
}
