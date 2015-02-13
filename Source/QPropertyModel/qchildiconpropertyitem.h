#ifndef QCHILDICONPROPERTYITEM_H
#define QCHILDICONPROPERTYITEM_H

#include "qpropertyitem.h"

class QChildIconPropertyItem : public QPropertyItem
{
	Q_OBJECT

public:
	QChildIconPropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent);
	~QChildIconPropertyItem();

	QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const Q_DECL_OVERRIDE;


};

#endif // QCHILDICONPROPERTYITEM_H
