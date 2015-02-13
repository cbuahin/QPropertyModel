#ifndef QIMAGEPROPERTYITEM_H
#define QIMAGEPROPERTYITEM_H

#include <QVariantPropertyItem.h>

class QImagePropertyItem : public QVariantPropertyItem
{
	Q_OBJECT

public:
	QImagePropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);
	~QImagePropertyItem();

	QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const Q_DECL_OVERRIDE;
	
};

#endif // QIMAGEPROPERTYITEM_H
