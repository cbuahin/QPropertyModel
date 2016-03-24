#ifndef QFLAGSPROPERTYITEM_H
#define QFLAGSPROPERTYITEM_H

#include "qvariantpropertyitem.h"

class QFlagsPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      QFlagsPropertyItem(const QVariant& value, const QMetaEnum& metaEnumProperty, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      virtual ~QFlagsPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      //bool setData(const QVariant & value, Qt::ItemDataRole role = Qt::UserRole) override;

      bool hasChildren() override;

      Qt::ItemFlags flags() const override;


      QMetaEnum enumerator() const;

   protected:
      void setChildValues() override;

   private slots:
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      QMetaEnum m_metaEnum;
      bool m_isSettingChildren;
};

#endif // QFLAGSPROPERTYITEM_H
