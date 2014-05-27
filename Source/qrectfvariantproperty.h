#ifndef QRECTFVARIANTPROPERTY_H
#define QRECTFVARIANTPROPERTY_H

#include <qvariantproperty.h>

typedef void (QRectF::*SetQRectFProperty)(qreal) ;
typedef qreal (QRectF::*GetQRectFProperty)() const;


class QRectFVariantProperty :public QVariantProperty
{
	Q_OBJECT

public:
	QRectFVariantProperty(const QRectF& value, const QMetaProperty& metaProperty, QVariantProperty *parent = nullptr);
	~QRectFVariantProperty();

	QVariant getData(Qt::ItemDataRole role , Column column);

	Qt::ItemFlags flags() const;

protected:
	void setupChildProperties();
	QMap<QString,SetQRectFProperty> setQRectFPropertyFunctions;
	QMap<QString,GetQRectFProperty> getQRectFPropertyFunctions;

private slots:
	void childPropertyValueChanged(const QString& propertyName, const QVariant& value);

};

#endif // QRECTFVARIANTPROPERTY_H
