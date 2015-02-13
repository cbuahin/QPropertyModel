#ifndef QPOPUPPROPERTYITEMEDITOR_H
#define QPOPUPPROPERTYITEMEDITOR_H

#include "qbasepropertyitemeditor.h"

class QPopUpPropertyItemEditor : public QBasePropertyItemEditor
{
	Q_OBJECT

public:
	QPopUpPropertyItemEditor(QWidget *parent);
	virtual ~QPopUpPropertyItemEditor();

private slots:
	virtual void onOpenEditorClicked();

protected:
	QBasePropertyItemEditor* m_dialog;

private:
	QPushButton* m_openEditorButton;
};

#endif // QPOPUPPROPERTYITEMEDITOR_H
