#ifndef QFONTFAMILYPROPERTY_H
#define QFONTFAMILYPROPERTY_H

#include <qvariantproperty.h>

class QFontFamilyProperty : public QVariantProperty
{
	Q_OBJECT

public:
	QFontFamilyProperty(const QString& propertyName, const QVariant& value, QtPropertyModel* const &  model, int row =  0, QVariantProperty *parent=nullptr);
	~QFontFamilyProperty();

   QVariant getData(Qt::ItemDataRole role , Column column);

   QString getQualifiedVariantPropertyName() const;

   static QString QualifiedVariantPropertyName;

private:
	
};
Q_DECLARE_METATYPE(QFontFamilyProperty*);

#endif // QFONTFAMILYPROPERTY_H
