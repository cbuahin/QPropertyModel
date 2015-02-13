#ifndef QCHILDBOOLPROPERTYITEM_H
#define QCHILDBOOLPROPERTYITEM_H

#include "qpropertyitem.h"

class QChildBoolPropertyItem : public QPropertyItem
{
	Q_OBJECT

public:
	QChildBoolPropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent);
	~QChildBoolPropertyItem();

	QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const Q_DECL_OVERRIDE;

	bool setData(const QVariant & value, Qt::ItemDataRole role = Qt::UserRole) Q_DECL_OVERRIDE;
	
};

#endif // QCHILDBOOLPROPERTYITEM_H
