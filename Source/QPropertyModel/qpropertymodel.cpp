#include "stdafx.h"
#include "qpropertymodel.h"
#include "qobjectpropertyitem.h"
#include "qpropertyitemdelegate.h"

QPropertyModel::QPropertyModel(QObject* parent)
	:QAbstractItemModel(parent)
{
	m_rootPropertyItem = nullptr;
	
}

QPropertyModel::QPropertyModel(const QVariant& item, QObject* parent)
	: QAbstractItemModel(parent)
{
	m_rootPropertyItem = nullptr;
	setParentData(item);
}

QPropertyModel::~QPropertyModel()
{
	delete m_rootPropertyItem;
}

void QPropertyModel::setParentData(const QVariant& item)
{
	beginResetModel();

	m_rootQVariantItem = item;

	if (m_rootPropertyItem)
	{
		delete m_rootPropertyItem;
		m_rootPropertyItem = NULL;
	}
	int type = item.type();

	switch (type)
	{
	case QMetaType::Void:
		break;
	case QMetaType::Bool:
		break;
	case QMetaType::Int:
		break;
	case QMetaType::UInt:
		break;
	case QMetaType::LongLong:
		break;
	case QMetaType::ULongLong:
		break;
	case QMetaType::Double:
		break;
	case QMetaType::Long:
		break;
	case QMetaType::Short:
		break;
	case QMetaType::Char:
		break;
	case QMetaType::ULong:
		break;
	case QMetaType::UShort:
		break;
	case QMetaType::UChar:
		break;
	case QMetaType::Float:
		break;
	case QMetaType::SChar:
		break;
	case QMetaType::QChar:
		break;
	case QMetaType::QString:
		break;
	case QMetaType::QStringList:
		break;
	case QMetaType::QByteArray:
		break;
	case QMetaType::QBitArray:
		break;
	case QMetaType::QDate:
		break;
	case QMetaType::QTime:
		break;
	case QMetaType::QDateTime:
		break;
	case QMetaType::QUrl:
		break;
	case QMetaType::QLocale:
		break;
	case QMetaType::QRect:
		break;
	case QMetaType::QRectF:
		break;
	case QMetaType::QSize:
		break;
	case QMetaType::QSizeF:
		break;
	case QMetaType::QLine:
		break;
	case QMetaType::QLineF:
		break;
	case QMetaType::QPoint:
		break;
	case QMetaType::QPointF:
		break;
	case QMetaType::QRegExp:
		break;
	case QMetaType::QEasingCurve:
		break;
	case QMetaType::QUuid:
		break;
	case QMetaType::QVariant:
		break;
	case QMetaType::QModelIndex:
		break;
	case QMetaType::QRegularExpression:
		break;
	case QMetaType::QJsonValue:
		break;
	case QMetaType::QJsonObject:
		break;
	case QMetaType::QJsonArray:
		break;
	case QMetaType::QJsonDocument:
		break;
	case QMetaType::QVariantMap:
		break;
	case QMetaType::QVariantList:
		break;
	case QMetaType::QVariantHash:
		break;
	case QMetaType::QFont:
		break;
	case QMetaType::QPixmap:
		break;
	case QMetaType::QBrush:
		break;
	case QMetaType::QColor:
		break;
	case QMetaType::QPalette:
		break;
	case QMetaType::QIcon:
		break;
	case QMetaType::QImage:
		break;
	case QMetaType::QPolygon:
		break;
	case QMetaType::QRegion:
		break;
	case QMetaType::QBitmap:
		break;
	case QMetaType::QCursor:
		break;
	case QMetaType::QKeySequence:
		break;
	case QMetaType::QPen:
		break;
	case QMetaType::QTextLength:
		break;
	case QMetaType::QTextFormat:
		break;
	case QMetaType::QMatrix:
		break;
	case QMetaType::QTransform:
		break;
	case QMetaType::QMatrix4x4:
		break;
	case QMetaType::QVector2D:
		break;
	case QMetaType::QVector3D:
		break;
	case QMetaType::QVector4D:
		break;
	case QMetaType::QQuaternion:
		break;
	case QMetaType::QPolygonF:
		break;
	case QMetaType::QSizePolicy:
		break;
	case QMetaType::UnknownType:
	case QMetaType::QObjectStar:
	case QMetaType::User:
	case QMetaType::VoidStar:
	default:
	{
		QObject* qobject =  qvariant_cast<QObject*>(item);

		if (qobject)
		{
			m_rootPropertyItem = new QObjectPropertyItem((QObject*)qobject, QMetaProperty(), nullptr);
		}
	}
	break;
	}

	if (m_rootPropertyItem)
	{
		m_rootPropertyItem->m_model = this;
	}

	endResetModel();
}

