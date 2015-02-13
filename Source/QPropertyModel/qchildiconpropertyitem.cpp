#include "stdafx.h"
#include "qchildiconpropertyitem.h"

QChildIconPropertyItem::QChildIconPropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent)
	: QPropertyItem(value, name , parent)
{

}

QChildIconPropertyItem::~QChildIconPropertyItem()
{

}

QVariant QChildIconPropertyItem::data(int column, Qt::ItemDataRole  role) const
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
		case Qt::EditRole:
			return m_value;
			break;
		case Qt::DecorationRole:
		{
			return  QIcon(qvariant_cast<QPixmap>(m_value));
		}
			break;
		}

		break;
	}
	return QVariant();
}