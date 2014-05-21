#include "stdafx.h"
#include "qabstractvariantpropertypopupeditor.h"

QAbstractVariantPropertyPopUpEditor::QAbstractVariantPropertyPopUpEditor(QWidget *parent)
	: QAbstractPropertyEditor(parent)
{

	
    openEditorButton = new QPushButton("...",this);
	openEditorButton->setToolTip("Open Editor Dialog");
	openEditorButton->setStatusTip("Open Editor Dialog");
	openEditorButton->setWhatsThis("Open Editor Dialog");


	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
	layout->setMargin(0);
	layout->addWidget(openEditorButton);

	this->setContentsMargins(0,0,0,0);
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
	openEditorButton->setSizePolicy(sizePolicy);
}

QAbstractVariantPropertyPopUpEditor::~QAbstractVariantPropertyPopUpEditor()
{
	delete openEditorButton;
}

void QAbstractVariantPropertyPopUpEditor::resizeEvent (QResizeEvent * event)
{
	int maxHeight = height();
	 openEditorButton->setMaximumWidth(maxHeight);
}
