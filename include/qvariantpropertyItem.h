#ifndef QVARIANTPROPERTYITEM_H
#define QVARIANTPROPERTYITEM_H

#include <QMetaProperty>
#include "qpropertymodel_global.h"
#include "qobjectclasspropertyitem.h"

class QPROPERTYMODEL_EXPORT  QVariantPropertyItem : public QPropertyItem
{
        Q_OBJECT

    public:
        QVariantPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

        virtual ~QVariantPropertyItem();

        QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

        bool setData(const QVariant & value, Qt::ItemDataRole role = Qt::UserRole) override;

        void resetData() override;

        QMetaProperty metaProperty() const;

    protected:
        QMetaProperty m_metaProperty;
        QObjectClassPropertyItem* m_parent;

};

Q_DECLARE_METATYPE(QVariantPropertyItem*)

#endif // QVARIANTPROPERTYITEM_H
