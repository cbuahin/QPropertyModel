#ifndef QSIZEFVARIANTPROPERTY_H
#define QSIZEFVARIANTPROPERTY_H

#include <qvariantproperty.h>

typedef void (QSizeF::*SetQSizeFProperty)(qreal) ;
typedef qreal (QSizeF::*GetQSizeFProperty)() const;


class QSizeFVariantProperty :public QVariantProperty
{
	Q_OBJECT

public:
	QSizeFVariantProperty(const QSizeF& value, const QMetaProperty& metaProperty, QtPropertyModel* const &  model, int row = 0, QVariantProperty *parent = nullptr);
	~QSizeFVariantProperty();

	bool hasChildren() ;

	QVariant getData(Qt::ItemDataRole role , Column column);
	//bool setData(const QVariant & value,Qt::ItemDataRole role, Column column);

	Qt::ItemFlags flags() const;

protected:
	void setupChildProperties();
	QMap<QString,SetQSizeFProperty> setQSizeFPropertyFunctions;
	QMap<QString,GetQSizeFProperty> getQSizeFPropertyFunctions;

private slots:
	void childPropertyValueChanged(const QString& propertyName, const QVariant& value);


};


#endif // QSIZEFVARIANTPROPERTY_H
