#ifndef QBITMAPPROPERTYEDITOR_H
#define QBITMAPPROPERTYEDITOR_H

#include <QAbstractVariantPropertyPopUpEditor.h>

class QBitmapPropertyEditor : public QAbstractVariantPropertyPopUpEditor
{
	Q_OBJECT

public:
	QBitmapPropertyEditor(QWidget *parent);
	~QBitmapPropertyEditor();

	void setValue(const QVariant& value); 
	QVariant getValue() const;

	private slots:
		void buttonClicked();
private:
	QBitmap bitmap;
};

#endif // QBITMAPPROPERTYEDITOR_H
