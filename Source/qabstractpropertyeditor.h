#ifndef QABSTRACTPROPERTYEDITOR_H
#define QABSTRACTPROPERTYEDITOR_H


class QAbstractPropertyEditor : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QVariant Value READ getValue WRITE setValue NOTIFY valueChanged USER true);

public:
	QAbstractPropertyEditor(QWidget *parent);
	virtual ~QAbstractPropertyEditor();

	virtual void setValue(const QVariant& value) = 0; 
	virtual QVariant getValue() const= 0; 

signals:
	void valueChanged();
	
};

#endif // QABSTRACTPROPERTYEDITOR_H
