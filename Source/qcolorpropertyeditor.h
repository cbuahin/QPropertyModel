#ifndef QCOLORPROPERTYEDITOR_H
#define QCOLORPROPERTYEDITOR_H

#include <QAbstractVariantPropertyPopUpEditor.h>

class QColorPropertyEditor : public QAbstractVariantPropertyPopUpEditor
{
	Q_OBJECT

public:
	QColorPropertyEditor(QWidget *parent);
	~QColorPropertyEditor();

	 void setValue(const QVariant& value); 
	 QVariant getValue() const;

private slots:
	void colorSelected(const QColor& color);

private:
	QColorDialog* colorDialog;
};

#endif // QCOLORPROPERTYEDITOR_H
