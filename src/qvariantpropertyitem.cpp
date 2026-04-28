/*!
 * \file qvariantpropertyitem.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of QVariantPropertyItem.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */


#include "qvariantpropertyItem.h"
#include <QDate>
#include <QDebug>
#include <QSizePolicy>
#include <QCursor>
#include <QPolygon>
#include <QTransform>
#include <QMatrix4x4>
#include <QPalette>
#include <QKeySequence>
#include <QMetaEnum>



QVariantPropertyItem::QVariantPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
   : QPropertyItem(value, metaProperty.name(), parent)
{

   m_metaProperty = metaProperty;
   m_parent = parent;

   if(m_metaProperty.isValid())
   {
      m_isEnabled = m_metaProperty.isReadable();
      m_isEditable = m_metaProperty.isWritable();
      m_isSelectable = m_metaProperty.isReadable();
      m_canReset = m_metaProperty.isResettable();
      
      // Make complex types read-only since they can't be edited as strings
      // Note: QKeySequence is editable via QKeySequenceEdit registered in delegate
      // Note: QCursor and QPalette now have custom editors
      switch (value.typeId())
      {
         case QMetaType::QSizePolicy:
         case QMetaType::QPolygon:
         case QMetaType::QPolygonF:
         case QMetaType::QTransform:
         case QMetaType::QMatrix4x4:
         case QMetaType::QRegion:
         case QMetaType::QTextLength:
         case QMetaType::QTextFormat:
         case QMetaType::QQuaternion:
         case QMetaType::QVariantMap:
         case QMetaType::QVariantHash:
            m_isEditable = false;
            break;
      }
   }

}

QVariantPropertyItem::~QVariantPropertyItem()
{

}

QVariant QVariantPropertyItem::data(int column, Qt::ItemDataRole  role) const
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
            case Qt::DisplayRole:
            case Qt::ToolTipRole:
            case Qt::StatusTipRole:
            case Qt::WhatsThisRole:
               {
                  QVariant value = m_metaProperty.read(m_parent->qObject());

                  if(value.typeId() == QMetaType::QDateTime)
                  {
                     QDateTime dateTime = value.toDateTime();
                     return dateTime.toString(Qt::ISODate);
                  }
                  else if(value.typeId() == QMetaType::QDate)
                  {
                     QDate date = value.toDate();
                     return date.toString(Qt::ISODate);
                  }
                  else if(value.typeId() == QMetaType::QTime)
                  {
                     QTime time = value.toTime();
                     return time.toString(Qt::ISODate);
                  }
                  else if(value.typeId() == QMetaType::QSizePolicy)
                  {
                     QSizePolicy sp = qvariant_cast<QSizePolicy>(value);
                     QMetaEnum policyEnum = QMetaEnum::fromType<QSizePolicy::Policy>();
                     const char* hName = policyEnum.valueToKey((int)sp.horizontalPolicy());
                     const char* vName = policyEnum.valueToKey((int)sp.verticalPolicy());
                     QString hPolicy = hName ? QString(hName) : QString::number((int)sp.horizontalPolicy());
                     QString vPolicy = vName ? QString(vName) : QString::number((int)sp.verticalPolicy());
                     return QString("[%1, %2, %3, %4]").arg(hPolicy, vPolicy).arg(sp.horizontalStretch()).arg(sp.verticalStretch());
                  }
                  else if(value.typeId() == QMetaType::QCursor)
                  {
                     QCursor cursor = qvariant_cast<QCursor>(value);
                     static const char* shapes[] = {
                        "Arrow", "UpArrow", "Cross", "Wait", "IBeam", "SizeVer", "SizeHor",
                        "SizeBDiag", "SizeFDiag", "SizeAll", "Blank", "SplitV", "SplitH",
                        "PointingHand", "Forbidden", "WhatsThis", "Busy", "OpenHand", "ClosedHand",
                        "DragCopy", "DragMove", "DragLink"
                     };
                     int shape = (int)cursor.shape();
                     if (shape >= 0 && shape < 22) {
                        return QString(shapes[shape]);
                     }
                     return QString("Cursor(%1)").arg(shape);
                  }
                  else if(value.typeId() == QMetaType::QPolygon)
                  {
                     QPolygon poly = qvariant_cast<QPolygon>(value);
                     return QString("Polygon(%1 points)").arg(poly.size());
                  }
                  else if(value.typeId() == QMetaType::QPolygonF)
                  {
                     QPolygonF poly = qvariant_cast<QPolygonF>(value);
                     return QString("PolygonF(%1 points)").arg(poly.size());
                  }
                  else if(value.typeId() == QMetaType::QTransform)
                  {
                     return QString("Transform");
                  }
                  else if(value.typeId() == QMetaType::QMatrix4x4)
                  {
                     return QString("Matrix4x4");
                  }
                  else if(value.typeId() == QMetaType::QPalette)
                  {
                     return QString("Palette");
                  }
                  else if(value.typeId() == QMetaType::QKeySequence)
                  {
                     QKeySequence seq = qvariant_cast<QKeySequence>(value);
                     return seq.toString(QKeySequence::NativeText);
                  }
                  else
                  {
                     return value;
                  }
               }
               break;
            case Qt::EditRole:
               return m_metaProperty.read(m_parent->qObject());
               break;
         }

         break;
   }
   return QVariant();
}

bool QVariantPropertyItem::setData(const QVariant & value, Qt::ItemDataRole role)
{
   switch (role)
   {
      case Qt::EditRole:
         if (m_parent->writePropertyToAll(m_metaProperty, value))
         {
            m_value = value;
            setChildValues();
            emit valueChanged(m_name, m_value);
            return true;
         }
         else
         {
            qWarning() << "QVariantPropertyItem::setData: failed to write property"
                       << m_metaProperty.name()
                       << "value:" << value;
         }
         break;
   }

   return false;
}

void QVariantPropertyItem::resetData()
{
   if (m_canReset)
   {
      // Reset all objects
      for (QObject* obj : m_parent->qObjects())
         m_metaProperty.reset(obj);
      m_value = m_metaProperty.read(m_parent->qObject());
   }
}

QMetaProperty QVariantPropertyItem::metaProperty() const
{
   return m_metaProperty;
}
