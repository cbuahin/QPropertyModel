#ifndef QVECTOR2DVARIANTPROPERTY_H
#define QVECTOR2DVARIANTPROPERTY_H

#include <qvariantproperty.h>

typedef void (QVector2D::*SetPropertyValue)(float) ;
typedef float (QVector2D::*GetPropertyValue)() const;

class QVector2DVariantProperty : public QVariantProperty
{
	Q_OBJECT

public:
	QVector2DVariantProperty(const QVector2D& value, const QMetaProperty& metaProperty, QVariantProperty *parent = nullptr);
	~QVector2DVariantProperty();

	QVariant getData(Qt::ItemDataRole role , Column column);

	Qt::ItemFlags flags() const;

protected:
	void setupChildProperties();
	QMap<QString,SetPropertyValue> setPropertyValueFunctions;
	QMap<QString,GetPropertyValue> getPropertyValueFunctions;

private slots:
	void childPropertyValueChanged(const QString& propertyName, const QVariant& value);
	
};

#endif // QVECTOR2DVARIANTPROPERTY_H
