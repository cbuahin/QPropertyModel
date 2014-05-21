#ifndef QCOLORVARIANTPROPERTY_H
#define QCOLORVARIANTPROPERTY_H

#include <QVariantProperty.h>

class QColorVariantProperty : public QVariantProperty
{
	Q_OBJECT

public:
	QColorVariantProperty(const QVariant& value, const QMetaProperty& metaProperty, QVariantProperty *parent = nullptr);
	~QColorVariantProperty();

    QVariant getData(Qt::ItemDataRole role , Column column);
	
};

#endif // QCOLORVARIANTPROPERTY_H
