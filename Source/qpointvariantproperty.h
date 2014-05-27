#ifndef QPOINTVARIANTPROPERTY_H
#define QPOINTVARIANTPROPERTY_H

#include <qvariantproperty.h>

typedef void (QPoint::*SetQPointProperty)(int) ;
typedef int (QPoint::*GetQPointProperty)() const;


class QPointVariantProperty : public QVariantProperty
{
	Q_OBJECT

public:
	QPointVariantProperty(const QPoint& value, const QMetaProperty& metaProperty, QVariantProperty *parent = nullptr);
	~QPointVariantProperty();

	QVariant getData(Qt::ItemDataRole role , Column column);

	Qt::ItemFlags flags() const;

protected:
	void setupChildProperties();
	QMap<QString,SetQPointProperty> setQPointPropertyFunctions;
	QMap<QString,GetQPointProperty> getQPointPropertyFunctions;

private slots:
	void childPropertyValueChanged(const QString& propertyName, const QVariant& value);
	
};

#endif // QPOINTVARIANTPROPERTY_H
