#ifndef QFONTPROPERTYEDITOR_H
#define QFONTPROPERTYEDITOR_H

#include <QAbstractVariantPropertyPopUpEditor.h>

class QFontPropertyEditor : public QAbstractVariantPropertyPopUpEditor
{
	Q_OBJECT

public:
	QFontPropertyEditor(QWidget *parent);
	~QFontPropertyEditor();

	void setValue(const QVariant& value); 
	QVariant getValue() const;

private slots:
	void fontSelected (const QFont& font);

private:
	QFontDialog* fontDialog;
	
};

#endif // QFONTPROPERTYEDITOR_H
