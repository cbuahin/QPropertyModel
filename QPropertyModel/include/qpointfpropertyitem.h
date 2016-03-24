#ifndef QPOINTFPROPERTYITEM_H
#define QPOINTFPROPERTYITEM_H

#include "qvariantpropertyitem.h"

class QPointFPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      QPointFPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      virtual ~QPointFPropertyItem();

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

#endif // QPOINTFPROPERTYITEM_H
