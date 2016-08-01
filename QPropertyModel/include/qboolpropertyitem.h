#ifndef QBOOLPROPERTYITEM_H
#define QBOOLPROPERTYITEM_H

#include "qvariantpropertyItem.h"

class QBoolPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      QBoolPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      virtual ~QBoolPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const Q_DECL_OVERRIDE;

      bool setData(const QVariant & value, Qt::ItemDataRole role = Qt::UserRole) Q_DECL_OVERRIDE;


};


#endif // QBOOLPROPERTYITEM_H

