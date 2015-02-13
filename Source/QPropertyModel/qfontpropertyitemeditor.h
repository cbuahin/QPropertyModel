#ifndef QFONTPROPERTYITEMEDITOR_H
#define QFONTPROPERTYITEMEDITOR_H

#include "qpopuppropertyitemeditor.h"

class QFontPropertyItemEditor : public QPopUpPropertyItemEditor
{
	Q_OBJECT

public:
	QFontPropertyItemEditor(QWidget *parent);
	~QFontPropertyItemEditor();

	void setValue(const QVariant& value) Q_DECL_OVERRIDE;

private slots:
	void onColorAccepted();
	
};

#endif // QFONTPROPERTYITEMEDITOR_H
