#ifndef QLINEPROPERTYITEM_H
#define QLINEPROPERTYITEM_H

#include "qvariantpropertyItem.h"

class QLinePropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      QLinePropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      virtual ~QLinePropertyItem();

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

#endif // QLINEPROPERTYITEM_H
