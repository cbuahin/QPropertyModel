#ifndef QPENPROPERTYITEM_H
#define QPENPROPERTYITEM_H

#include "qvariantpropertyItem.h"

class QPenPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      QPenPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      virtual ~QPenPropertyItem();

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

#endif // QPENPROPERTYITEM_H
