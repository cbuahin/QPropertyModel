#ifndef QVARIANTHOLDERHELPER_H
#define QVARIANTHOLDERHELPER_H

#include "qpropertymodel_global.h"
#include <QVariant>
#include <QModelIndex>
#include "qobjectpropertyitem.h"

class QPROPERTYMODEL_EXPORT QVariantHolderHelper : public QObject
{
      Q_OBJECT
      Q_PROPERTY(QVariant Value READ value WRITE setValue NOTIFY valueChanged)

   public:
      QVariantHolderHelper(const QVariant& value, QObject* parent);

      virtual ~QVariantHolderHelper();

      QVariant value() const;

      void setValue(const QVariant& value);

      QModelIndex modelIndex() const;

      void setModelIndex(const QModelIndex& index);

   private:
      QString objectName() const;

   signals:
      void valueChanged();

   private:
      QVariant m_value;
      QModelIndex m_index;
};





#endif // QVARIANTHOLDERHELPER_H
