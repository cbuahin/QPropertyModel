#ifndef QPROPERTYFROMLISTEDITOR_H
#define QPROPERTYFROMLISTEDITOR_H

#include <qabstractpropertyeditor.h>
#include <qfontfamilyproperty.h>

class QPropertyFromListEditor : public QAbstractPropertyEditor
{
	Q_OBJECT

public:
	QPropertyFromListEditor(QWidget *parent);
	virtual ~QPropertyFromListEditor();

    void setValue(const QVariant& value) ; 
    QVariant getValue() const; 


private slots:
    void currentIndexChanged(int index);
	

protected:
	QComboBox* comboBox;
	//QStringListModel* model;
};

#endif // QPROPERTYFROMLISTEDITOR_H
