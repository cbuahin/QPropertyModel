#ifndef QLINEFVARIANTPROPERTY_H
#define QLINEFVARIANTPROPERTY_H

#include <qvariantproperty.h>

typedef void (QLineF::*SetQLineFProperty)(const QPointF &) ;
typedef QPointF (QLineF::*GetQLineFProperty)() const;

class QLineFVariantProperty : public QVariantProperty
{
	Q_OBJECT

public:
	QLineFVariantProperty(const QLineF& value, const QMetaProperty& metaProperty, QVariantProperty *parent = nullptr);
	~QLineFVariantProperty();

	QVariant getData(Qt::ItemDataRole role , Column column);

	Qt::ItemFlags flags() const;

protected:
	void setupChildProperties();
	QMap<QString,SetQLineFProperty> setQLineFPropertyFunctions;
	QMap<QString,GetQLineFProperty> getQLineFPropertyFunctions;

private slots:
	void childPropertyValueChanged(const QString& propertyName, const QVariant& value);
	
};

#endif // QLINEFVARIANTPROPERTY_H
