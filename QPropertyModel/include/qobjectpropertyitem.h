#ifndef QOBJECTPROPERTYITEM_H
#define QOBJECTPROPERTYITEM_H

#include "qpropertyItem.h"
#include <QMetaProperty>

class QPROPERTYMODEL_EXPORT QObjectPropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      Q_INVOKABLE QObjectPropertyItem(QObject* value, const QMetaProperty& prop, QPropertyItem * parent);

      virtual ~QObjectPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      bool setData(const QVariant & value, Qt::ItemDataRole role = Qt::UserRole) override;

      bool hasChildren() override;

      QObject* qObject() const;

   protected:
      QObject* m_objectvalue;

   private:
      QMetaProperty m_property;
      bool m_hasMetaProperty ;

};

#endif // QOBJECTPROPERTYITEM_H
