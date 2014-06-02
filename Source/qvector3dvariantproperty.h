#ifndef QVECTOR3DVARIANTPROPERTY_H
#define QVECTOR3DVARIANTPROPERTY_H

#include <qvariantproperty.h>

typedef void (QVector3D::*SetQVector3DProperty)(float) ;
typedef float (QVector3D::*GetQVector3DProperty)() const;

class QVector3DVariantProperty : public QVariantProperty
{
	Q_OBJECT

public:
	QVector3DVariantProperty(const QVector3D& value, const QMetaProperty& metaProperty, QtPropertyModel* const &  model, int row = 0, QVariantProperty *parent = nullptr);
	~QVector3DVariantProperty();

	bool hasChildren() ;

	QVariant getData(Qt::ItemDataRole role , Column column);

	Qt::ItemFlags flags() const;

protected:
	void setupChildProperties();
	QMap<QString,SetQVector3DProperty> setPropertyValueFunctions;
	QMap<QString,GetQVector3DProperty> getPropertyValueFunctions;

private slots:
	void childPropertyValueChanged(const QString& propertyName, const QVariant& value);
	
};

#endif // QVECTOR3DVARIANTPROPERTY_H
