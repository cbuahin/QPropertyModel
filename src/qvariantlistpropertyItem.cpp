#include "stdafx.h"
#include "qvariantlistpropertyitem.h"

QVariantListPropertyItem::QVariantListPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
   : QVariantPropertyItem(value, metaProperty, parent)
{
   m_isSelectable = true;
   m_isEnabled = true;
   m_isEditable = true;
}

QVariantListPropertyItem::~QVariantListPropertyItem()
{

}

QVariant QVariantListPropertyItem::data(int column, Qt::ItemDataRole  role) const
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
            case Qt::DisplayRole:
            case Qt::ToolTipRole:
            case Qt::StatusTipRole:
            case Qt::WhatsThisRole:
               {
                  QVariantList list = qvariant_cast<QVariantList>(m_metaProperty.read(m_parent->qObject()));
                  return QString("[Count=%1]").arg(list.count());
               }
               break;
         }

         break;
   }
   return QVariant();
}
