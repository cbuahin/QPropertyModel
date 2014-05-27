#ifndef QFONTFAMILYPROPERTYEDITOR_H
#define QFONTFAMILYPROPERTYEDITOR_H

#include <qpropertyfromlisteditor.h>

class QFontFamilyPropertyEditor : public QPropertyFromListEditor
{
	Q_OBJECT

public:
	QFontFamilyPropertyEditor(QWidget *parent);
	~QFontFamilyPropertyEditor();

	void setupModel();

private:
	
};

#endif // QFONTFAMILYPROPERTYEDITOR_H
