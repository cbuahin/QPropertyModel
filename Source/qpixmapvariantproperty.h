#ifndef QPIXMAPVARIANTPROPERTY_H
#define QPIXMAPVARIANTPROPERTY_H

#include <qvariantproperty.h>

class QPixmapVariantProperty : public QVariantProperty
{
	Q_OBJECT

public:
	QPixmapVariantProperty(const QPixmap& value, const QMetaProperty& metaProperty, QVariantProperty *parent = nullptr);
	~QPixmapVariantProperty();

	QVariant getData(Qt::ItemDataRole role , Column column);
private:
	
};

#endif // QPIXMAPVARIANTPROPERTY_H
