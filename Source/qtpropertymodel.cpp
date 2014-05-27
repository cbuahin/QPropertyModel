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
#include "qtpropertymodel.h"
#include <qvariantproperty.h>
#include <qvariantqobjectproperty.h>
#include <qboolvariantproperty.h>
#include <qfontvariantproperty.h>

QtPropertyModel::QtPropertyModel(QObject *parent)
	: QAbstractItemModel (parent)
{
	rootProperty = nullptr;
	rootProperty = new QVariantQObjectProperty(parent,QMetaProperty(), nullptr);
	rootProperty->setModel(this);

	
    const QMetaObject& mo = StaticQtMetaObject::get();
    int index = mo.indexOfEnumerator("Alignment");
    QMetaEnum me = mo.enumerator(index);

}

QtPropertyModel::QtPropertyModel(const QVariant& parent)
{
	rootProperty = nullptr;

	switch (parent.userType())
	{
	case QMetaType::Bool:
		rootProperty = new QBoolVariantProperty(parent.toBool(), QMetaProperty());
		break;
	case QMetaType::Void:
	case QMetaType::Int:
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
		rootProperty = new QVariantProperty(parent, QMetaProperty());
		break;
	case QMetaType::QLocale:
	case QMetaType::QRect:
	case QMetaType::QRectF:
	case QMetaType::QSize:
	case QMetaType::QSizeF:
	case QMetaType::QLine:
	case QMetaType::QLineF:
	case QMetaType::QPoint:
	case QMetaType::QPointF:
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
	case QMetaType::QFont:
		rootProperty = new QFontVariantProperty(qvariant_cast<QFont>(parent), QMetaProperty());
		break;
	case QMetaType::QPixmap:
	case QMetaType::QBrush:
	case QMetaType::QColor:
	case QMetaType::QPalette:
	case QMetaType::QIcon:
	case QMetaType::QImage:
	case QMetaType::QPolygon:
	case QMetaType::QRegion:
	case QMetaType::QBitmap:
	case QMetaType::QCursor:
	case QMetaType::QKeySequence:
	case QMetaType::QPen:
	case QMetaType::QTextLength:
	case QMetaType::QTextFormat:
	case QMetaType::QMatrix:
	case QMetaType::QTransform:
	case QMetaType::QMatrix4x4:
	case QMetaType::QVector2D:
	case QMetaType::QVector3D:
	case QMetaType::QVector4D:
	case QMetaType::QQuaternion:
	case QMetaType::QPolygonF:
	case QMetaType::QStringList:
	case QMetaType::QSizePolicy:
		break;
	case QMetaType::QObjectStar:
		{
			QObject* tempobject = qvariant_cast<QObject*>(parent);
			if(tempobject != nullptr)
			{
				rootProperty = new QVariantQObjectProperty(tempobject,QMetaProperty(), nullptr);
			}
		}
		break;
	case QMetaType::UnknownType:
	case QMetaType::User:
	default:
		{
			QObject* tempobject = qvariant_cast<QObject*>(parent);
			if(tempobject != nullptr)
			{
				rootProperty = new QVariantQObjectProperty(tempobject,QMetaProperty(), nullptr);
			}
			

		}
		break;
	}

	rootProperty->setModel(this);
	//rootProperty = new QVariantProperty(parent,parent,QMetaProperty(), nullptr);
	//rootProperty->setModel(this);
}

QtPropertyModel::~QtPropertyModel()
{
	//	delete rootProperty;
}

bool QtPropertyModel::hasChildren(const QModelIndex & parent) const
{
	QVariantProperty* qproperty = getProperty(parent);

	if(qproperty)
	{
		return qproperty->hasChildren();
	}

	return false;
}

