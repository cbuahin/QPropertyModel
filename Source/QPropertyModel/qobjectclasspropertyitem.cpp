#include "stdafx.h"
#include "qobjectclasspropertyitem.h"
#include <QMetaProperty>
#include "qobjectpropertyitem.h"
#include "qvariantpropertyitem.h"
#include "qdebug.h"
#include "qboolpropertyitem.h"
#include "qfontpropertyitem.h"
#include "qenumpropertyitem.h"
#include "qflagspropertyitem.h"
#include "qimagepropertyitem.h"
#include "qiconpropertyitem.h"
#include "qsizepropertyitem.h"
#include "qsizefpropertyitem.h"
#include "qrectpropertyitem.h"
#include "qrectfpropertyitem.h"
#include "qpointpropertyitem.h"
#include "qpointfpropertyitem.h"
#include "qvector2dpropertyitem.h"
#include "qvector3dpropertyitem.h"
#include "qvector4dpropertyitem.h"
#include "qbrushpropertyitem.h"
#include "qpenpropertyitem.h"
#include "qlinepropertyitem.h"
#include "qlinefpropertyitem.h"

QColor QObjectClassPropertyItem::s_backgroundColor = Qt::lightGray;
QColor QObjectClassPropertyItem::s_foregroundColor = Qt::white;

QObjectClassPropertyItem::QObjectClassPropertyItem(QObject* const value, const QMetaObject* metaObject, QPropertyItem * parent)
	: QPropertyItem(QVariant::fromValue(value), metaObject->className(), parent)
{
	m_objectvalue = value;
	m_metaObject = metaObject;
}

QObjectClassPropertyItem::~QObjectClassPropertyItem()
{

}

QVariant QObjectClassPropertyItem::data(int column, Qt::ItemDataRole role) const
{

	switch (column)
	{
	case QPropertyItem::Property:
		switch (role)
		{
		case Qt::DisplayRole:
			return m_name;
		case Qt::BackgroundRole:
			return s_backgroundColor;
			break;
		case Qt::ForegroundRole:
			return s_foregroundColor;
			break;
		}
		break;
	case QPropertyItem::Value:
		switch (role)
		{
		case Qt::BackgroundRole:
			return s_backgroundColor;
			break;
		case Qt::ForegroundRole:
			return s_foregroundColor;
			break;
		}
		break;
	}
	return QVariant();
}

bool QObjectClassPropertyItem::setData(const QVariant & value, Qt::ItemDataRole role)
{
	switch (role)
	{
	case Qt::EditRole:
		m_value = value;
		break;
	}
	return false;
}

