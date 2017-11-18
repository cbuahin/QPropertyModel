#ifndef QOBJECTLISTPROPERTYITEM_H
#define QOBJECTLISTPROPERTYITEM_H

#include "qvariantpropertyItem.h"

typedef QList<QObject*> (VariantToObjectListConverter)(const QVariant&);

class QPROPERTYMODEL_EXPORT QObjectListPropertyItem :  public QVariantPropertyItem
{
      Q_OBJECT

   public:

      Q_INVOKABLE QObjectListPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem* parent);

      virtual ~ QObjectListPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole role = Qt::UserRole) const override;

      void setQVariantToQObjectListConverter(VariantToObjectListConverter* converter);

   private:
      VariantToObjectListConverter* m_variantToObjectListConverter;

};

#endif // QOBJECTLISTPROPERTYITEM_H


