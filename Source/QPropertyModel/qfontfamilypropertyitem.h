#ifndef QFONTFAMILYPROPERTYITEM_H
#define QFONTFAMILYPROPERTYITEM_H

#include "qpropertyitem.h"


class QFontFamilyPropertyItem : public QPropertyItem
{
	Q_OBJECT

public:
	QFontFamilyPropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent);
	~QFontFamilyPropertyItem();

private:
	
};

#endif // QFONTFAMILYPROPERTYITEM_H
