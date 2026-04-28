
#include "qchildpropertyitems.h"
#include <QBitmap>

QChildImagePropertyItem::QChildImagePropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent)
   : QPropertyItem(value, name , parent)
{

}

QChildImagePropertyItem::~QChildImagePropertyItem()
{

}

QVariant QChildImagePropertyItem::data(int column, Qt::ItemDataRole  role) const
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
               return m_value;
               break;
            case Qt::DecorationRole:
               {
                  int typeId = m_value.typeId();
                  if (typeId == QMetaType::QPixmap || typeId == QMetaType::QBitmap)
                     return QIcon(qvariant_cast<QPixmap>(m_value));
                  else if (typeId == QMetaType::QImage)
                     return QIcon(QPixmap::fromImage(qvariant_cast<QImage>(m_value)));
                  else if (typeId == QMetaType::QIcon)
                     return qvariant_cast<QIcon>(m_value);
                  return QVariant();
               }
               break;
         }

         break;
   }
   return QVariant();
}
