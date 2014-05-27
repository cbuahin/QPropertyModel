#ifndef QCOLORVARIANTPROPERTY_H
#define QCOLORVARIANTPROPERTY_H

#include <qvariantproperty.h>

class QColorVariantProperty : public QVariantProperty
{
	Q_OBJECT

public:
	QColorVariantProperty(const QColor& value, const QMetaProperty& metaProperty, QVariantProperty *parent = nullptr);
	~QColorVariantProperty();

    QVariant getData(Qt::ItemDataRole role , Column column);

};

#endif // QCOLORVARIANTPROPERTY_H
