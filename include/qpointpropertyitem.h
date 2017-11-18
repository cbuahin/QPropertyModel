#ifndef QPOINTPROPERTYITEM_H
#define QPOINTPROPERTYITEM_H

#include "qvariantpropertyItem.h"

class QPointPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      QPointPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      virtual ~QPointPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      bool hasChildren() override;

      Qt::ItemFlags flags() const override;


   protected:
      void setChildValues() override;

   private slots:
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren;

};
#endif // QPOINTPROPERTYITEM_H
