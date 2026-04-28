/*!
 * \file qobjectclasspropertyitem.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of QObjectClassPropertyItem.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */


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
#include "qsizepolicypropertyitem.h"
#include "qtransformpropertyitem.h"
#include "qmatrix4x4propertyitem.h"
#include "qpolygonpropertyitem.h"
#include <QDebug>
#include <QMetaProperty>

QColor QObjectClassPropertyItem::s_backgroundColor = Qt::lightGray;
QColor QObjectClassPropertyItem::s_foregroundColor = Qt::white;

QObjectClassPropertyItem::QObjectClassPropertyItem(QObject* value, const QMetaObject* metaObject, QPropertyItem * parent)
   : QPropertyItem(QVariant::fromValue(value), metaObject->className(), parent)
{
   m_objectvalues.append(value);
   m_metaObject = metaObject;
   m_isEditable = false;
}

QObjectClassPropertyItem::QObjectClassPropertyItem(const QList<QObject*>& values, const QMetaObject* metaObject, QPropertyItem * parent)
   : QPropertyItem(values.isEmpty() ? QVariant() : QVariant::fromValue(values.first()), metaObject->className(), parent)
{
   m_objectvalues = values;
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

int QObjectClassPropertyItem::rowCount() const
{
   if (!m_childrenSet && m_model)
      const_cast<QObjectClassPropertyItem*>(this)->hasChildren();
   return m_children.count();
}

bool QObjectClassPropertyItem::hasChildren()
{
   if (m_metaObject)
   {
      if (!m_childrenSet)
      {
         int startIndex = 0;

         const QMetaObject* baseClass = m_metaObject->superClass();

         if (baseClass != nullptr)
            startIndex = baseClass->propertyCount();

         int propertyCount = m_metaObject->propertyCount();
         int size = propertyCount - startIndex;

         m_childrenSet = true;

         if (size > 0 && !m_objectvalues.isEmpty())
         {
            QObject* primaryObj = m_objectvalues.first();
            m_children.reserve(m_children.size() + size);

            for (int i = 0; i < size; i++)
            {
               QMetaProperty property = m_metaObject->property(startIndex + i);
               QVariant cvalue = property.read(primaryObj);
               QMetaType::Type type = (QMetaType::Type)cvalue.userType();
               QPropertyItem* childProperty = nullptr;
               if ((childProperty = m_model->createPropertyItemByType(cvalue.userType(), cvalue, property, this)) == nullptr)
               {
                  // In Qt 6, enum/flag properties may return a user type rather than
                  // QMetaType::Int.  Check the QMetaProperty before the type switch.
                  if (property.isEnumType() || property.isFlagType())
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
                  else switch (type)
                  {
                     case QMetaType::Int:
                        {
                           childProperty = new QVariantPropertyItem(cvalue, property, this);
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
                     case QMetaType::QSizePolicy:
                        {
                           childProperty = new QSizePolicyPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QTransform:
                        {
                           childProperty = new QTransformPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QMatrix4x4:
                        {
                           childProperty = new QMatrix4x4PropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QPolygon:
                        {
                           childProperty = new QPolygonPropertyItem(cvalue, property, this);
                        }
                        break;
                     case QMetaType::QPolygonF:
                        {
                           childProperty = new QPolygonFPropertyItem(cvalue, property, this);
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
                     case QMetaType::QRegion:
                     case QMetaType::QCursor:
                     case QMetaType::QKeySequence:
                     case QMetaType::QTextLength:
                     case QMetaType::QTextFormat:
                     case QMetaType::QQuaternion:
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
   return m_objectvalues.isEmpty() ? nullptr : m_objectvalues.first();
}

QList<QObject*> QObjectClassPropertyItem::qObjects() const
{
   return m_objectvalues;
}

bool QObjectClassPropertyItem::isMultiObject() const
{
   return m_objectvalues.size() > 1;
}

bool QObjectClassPropertyItem::hasUniformValue(const QMetaProperty& prop) const
{
   if (m_objectvalues.size() <= 1)
      return true;

   QVariant primary = prop.read(m_objectvalues.first());
   for (int i = 1; i < m_objectvalues.size(); ++i)
   {
      if (prop.read(m_objectvalues[i]) != primary)
         return false;
   }
   return true;
}

bool QObjectClassPropertyItem::writePropertyToAll(const QMetaProperty& prop, const QVariant& value)
{
   bool ok = false;
   for (QObject* obj : m_objectvalues)
   {
      if (prop.write(obj, value))
         ok = true;
   }
   return ok;
}
