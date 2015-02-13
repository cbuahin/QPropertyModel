#include "stdafx.h"
#include "qchildimagepropertyitem.h"

QChildImagePropertyItem::QChildImagePropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent)
	: QPropertyItem(value, name , parent)
{

}

QChildImagePropertyItem::~QChildImagePropertyItem()
{

}

QVariant QChildImagePropertyItem::data(int column, Qt::ItemDataRole  role) const
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