#ifndef QSIZEPROPERTYITEM_H
#define QSIZEPROPERTYITEM_H

#include "qvariantpropertyItem.h"

class QSizePropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      QSizePropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      virtual ~QSizePropertyItem();

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

#endif // QSIZEPROPERTYITEM_H
