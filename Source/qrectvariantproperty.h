#ifndef QRECTVARIANTPROPERTY_H
#define QRECTVARIANTPROPERTY_H

#include <qvariantproperty.h>

typedef void (QRect::*SetQRectProperty)(int) ;
typedef int (QRect::*GetQRectProperty)() const;


class QRectVariantProperty :public QVariantProperty
{
	Q_OBJECT

public:
	QRectVariantProperty(const QRect& value, const QMetaProperty& metaProperty, QtPropertyModel* const &  model, int row =0, QVariantProperty *parent = nullptr);
	~QRectVariantProperty();

	bool hasChildren() ;

	QVariant getData(Qt::ItemDataRole role , Column column);

	Qt::ItemFlags flags() const;

protected:
	void setupChildProperties();
	QMap<QString,SetQRectProperty> setQRectPropertyFunctions;
	QMap<QString,GetQRectProperty> getQRectPropertyFunctions;

private slots:
	void childPropertyValueChanged(const QString& propertyName, const QVariant& value);

};


#endif // QRECTVARIANTPROPERTY_H
