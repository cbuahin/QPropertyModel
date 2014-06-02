#ifndef QLINEVARIANTPROPERTY_H
#define QLINEVARIANTPROPERTY_H

#include <qvariantproperty.h>

typedef void (QLine::*SetQLineProperty)(const QPoint &) ;
typedef QPoint (QLine::*GetQLineProperty)() const;

class QLineVariantProperty : public QVariantProperty
{
	Q_OBJECT

public:
	QLineVariantProperty(const QLine& value, const QMetaProperty& metaProperty, QtPropertyModel* const &  model,int row = 0, QVariantProperty *parent = nullptr);
	~QLineVariantProperty();

	bool hasChildren() ;
	QVariant getData(Qt::ItemDataRole role , Column column);

	Qt::ItemFlags flags() const;

protected:
	void setupChildProperties();
	QMap<QString,SetQLineProperty> setQLinePropertyFunctions;
	QMap<QString,GetQLineProperty> getQLinePropertyFunctions;

private slots:
	void childPropertyValueChanged(const QString& propertyName, const QVariant& value);
	
};

#endif // QLINEVARIANTPROPERTY_H
