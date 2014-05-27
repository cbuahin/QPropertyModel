#ifndef QPIXMAPPROPERTYEDITOR_H
#define QPIXMAPPROPERTYEDITOR_H

#include <QAbstractVariantPropertyPopUpEditor.h>

class QPixmapPropertyEditor : public QAbstractVariantPropertyPopUpEditor
{
	Q_OBJECT

public:
	QPixmapPropertyEditor(QWidget *parent);
	~QPixmapPropertyEditor();

	void setValue(const QVariant& value); 
	QVariant getValue() const;

private slots:
	void buttonClicked();

private:
	QPixmap pixmap;
	
};

#endif // QPIXMAPPROPERTYEDITOR_H
