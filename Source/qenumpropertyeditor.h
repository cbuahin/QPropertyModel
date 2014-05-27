#ifndef QENUMPROPERTYEDITOR_H
#define QENUMPROPERTYEDITOR_H

#include <qpropertyfromlisteditor.h>

class QEnumPropertyEditor :  public QPropertyFromListEditor
{
	Q_OBJECT

public:
	QEnumPropertyEditor(QWidget *parent);
	~QEnumPropertyEditor();

	void setupModel(const QMetaEnum& metaProp);

	void setValue(const QVariant& value) ; 
    QVariant getValue() const; 

private:
	QMetaEnum metaEnum;
};

#endif // QENUMPROPERTYEDITOR_H
