#ifndef QIMAGEPROPERTYITEM_H
#define QIMAGEPROPERTYITEM_H

#include "qvariantpropertyItem.h"


class QImagePropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      QImagePropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      virtual ~QImagePropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

};

#endif // QIMAGEPROPERTYITEM_H
