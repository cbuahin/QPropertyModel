/****************************************************************************
**
**  Copyright (C) 2014 Caleb Amoa Buahin
**  Contact: calebgh@gmail.com
** 
**  This file is part of QPropertGrid.exe and QPropertGrid.dll
**
**  QPropertGrid.exe and QPropertGrid.dll and its associated files is free software; you can redistribute it and/or modify
**  it under the terms of the Lesser GNU General Public License as published by
**  the Free Software Foundation; either version 3 of the License, or
**  (at your option) any later version.
**
**  QPropertGrid.exe and QPropertGrid.dll and its associated files is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  Lesser GNU General Public License for more details.
**
**  You should have received a copy of the Lesser GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>
**
****************************************************************************/
#include "stdafx.h"

#include "qvariantobjectsuperclassproperty.h"
#include <qboolvariantproperty.h>
#include <qcolorvariantproperty.h>
#include <qfontvariantproperty.h>
#include <qsizevariantproperty.h>
#include <qsizefvariantproperty.h>
#include <qrectvariantproperty.h>
#include <qrectfvariantproperty.h>
#include <qpointvariantproperty.h>
#include <qpointfvariantproperty.h>
#include <qlinevariantproperty.h>
#include <qlinefvariantproperty.h>
#include <qvector2dvariantproperty.h>
#include <qvector3dvariantproperty.h>
#include <qvector4dvariantproperty.h>
#include <qpixmapvariantproperty.h>
#include <qbitmapvariantproperty.h>
#include <qenumvariantproperty.h>
#include <qflagsvariantproperty.h>
#include <qiconvariantproperty.h>
#include <qbrushvariantproperty.h>
#include <qpenvariantproperty.h>
#include <qsizepolicyvariantproperty.h>
#include <qstringlistvariantproperty.h>
#include <qvariantmapproperty.h>
#include <qvarianthashproperty.h>
#include <qvariantlistproperty.h>

QVariantObjectSuperClassProperty::QVariantObjectSuperClassProperty(QObject* const &object, const  QMetaObject* superClassMetaObject,QtPropertyModel* const &  model, int row,  QVariantProperty *parent)
	: QVariantProperty(QVariant::fromValue(object), QMetaProperty(),model,row, parent), object(object)
{
	this->object = object;
	this->superClassMetaObject = superClassMetaObject;
	columnCount = 2;
}

QVariantObjectSuperClassProperty::~QVariantObjectSuperClassProperty()
{
	//delete superClassMetaObject;
}

bool QVariantObjectSuperClassProperty::hasChildren()
{
	if(!(superClassMetaObject == nullptr))
	{

		QList<QMetaProperty> superclassProperties;

		int propertyCount = 0;
		int startIndex =0;
		const QMetaObject* baseClass  = superClassMetaObject->superClass();

		if(baseClass != nullptr)
		{
			startIndex = baseClass->propertyCount();
		}

		propertyCount = superClassMetaObject->propertyCount();
		int size = propertyCount - startIndex;

		if(size > 0)
			return true;
	}


	return false;
}

QVariant QVariantObjectSuperClassProperty::getData(Qt::ItemDataRole  role , Column column)
{
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
		if(column == Column::PropertyNameColumn)
		{
			QString test(metaProperty.name());
			return QVariant(superClassMetaObject->className());
		}
		break;
	case Qt::FontRole:
		{
			QFont font(QApplication::font());
			font.setBold(true);
		}
		break;
	case Qt::TextAlignmentRole:
		return QVariant();
		break;
	case Qt::BackgroundRole:
		return QBrush(Qt::lightGray);
		break;
	case Qt::ForegroundRole:
		return QBrush(Qt::white);
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
	return QVariant();

}

bool QVariantObjectSuperClassProperty::setData(const QVariant & value, Qt::ItemDataRole  role, Column column)
{
	emit valueChangedSignal(propertyName,this->value);

	setupChildProperties();

	return true;
}

Qt::ItemFlags  QVariantObjectSuperClassProperty::flags() const
{
	Qt::ItemFlags flags = Qt::ItemIsSelectable;

	if(metaProperty.isValid() && metaProperty.isWritable())
	{
		flags = flags |Qt::ItemIsEnabled;
	}
	return flags;
}

