#ifndef QICONPROPERTYITEM_H
#define QICONPROPERTYITEM_H

#include "qvariantpropertyitem.h"

class QIconPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      QIconPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);
      virtual ~QIconPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      bool hasChildren() override;

   protected:
      void setChildValues() override;

   private slots:
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren;
};

#endif // QICONPROPERTYITEM_H
