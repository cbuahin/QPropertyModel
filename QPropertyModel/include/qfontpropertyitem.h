#ifndef QFONTPROPERTYITEM_H
#define QFONTPROPERTYITEM_H

#include "qvariantpropertyitem.h"

class QFontPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      QFontPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      virtual ~QFontPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      bool hasChildren() override;

   protected:
      void setChildValues() override;

   private slots:
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_settingChildren;
};

#endif // QFONTPROPERTYITEM_H
