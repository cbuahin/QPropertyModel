#ifndef QCOLORPROPERTYITEMEDITOR_H
#define QCOLORPROPERTYITEMEDITOR_H

#include "qpopuppropertyitemeditor.h"

class QColorPropertyItemEditor : public QPopUpPropertyItemEditor
{
	Q_OBJECT

public:
	QColorPropertyItemEditor(QWidget *parent);
	~QColorPropertyItemEditor();

void setValue(const QVariant& value) Q_DECL_OVERRIDE;

private slots:
       void onColorAccepted();

	
};

#endif // QCOLORPROPERTYITEMEDITOR_H
