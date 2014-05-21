#ifndef QPROPERTYFROMLISTEDITOR_H
#define QPROPERTYFROMLISTEDITOR_H

#include <qabstractpropertyeditor.h>
#include <qfontfamilyproperty.h>

class QPropertyFromListEditor : public QAbstractPropertyEditor
{
	Q_OBJECT

public:
	QPropertyFromListEditor(QWidget *parent);
	~QPropertyFromListEditor();

	void setupModel(QMetaEnum enumeration);
	void setupModel(QMetaType::Type type);

    void setValue(const QVariant& value) = 0; 
    QVariant getValue() const= 0; 


private slots:
    void currentIndexChanged(int index);
	

private:
	QComboBox* comboBox;
	QStringListModel* model;
};

#endif // QPROPERTYFROMLISTEDITOR_H
