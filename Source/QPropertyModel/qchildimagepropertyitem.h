#ifndef QCHILDIMAGEPROPERTYITEM_H
#define QCHILDIMAGEPROPERTYITEM_H

#include "qpropertyItem.h"

class QChildImagePropertyItem : public QPropertyItem
{
	Q_OBJECT

public:
	QChildImagePropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent);
	~QChildImagePropertyItem();

	QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const Q_DECL_OVERRIDE;
	
};

#endif // QCHILDIMAGEPROPERTYITEM_H
