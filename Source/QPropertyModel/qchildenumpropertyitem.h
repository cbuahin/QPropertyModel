#ifndef QCHILDENUMPROPERTYITEM_H
#define QCHILDENUMPROPERTYITEM_H

#include "qpropertyitem.h"
#include <QMetaEnum>

class QChildEnumPropertyItem : public QPropertyItem
{
	Q_OBJECT

public:
	QChildEnumPropertyItem(const QVariant& value, const QString& name, const QMetaEnum& metaEnum, QPropertyItem * parent);
	~QChildEnumPropertyItem();

	QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const Q_DECL_OVERRIDE;

	QMetaEnum QChildEnumPropertyItem::enumerator() const;

private:
	QMetaEnum m_metaEnumProperty;
};

#endif // QCHILDENUMPROPERTYITEM_H
