#ifndef QENUMPROPERTYITEM_H
#define QENUMPROPERTYITEM_H

#include "qvariantpropertyItem.h"

class QEnumPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      QEnumPropertyItem(const QVariant& value, const QMetaEnum& metaEnumProperty, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      virtual ~QEnumPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      QMetaEnum enumerator() const;

   private:
      QMetaEnum m_metaEnumProperty;
};

#endif // QENUMPROPERTYITEM_H