void QVariantObjectSuperClassProperty::setupChildProperties()
{
	if(!(superClassMetaObject == nullptr))
	{
		if(!childPropertiesSet)
		{
			QList<QMetaProperty> superclassProperties;

			int propertyCount = 0;
			int startIndex =0;
			const QMetaObject* baseClass  = this->superClassMetaObject->superClass();

			if(baseClass != nullptr)
			{
				startIndex = baseClass->propertyCount();
			}

			int size = children.count();

			if( size > 0)
			{	
				qDeleteAll(children);
				children.clear();
			}

			propertyCount = superClassMetaObject->propertyCount();
			size = propertyCount - startIndex;

			int count  = 0;

			for(int i = 0; i < size ; i++)
			{
				QMetaProperty prop = superClassMetaObject->property(startIndex + i);
				QString name (prop.name());

				QVariant tvalue = prop.read(object);
				int type = tvalue.userType();

				QVariantProperty* propn = nullptr;

				switch (type)
				{
				case QMetaType::Bool:
					propn = new QBoolVariantProperty(tvalue.toBool(), prop,  model, count , this);
					break;
				case QMetaType::QFont:
					propn = new QFontVariantProperty(qvariant_cast<QFont>(tvalue), prop,  model, count , this);
					break;
				case QMetaType::QColor:
					propn = new QColorVariantProperty(qvariant_cast<QColor>(tvalue), prop,  model, count , this);
					break;	
				case QMetaType::Int:
					{
						if(prop.isEnumType())
						{

							if(prop.isFlagType())
							{
								propn = new QFlagsVariantProperty(tvalue, prop.enumerator(), prop,  model, count , this);
							}
							else
							{
								propn = new QEnumVariantProperty(tvalue, prop.enumerator(), prop,  model, count , this);
							}
						}
						else if(prop.isFlagType())
						{
							propn = new QFlagsVariantProperty(tvalue, prop.enumerator(), prop,  model, count , this);
						}
						else
						{
							propn = new QVariantProperty(tvalue, prop,  model, count , this);
						}
					}
					break;
				case QMetaType::QBrush:
					propn = new QBrushVariantProperty(qvariant_cast<QBrush>(tvalue), prop,  model, count , this);
					break;
				case QMetaType::QRect:
					propn = new QRectVariantProperty(qvariant_cast<QRect>(tvalue), prop,  model, count , this);
					break;	
				case QMetaType::QRectF:
					propn = new QRectFVariantProperty(qvariant_cast<QRectF>(tvalue), prop,  model, count , this);
					break;
				case QMetaType::QSize:
					propn = new QSizeVariantProperty(qvariant_cast<QSize>(tvalue), prop,  model, count , this);
					break;	
				case QMetaType::QSizeF:
					propn = new QSizeFVariantProperty(qvariant_cast<QSizeF>(tvalue), prop,  model, count , this);
					break;	
				case QMetaType::QLine:
					propn = new QLineVariantProperty(qvariant_cast<QLine>(tvalue), prop,  model, count , this);
					break;	
				case QMetaType::QLineF:
					propn = new QLineFVariantProperty(qvariant_cast<QLineF>(tvalue), prop,  model, count , this);
					break;	
				case QMetaType::QPoint:
					propn = new QPointVariantProperty(qvariant_cast<QPoint>(tvalue), prop,  model, count , this);
					break;	
				case QMetaType::QPointF:
					propn = new QPointFVariantProperty(qvariant_cast<QPointF>(tvalue), prop,  model, count , this);
					break;	
				case QMetaType::QVector2D:
					propn = new QVector2DVariantProperty(qvariant_cast<QVector2D>(tvalue), prop,  model, count , this);
					break;	
				case QMetaType::QVector3D:
					propn = new QVector3DVariantProperty(qvariant_cast<QVector3D>(tvalue), prop,  model, count , this);
					break;	
				case QMetaType::QVector4D:
					propn = new QVector4DVariantProperty(qvariant_cast<QVector4D>(tvalue), prop,  model, count , this);
					break;	
				case QMetaType::QBitmap:
					propn = new QBitmapVariantProperty(qvariant_cast<QBitmap>(tvalue), prop,  model, count , this);
					break;
				case QMetaType::QImage:
					propn = new QPixmapVariantProperty(qvariant_cast<QPixmap>(tvalue), prop,  model, count , this);
					break;	
				case QMetaType::QPixmap:
					propn = new QPixmapVariantProperty(qvariant_cast<QPixmap>(tvalue), prop,  model, count , this);
					break;	
				case QMetaType::QIcon:
					propn = new QIconVariantProperty(qvariant_cast<QIcon>(tvalue), prop,  model, count , this);
					break;	
				case QMetaType::QPen:
					propn = new QPenVariantProperty(qvariant_cast<QPen>(tvalue), prop,  model, count , this);
					break;
				case QMetaType::QSizePolicy:
					propn = new QSizePolicyVariantProperty(qvariant_cast<QSizePolicy>(tvalue), prop,  model, count , this);
					break;
				case QMetaType::QStringList:
					propn = new QStringListVariantProperty(qvariant_cast<QStringList>(tvalue), prop,  model, count , this);
					break;
				case QMetaType::QVariantMap:
					propn = new QVariantMapProperty(qvariant_cast<QVariantMap>(tvalue), prop,  model, count , this);
					break;
				case QMetaType::QVariantHash:
					propn = new QVariantHashProperty(qvariant_cast<QVariantHash>(tvalue), prop,  model, count , this);
					break;
				case QMetaType::QVariantList:
					propn = new QVariantListProperty(qvariant_cast<QVariantList>(tvalue), prop,  model, count , this);
					break;
				case QMetaType::Void:
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
				case QMetaType::VoidStar:
				case QMetaType::QChar:
				case QMetaType::QString:
				case QMetaType::QDate:
				case QMetaType::QTime:
				case QMetaType::QDateTime:
				case QMetaType::QByteArray:
				case QMetaType::QBitArray:
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
					propn = new QVariantProperty(tvalue, prop,  model, count , this);
					break;
				case QMetaType::QObjectStar:
				case QMetaType::UnknownType:
				case QMetaType::User:
				default:
					{
						QObject* inval = qvariant_cast<QObject*>(tvalue);

						if(inval)
						{
							propn = new QVariantQObjectProperty(inval, prop,  model, count , this);
						}
						else
						{
							propn = new QVariantProperty(tvalue, prop,  model, count , this);
						}
					}
					break;
				}

				if(propn != nullptr)
				{
					children.append(propn);
					count++;
				}
			}

			childPropertiesSet = true;
		}
		else
		{
			if(children.count() > 0)
			{
				for(int i =0 ; i < children.count() ;i++)
				{
					QVariantProperty* prop = children[i];
					QMetaProperty mprop = prop->getMetaProperty();
					QVariant tempv = mprop.read(object);
					prop->blockSignals(true);
					prop->setData(tempv);
					prop->blockSignals(false);
				}

				emit this->model->dataChanged(children[0]->getModelIndex(),children[children.count()-1]->getModelIndex());
			}
		}
	}
}