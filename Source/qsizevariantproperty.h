#ifndef QSIZEVARIANTPROPERTY_H
#define QSIZEVARIANTPROPERTY_H

#include <qvariantproperty.h>

typedef void (QSize::*SetQSizeProperty)(int) ;
typedef int (QSize::*GetSizeProperty)() const;


class QSizeVariantProperty :public QVariantProperty
{
	Q_OBJECT

public:
	QSizeVariantProperty(const QSize& value, const QMetaProperty& metaProperty, QtPropertyModel* const &  model, int row = 0, QVariantProperty *parent = nullptr);
	~QSizeVariantProperty();

	bool hasChildren() ;

	QVariant getData(Qt::ItemDataRole role , Column column);

	Qt::ItemFlags flags() const;

protected:
	void setupChildProperties();
	QMap<QString,SetQSizeProperty> setQSizePropertyFunctions;
	QMap<QString,GetSizeProperty> getQSizePropertyFunctions;

	private slots:
		void childPropertyValueChanged(const QString& propertyName, const QVariant& value);


};


#endif // QSIZEVARIANTPROPERTY_H
