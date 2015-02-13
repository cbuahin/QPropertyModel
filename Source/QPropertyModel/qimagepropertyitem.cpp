#include "stdafx.h"
#include "qimagepropertyitem.h"
#include <QBitmap>

QImagePropertyItem::QImagePropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
	: QVariantPropertyItem(value, metaProperty , parent)
{

}

QImagePropertyItem::~QImagePropertyItem()
{

}


QVariant QImagePropertyItem::data(int column, Qt::ItemDataRole  role) const
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
			return m_metaProperty.read(m_parent->qObject());
			break;
		case Qt::DecorationRole:
		{
			QVariant value = m_metaProperty.read(m_parent->qObject());
			return  QIcon(qvariant_cast<QPixmap>(value));
		}
			break;
		}

		break;
	}
	return QVariant();
}
