#ifndef QSIZEFPROPERTYITEM_H
#define QSIZEFPROPERTYITEM_H

#include "qvariantpropertyitem.h"

class QSizeFPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      QSizeFPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      virtual ~QSizeFPropertyItem();

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

#endif // QSIZEFPROPERTYITEM_H