QModelIndex QtPropertyModel::index(int row, int column, const QModelIndex & parent) const	
{
	bool validParent = parent.isValid();
	bool hasindex = hasIndex(row, column, parent);

	if (!hasIndex(row, column, parent))
		return QModelIndex();

	QVariantProperty* parentItem = nullptr ;

	if (!parent.isValid())
		parentItem = rootProperty;
	else
		parentItem = getProperty(parent);

	QList<QVariantProperty*> children = parentItem->childProperties();

	if(row < children.count())
	{
		QVariantProperty *temp = children[row];
		QModelIndex tempindex = createIndex(row, column, temp);
		if(column == 1)
		temp->setModelIndex(tempindex);
		return tempindex;
	}
	else
	{
		return QModelIndex();
	}
}

QModelIndex QtPropertyModel::parent(const QModelIndex &index) const
{
	if(!index.isValid())
	{
		return  QModelIndex();
	}
	else
	{
		QVariantProperty* qproperty = getProperty(index);

		if(qproperty != nullptr)
		{
			QVariantProperty* parentProp = static_cast<QVariantProperty*>(qproperty->parent());

			if(parentProp != nullptr)
			{
				if(parentProp == rootProperty)
				{
					return QModelIndex();
				}
				else
				{
					return 	createIndex(qproperty->getRowInParent(),1, parentProp);
				}
			}
		}
		return  QModelIndex();
	}
}

int QtPropertyModel::rowCount(const QModelIndex &parent) const
{
	QVariantProperty* qproperty = getProperty(parent);

	if(qproperty != nullptr && qproperty->hasChildren())
	{
		return qproperty->getRowCount();
	}

	return 0;
}

int QtPropertyModel::columnCount(const QModelIndex &parent) const
{
	return 2;
	QVariantProperty* qproperty = getProperty(parent);

	if(qproperty != NULL)
	{
		if(qproperty->getColumnCount() == 2)
		{
			qDebug()<<"Test";
		}
		return qproperty->getColumnCount();
	}
	else
	{
		return 1;
	}

	return 0;
}

QVariant  QtPropertyModel::data(const QModelIndex & index, int role) const
{
	QVariantProperty* qproperty = getProperty(index);

	if(qproperty != nullptr)
	{
		return qproperty->getData((Qt::ItemDataRole)role, (QVariantProperty::Column)index.column());
	}
	else
	{
		return QVariant();
	}
}

bool QtPropertyModel::setData(const QModelIndex & index, const QVariant & value, int role)
{	
	if(index.column() == 0)
		return false;
	QVariantProperty* qproperty = getProperty(index);

	if(qproperty)
	{
		bool valid = qproperty->setData(value,(Qt::ItemDataRole)role,(QVariantProperty::Column)index.column());

		if(valid)
		{
			emit dataChanged(index,index);
			
			return valid;
		}
	}

	return false;
}

QVariantProperty*  QtPropertyModel::getProperty(const QModelIndex &index) const
{
	if(index.isValid())
	{
		QVariantProperty* qvproperty = static_cast<QVariantProperty*>(index.internalPointer());
		return qvproperty;
	}
	else
	{
		return rootProperty;
	}
}

QVariant QtPropertyModel::headerData(int section, Qt::Orientation orientation, int role) const
{

	if (orientation == Qt::Horizontal )
	{
		switch(section)
		{
		case 0:
			switch (role)
			{
			case Qt::DisplayRole:
			case Qt::ToolTipRole:
			case Qt::StatusTipRole:
				return QString("Property");
				break;
			case Qt::WhatsThisRole:
				return QString("Column for name of property");
				break;
			}
			break;
		case 1:
			switch (role)
			{
			case Qt::DisplayRole:
			case Qt::ToolTipRole:
			case Qt::StatusTipRole:
				return QString("Value");
				break;
			case Qt::WhatsThisRole:
				return QString("Column for value of property");
				break;
			}
			break;
		}
	}

	return QVariant();
}

Qt::ItemFlags QtPropertyModel::flags(const QModelIndex & index) const
{
	if(index.column() == 1)
	{
		QVariantProperty* qproperty = getProperty(index);

		if(qproperty != nullptr)
		{
			return qproperty->flags();
		}
	}
	return Qt::ItemIsEnabled|Qt::ItemIsSelectable;

}

