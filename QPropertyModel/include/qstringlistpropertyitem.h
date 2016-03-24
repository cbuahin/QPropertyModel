#ifndef QSTRINGLISTPROPERTYITEM_H
#define QSTRINGLISTPROPERTYITEM_H

#include "qvariantpropertyitem.h"

class QPROPERTYMODEL_EXPORT QStringListPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      Q_INVOKABLE QStringListPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      virtual ~QStringListPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

};

#endif // QSTRINGLISTPROPERTYITEM_H
