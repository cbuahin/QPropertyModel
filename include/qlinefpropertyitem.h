#ifndef QLINEFPROPERTYITEM_H
#define QLINEFPROPERTYITEM_H

#include "qvariantpropertyItem.h"

class QLineFPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      QLineFPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      virtual ~QLineFPropertyItem();

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

#endif // QLINEFPROPERTYITEM_H
