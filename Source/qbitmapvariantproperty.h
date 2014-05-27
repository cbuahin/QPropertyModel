#ifndef QBITMAPVARIANTPROPERTY_H
#define QBITMAPVARIANTPROPERTY_H

#include <qvariantproperty.h>

class QBitmapVariantProperty : public QVariantProperty
{
	Q_OBJECT

public:
	QBitmapVariantProperty(const QBitmap& value, const QMetaProperty& metaProperty, QVariantProperty *parent = nullptr);
	~QBitmapVariantProperty();

	QVariant getData(Qt::ItemDataRole role , Column column);
private:
	
};

#endif // QBITMAPVARIANTPROPERTY_H
