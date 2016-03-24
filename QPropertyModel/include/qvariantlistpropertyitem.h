#ifndef QVARIANTLISTPROPERTYITEM_H
#define QVARIANTLISTPROPERTYITEM_H

#include "qvariantpropertyitem.h"

class QVariantListPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      Q_INVOKABLE QVariantListPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      virtual ~QVariantListPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

};

#endif // QVARIANTLISTPROPERTYITEM_H
