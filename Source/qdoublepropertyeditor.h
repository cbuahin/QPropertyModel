#ifndef QDOUBLEPROPERTYEDITOR_H
#define QDOUBLEPROPERTYEDITOR_H

#include <qabstractpropertyeditor.h>

class QDoublePropertyEditor : public QAbstractPropertyEditor
{
	Q_OBJECT

public:
	QDoublePropertyEditor(QWidget *parent);
    ~QDoublePropertyEditor();


	void setValue(const QVariant& value) ; 
    QVariant getValue() const; 


private slots:
	void textChanged(const QString & text);
    //void internalValueChanged(double value);
	//void precisionValueChanged(int value);

protected:
	QLineEdit* lineEditor;
	QString originalStyle;
	double mostRecent;
	//QSpinBox* precSpinBox;
	//QStringListModel* model;
};

#endif // QDOUBLEPROPERTYEDITOR_H
