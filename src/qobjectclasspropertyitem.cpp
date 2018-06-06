/*!
 * \author Caleb Amoa Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * \license
 * This file and its associated files, and libraries are free software.
 * You can redistribute it and/or modify it under the terms of the
 * Lesser GNU General Public License as published by the Free Software Foundation;
 * either version 3 of the License, or (at your option) any later version.
 * This file and its associated files is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.(see <http://www.gnu.org/licenses/> for details)
 * \copyright Copyright 2014-2018, Caleb Buahin, All rights reserved.
 * \date 2014-2018
 * \pre
 * \bug
 * \warning
 * \todo
 */

#include "stdafx.h"
#include "qobjectclasspropertyitem.h"
#include "qobjectpropertyitem.h"
#include "qvariantpropertyItem.h"
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
#include "qstringlistpropertyitem.h"
#include "qpropertymodel.h"
#include "qvariantlistpropertyitem.h"
#include <QDebug>
#include <QMetaProperty>

QColor QObjectClassPropertyItem::s_backgroundColor = Qt::lightGray;
QColor QObjectClassPropertyItem::s_foregroundColor = Qt::white;

QObjectClassPropertyItem::QObjectClassPropertyItem(QObject* value, const QMetaObject* metaObject, QPropertyItem * parent)
   : QPropertyItem(QVariant::fromValue(value), metaObject->className(), parent)
{
   m_objectvalue = value;
   m_metaObject = metaObject;
   m_isEditable = false;
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
   if (m_metaObject)
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
               QMetaType::Type type = (QMetaType::Type)cvalue.userType();
               QPropertyItem* childProperty = nullptr;


               if(! QString(property.name()).compare("Publications"))
               {
                  qDebug() << "";
               }

               if ((childProperty = m_model->createPropertyItemByType(cvalue.userType(), cvalue, property, this)) == nullptr)
               {
                  switch (type)
                  {
                     case QMetaType::Int:
                        {
                           if (property.isEnumType())
                           {
                              if (property.isFlagType())
                              {
                                 childProperty = new QFlagsPropertyItem(cvalue, property.enumerator(), property, this);
                              }
                              else
                              {
                                 childProperty = new QEnumPropertyItem(cvalue, property.enumerator(), property, this);
                              }
                           }
                           else if (property.isFlagType())
                           {
                              childProperty = new QFlagsPropertyItem(cvalue, property.enumerator(), property, this);

                           }
                           else
                           {
                              childProperty = new QVariantPropertyItem(cvalue, property, this);
                           }
                        }
                        break;
                     case QMetaType::Bool:
                        {
                           childProperty = new QBoolPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QPixmap:
                     case QMetaType::QImage:
                     case QMetaType::QBitmap:
                        {
                           childProperty = new QImagePropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QIcon:
                        {
                           childProperty = new QIconPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QSize:
                        {
                           childProperty = new QSizePropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QSizeF:
                        {

                           childProperty = new QSizeFPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QRect:
                        {
                           childProperty = new QRectPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QRectF:
                        {
                           childProperty = new QRectFPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QPoint:
                        {
                           childProperty = new QPointPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QPointF:
                        {
                           childProperty = new QPointFPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QVector2D:
                        {
                           childProperty = new QVector2DPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QVector3D:
                        {
                           childProperty = new QVector3DPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QVector4D:
                        {
                           childProperty = new QVector4DPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QBrush:
                        {
                           childProperty = new QBrushPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QPen:
                        {
                           childProperty = new QPenPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QLine:
                        {
                           childProperty = new QLinePropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QLineF:
                        {
                           childProperty = new QLineFPropertyItem(cvalue, property, this);

                        }
                        break;
                     case QMetaType::QStringList:
                        {
                           childProperty = new QStringListPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QVariantList:
                        {
                           childProperty = new QVariantListPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::Void:
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
                           childProperty = new QVariantPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QFont:
                        {
                           childProperty = new QFontPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::UnknownType:
                     case QMetaType::QObjectStar:
                     case QMetaType::User:
                     case QMetaType::VoidStar:
                     default:
                        {
                           QObject* qobject = cvalue.value<QObject*>();

                           if (qobject)
                           {
                              childProperty = new QObjectPropertyItem(qobject, property, this);
                           }
                           else
                           {
                              childProperty = new QVariantPropertyItem(cvalue, property, this);
                           }
                        }
                        break;
                  }
               }

               if (childProperty != nullptr)
               {
                  m_children.append(childProperty);
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
