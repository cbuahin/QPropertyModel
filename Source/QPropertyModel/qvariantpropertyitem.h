#ifndef QVARIANTPROPERTYITEM_H
#define QVARIANTPROPERTYITEM_H

#include <QMetaProperty>
#include "qobjectclasspropertyitem.h"

class QVariantPropertyItem : public QPropertyItem
{
	Q_OBJECT
   
public:
	QVariantPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

	virtual ~QVariantPropertyItem();

	QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const Q_DECL_OVERRIDE;

	bool setData(const QVariant & value, Qt::ItemDataRole role = Qt::UserRole) Q_DECL_OVERRIDE;

	void resetData() Q_DECL_OVERRIDE;


protected:
	QMetaProperty m_metaProperty;
	QObjectClassPropertyItem* m_parent;

};

Q_DECLARE_METATYPE(QVariantPropertyItem*);

#endif // QVARIANTPROPERTYITEM_H
