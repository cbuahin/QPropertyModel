#ifndef QPOINTFVARIANTPROPERTY_H
#define QPOINTFVARIANTPROPERTY_H

#include <qvariantproperty.h>

typedef void (QPointF::*SetQPointFProperty)(qreal) ;
typedef qreal (QPointF::*GetQPointFProperty)() const;


class QPointFVariantProperty : public QVariantProperty
{
	Q_OBJECT

public:
	QPointFVariantProperty(const QPointF& value, const QMetaProperty& metaProperty, QVariantProperty *parent = nullptr);
	~QPointFVariantProperty();

	QVariant getData(Qt::ItemDataRole role , Column column);

	Qt::ItemFlags flags() const;

protected:
	void setupChildProperties();
	QMap<QString,SetQPointFProperty> setQPointFPropertyFunctions;
	QMap<QString,GetQPointFProperty> getQPointFPropertyFunctions;

private slots:
	void childPropertyValueChanged(const QString& propertyName, const QVariant& value);
	
};
#endif // QPOINTFVARIANTPROPERTY_H
