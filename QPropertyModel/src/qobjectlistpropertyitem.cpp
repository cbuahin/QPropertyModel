#include "stdafx.h"
#include "qobjectlistpropertyitem.h"
#include <QDebug>

QObjectListPropertyItem::QObjectListPropertyItem(const QVariant &value, const QMetaProperty &metaProperty, QObjectClassPropertyItem *parent)
   :QVariantPropertyItem(value, metaProperty, parent) , m_variantToObjectListConverter(nullptr)
{
   m_isEnabled = m_metaProperty.isReadable();
   m_isEditable = m_metaProperty.isReadable();
   m_isSelectable = m_metaProperty.isReadable();
   m_canReset = m_metaProperty.isResettable();
}

QObjectListPropertyItem::~QObjectListPropertyItem()
{

}

QVariant QObjectListPropertyItem::data(int column, Qt::ItemDataRole  role) const
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
               {
                  QVariant value = m_metaProperty.read(m_parent->qObject());

                  if(m_variantToObjectListConverter)
                  {
                     QList<QObject*> objects =  m_variantToObjectListConverter(value);
                     value = QVariant::fromValue<QList<QObject*>>(objects);
                  }

                  return value;
               }
               break;
            case Qt::DisplayRole:
            case Qt::ToolTipRole:
            case Qt::StatusTipRole:
            case Qt::WhatsThisRole:
               {
                  QVariant value = m_metaProperty.read(m_parent->qObject());

                  if(m_variantToObjectListConverter)
                  {
                     QList<QObject*> objects =  m_variantToObjectListConverter(value);
                     return QString("[Count=%1]").arg(objects.count());
                  }
                  else
                  {
                     QList<QObject*> list = qvariant_cast<QList<QObject*>>(value);
                     return QString("[Count=%1]").arg(list.count());
                  }
               }
               break;
         }

         break;
   }
   return QVariant();
}


void QObjectListPropertyItem::setQVariantToQObjectListConverter(VariantToObjectListConverter *converter)
{
   this->m_variantToObjectListConverter = converter;
}
