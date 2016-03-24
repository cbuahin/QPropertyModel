#ifndef QRECTFPROPERTYITEM_H
#define QRECTFPROPERTYITEM_H

#include "qvariantpropertyitem.h"

class QRectFPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      QRectFPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

     virtual ~QRectFPropertyItem();

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

#endif // QRECTFPROPERTYITEM_H