bool QObjectClassPropertyItem::hasChildren()
{
	if (m_metaObject != nullptr)
	{
		if (!m_childrenSet)
		{
			int propertyCount = 0;
			int startIndex = 0;

			const QMetaObject* baseClass = m_metaObject->superClass();

			if (baseClass != nullptr)
			{
				startIndex = baseClass->propertyCount();
			}

			propertyCount = m_metaObject->propertyCount();
			int size = propertyCount - startIndex;

			m_childrenSet = true;

			if (size > 0)
			{
				for (int i = 0; i < size; i++)
				{
					QMetaProperty property = m_metaObject->property(startIndex + i);
					QVariant cvalue = property.read(m_objectvalue);

					QMetaType::Type type = (QMetaType::Type)property.userType();

					switch (type)
					{
					case QMetaType::Void:
						break;
					case QMetaType::Int:
					{
						if (property.isEnumType())
						{
							if (property.isFlagType())
							{
								QFlagsPropertyItem* flagprop = new QFlagsPropertyItem(cvalue, property.enumerator(), property, this);
								m_children.append(flagprop);
							}
							else
							{
								QEnumPropertyItem* enumProp = new QEnumPropertyItem(cvalue, property.enumerator(), property, this);
								m_children.append(enumProp);
							}
						}
						else if (property.isFlagType())
						{
							QFlagsPropertyItem* flagprop = new QFlagsPropertyItem(cvalue, property.enumerator(), property, this);
							m_children.append(flagprop);
						}
						else
						{
							QVariantPropertyItem* cPropItem = new QVariantPropertyItem(cvalue, property, this);
							m_children.append(cPropItem);
						}
					}
					break;
					case QMetaType::Bool:
					{
						QBoolPropertyItem* item = new QBoolPropertyItem(cvalue, property, this);
						m_children.append(item);
					}
					break;
					case QMetaType::QPixmap:
					case QMetaType::QImage:
					case QMetaType::QBitmap:
					{
						QImagePropertyItem* image = new QImagePropertyItem(cvalue, property, this);
						m_children.append(image);
					}
					break;
					case QMetaType::QIcon:
					{
						QIconPropertyItem* icon = new QIconPropertyItem(cvalue, property, this);
						m_children.append(icon);
					}
					break;
					case QMetaType::QSize:
					{
						QSizePropertyItem* size = new QSizePropertyItem(cvalue, property, this);
						m_children.append(size);
					}
					break;
					case QMetaType::QSizeF:
					{

						QSizeFPropertyItem* sizef = new QSizeFPropertyItem(cvalue, property, this);
						m_children.append(sizef);
					}
					break;
					case QMetaType::QRect:
					{
						QRectPropertyItem* rect = new QRectPropertyItem(cvalue, property, this);
						m_children.append(rect);
					}
					break;
					case QMetaType::QRectF:
					{
						QRectFPropertyItem* rect = new QRectFPropertyItem(cvalue, property, this);
						m_children.append(rect);
					}
					break;
					case QMetaType::QPoint:
					{
						QPointPropertyItem* point = new QPointPropertyItem(cvalue, property, this);
						m_children.append(point);
					}
					break;
					case QMetaType::QPointF:
					{
						QPointFPropertyItem* pointf = new QPointFPropertyItem(cvalue, property, this);
						m_children.append(pointf);
					}
					break;
					case QMetaType::QVector2D:
					{
						QVector2DPropertyItem* v2d = new QVector2DPropertyItem(cvalue, property, this);
						m_children.append(v2d);
					}
					break;
					case QMetaType::QVector3D:
					{
						QVector3DPropertyItem* v3d = new QVector3DPropertyItem(cvalue, property, this);
						m_children.append(v3d);
					}
					break;
					case QMetaType::QVector4D:
					{
						QVector4DPropertyItem* v4d = new QVector4DPropertyItem(cvalue, property, this);
						m_children.append(v4d);
					}
					break;
					case QMetaType::QBrush:
					{
						QBrushPropertyItem* br = new QBrushPropertyItem(cvalue, property, this);
						m_children.append(br);

					}
					break;
					case QMetaType::QPen:
					{
						QPenPropertyItem* pen = new QPenPropertyItem(cvalue, property, this);
						m_children.append(pen);

					}
					break;
					case QMetaType::QLine:
					{
						QLinePropertyItem* line = new QLinePropertyItem(cvalue, property, this);
						m_children.append(line);
					}
						break;
					case QMetaType::QLineF:
					{
						QLineFPropertyItem* linef = new QLineFPropertyItem(cvalue, property, this);
						m_children.append(linef);

					}
					break;
					case QMetaType::QColor:
					case QMetaType::UInt:
					case QMetaType::LongLong:
					case QMetaType::ULongLong:
					case QMetaType::Double:
					case QMetaType::Long:
					case QMetaType::Short:
					case QMetaType::Char:
					case QMetaType::ULong:
					case QMetaType::UShort:
					case QMetaType::UChar:
					case QMetaType::Float:
					case QMetaType::SChar:
					case QMetaType::QChar:
					case QMetaType::QString:
					case QMetaType::QStringList:
					case QMetaType::QByteArray:
					case QMetaType::QBitArray:
					case QMetaType::QTime:
					case QMetaType::QDate:
					case QMetaType::QDateTime:
					case QMetaType::QUrl:
					case QMetaType::QLocale:
					case QMetaType::QRegExp:
					case QMetaType::QEasingCurve:
					case QMetaType::QUuid:
					case QMetaType::QVariant:
					case QMetaType::QModelIndex:
					case QMetaType::QRegularExpression:
					case QMetaType::QJsonValue:
					case QMetaType::QJsonObject:
					case QMetaType::QJsonArray:
					case QMetaType::QJsonDocument:
					case QMetaType::QVariantMap:
					case QMetaType::QVariantList:
					case QMetaType::QVariantHash:
					case QMetaType::QPalette:
					case QMetaType::QPolygon:
					case QMetaType::QRegion:
					case QMetaType::QCursor:
					case QMetaType::QKeySequence:
					case QMetaType::QTextLength:
					case QMetaType::QTextFormat:
					case QMetaType::QMatrix:
					case QMetaType::QTransform:
					case QMetaType::QMatrix4x4:
					case QMetaType::QQuaternion:
					case QMetaType::QPolygonF:
					case QMetaType::QSizePolicy:
					{
						QVariantPropertyItem* cPropItem = new QVariantPropertyItem(cvalue, property, this);
						m_children.append(cPropItem);
					}
					break;
					case QMetaType::QFont:
					{
						QVariantPropertyItem* cPropItem = new QFontPropertyItem(cvalue, property, this);
						m_children.append(cPropItem);
					}
					break;
				    case QMetaType::UnknownType:
					case QMetaType::QObjectStar:
					case QMetaType::User:
					case QMetaType::VoidStar:
					default:
					{
						QObject* qobject = qvariant_cast<QObject*>(cvalue);

						if (qobject)
						{
							QObjectPropertyItem* cPropItem = new QObjectPropertyItem((QObject*)qobject, property, this);
							m_children.append(cPropItem);
						}
					}
					break;
					}
				}
				if (m_children.count())
				return true;
			}
		}
		else
		{
			if (m_children.count() > 0)
			{
				return true;
			}
		}
	}

	return false;
}

QObject* QObjectClassPropertyItem::qObject() const
{
	return m_objectvalue;
}
