#ifndef QRECTPROPERTYITEM_H
#define QRECTPROPERTYITEM_H

#include "qvariantpropertyitem.h"

class QRectPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      QRectPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

     virtual ~QRectPropertyItem();

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

#endif // QRECTPROPERTYITEM_H
