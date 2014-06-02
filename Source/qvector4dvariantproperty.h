#ifndef QVECTOR4DVARIANTPROPERTY_H
#define QVECTOR4DVARIANTPROPERTY_H

#include <qvariantproperty.h>

typedef void (QVector4D::*SetQVector4DProperty)(float) ;
typedef float (QVector4D::*GetQVector4DProperty)() const;

class QVector4DVariantProperty : public QVariantProperty
{
	Q_OBJECT

public:
	QVector4DVariantProperty(const QVector4D& value, const QMetaProperty& metaProperty, QtPropertyModel* const &  model, int row = 0, QVariantProperty *parent = nullptr);
	~QVector4DVariantProperty();

	bool hasChildren() ;
	
	QVariant getData(Qt::ItemDataRole role , Column column);

	Qt::ItemFlags flags() const;

protected:
	void setupChildProperties();
	QMap<QString,SetQVector4DProperty> setPropertyValueFunctions;
	QMap<QString,GetQVector4DProperty> getPropertyValueFunctions;

private slots:
	void childPropertyValueChanged(const QString& propertyName, const QVariant& value);
	
};

#endif // QVECTOR4DVARIANTPROPERTY_H