int	QPropertyModel::columnCount(const QModelIndex & parent) const
{
	return 2;
}

int QPropertyModel::rowCount(const QModelIndex & parent) const
{

	QPropertyItem* propertyItem = parent.isValid() ? static_cast<QPropertyItem*>(parent.internalPointer()) : m_rootPropertyItem;

	if (propertyItem)
	{
		return propertyItem->rowCount();
	}

	return 0;
}

QModelIndex	QPropertyModel::index(int row, int column, const QModelIndex & parent) const
{
	QPropertyItem* propertyItem = parent.isValid() ? static_cast<QPropertyItem*>(parent.internalPointer()) : m_rootPropertyItem;

	if (propertyItem && row > -1 && row < propertyItem->rowCount())
	{
		QPropertyItem* child = propertyItem->childPropertyItem(row);
		//child->m_model = this;
		QModelIndex tempindex;

		if (child->index().isValid() && child->index().column() == column)
		{
			return child->index();
		}
		else
		{
			tempindex = createIndex(row, column, child);

			if (column == 0)
				child->m_index = tempindex;

			return tempindex;
		}
	}

	return QModelIndex();
}

QModelIndex	QPropertyModel::parent(const QModelIndex & index) const
{
	if (index.isValid())
	{
		QPropertyItem* propertyItem = static_cast<QPropertyItem*>(index.internalPointer());

		if (propertyItem)
		{
			if (propertyItem->parent())
				return propertyItem->parent()->index();
		}
	}

	return QModelIndex();
}

QVariant QPropertyModel::data(const QModelIndex & index, int role) const
{
	Qt::ItemDataRole r = (Qt::ItemDataRole) role;

	if (index.isValid())
	{
		QPropertyItem* propertyItem = static_cast<QPropertyItem*>(index.internalPointer());

		if (propertyItem)
		{
			return propertyItem->data(index.column(), r);
		}

	}

	return QVariant();
}

bool QPropertyModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	QPropertyItem* propertyItem = index.isValid() ? static_cast<QPropertyItem*>(index.internalPointer()) : m_rootPropertyItem;

	if (propertyItem)
	{
		if (propertyItem->setData(value, (Qt::ItemDataRole)role))
		{
			emit dataChanged(index, index);

			return true;
		}
	}

	return false;
}

Qt::ItemFlags QPropertyModel::flags(const QModelIndex & index) const
{
	if (index.isValid() && index.column() > 0)
	{
		QPropertyItem* propertyItem = static_cast<QPropertyItem*>(index.internalPointer());

		if (propertyItem)
		{
			return propertyItem->flags();
		}
	}

	return Qt::ItemFlags(Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsSelectable);
}

QVariant QPropertyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == 0 && orientation == Qt::Orientation::Horizontal)
	{
		switch (section)
		{
		case 0:
			return "Property";
			break;
		case 1:
			return "Value";
			break;
		}
	}

	return QVariant();
}

bool QPropertyModel::hasChildren(const QModelIndex & parent) const
{
	QPropertyItem* propertyItem = parent.isValid() ? static_cast<QPropertyItem*>(parent.internalPointer()) : m_rootPropertyItem;

	if (propertyItem)
	{
		return propertyItem->hasChildren();
	}

	return false;
}

void QPropertyModel::clear()
{
	beginResetModel();


	endResetModel();
}

QPropertyItem* QPropertyModel::rootPropertyItem() const
{
	return m_rootPropertyItem;
}

QVariant QPropertyModel::rootQVariantItem() const
{
	return m_rootQVariantItem;
}

void QPropertyModel::onDataChanged(const QModelIndex & index)
{
	emit dataChanged(index, index);
}
