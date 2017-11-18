#ifndef QBRUSHPROPERTYITEM_H
#define QBRUSHPROPERTYITEM_H

#include "qvariantpropertyItem.h"

class QBrushPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      QBrushPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      virtual ~QBrushPropertyItem();

      bool hasChildren() override;

      Qt::ItemFlags flags() const override;


   protected:
      void setChildValues() override;

   private slots:
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren;

};

#endif // QBRUSHPROPERTYITEM_H
