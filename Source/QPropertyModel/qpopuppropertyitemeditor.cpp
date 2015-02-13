#include "stdafx.h"
#include "qpopuppropertyitemeditor.h"

QPopUpPropertyItemEditor::QPopUpPropertyItemEditor(QWidget *parent)
	: QBasePropertyItemEditor(parent)
{

	m_openEditorButton = new QPushButton("...", this);
	m_openEditorButton->setToolTip("Open Editor Dialog");
	m_openEditorButton->setStatusTip("Open Editor Dialog");
	m_openEditorButton->setWhatsThis("Open Editor Dialog");
	m_openEditorButton->setFixedWidth(20);
	m_openEditorButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

	static_cast<QHBoxLayout*>(layout())->insertWidget(0,m_openEditorButton);
	
	connect(m_openEditorButton, SIGNAL(clicked()), this, SLOT(onOpenEditorClicked()));
}

QPopUpPropertyItemEditor::~QPopUpPropertyItemEditor()
{

}

void QPopUpPropertyItemEditor::onOpenEditorClicked()
{
	m_editorWidget->show();
}
