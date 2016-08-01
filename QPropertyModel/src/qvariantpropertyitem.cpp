#include "stdafx.h"
#include "qvariantpropertyItem.h"
#include <QDate>
#include <QDebug>



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

                  if(value.type() == QMetaType::QDateTime)
                  {
                     QDateTime dateTime = value.toDateTime();
                     return dateTime.toString("MM/dd/yyyy hh:mm:ss AP");
                  }
                  else if(value.type() == QMetaType::QDate)
                  {
                     QDate date = value.toDate();
                     return date.toString("MM/dd/yyyy");
                  }
                  else if(value.type() == QMetaType::QTime)
                  {
                     QTime time = value.toTime();
                     return time.toString("hh:mm:ss AP");
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
         if ( m_metaProperty.write(m_parent->qObject(), value))
         {
            m_value = value;

            setChildValues();

            emit valueChanged(m_name, m_value);

            return true;
         }
         break;
   }

   return false;
}

void QVariantPropertyItem::resetData()
{
   if (m_canReset)
   {
      m_metaProperty.reset(m_parent->qObject());
      m_value = m_metaProperty.read(m_parent->qObject());
   }
}

QMetaProperty QVariantPropertyItem::metaProperty() const
{
   return m_metaProperty;
}
