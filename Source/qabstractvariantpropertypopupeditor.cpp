#include "stdafx.h"
#include "qabstractvariantpropertypopupeditor.h"

QAbstractVariantPropertyPopUpEditor::QAbstractVariantPropertyPopUpEditor(QWidget *parent)
	: QAbstractPropertyEditor(parent)
{

	int maxHeight = 0;
	
	if(parent != nullptr)
		maxHeight = parent->height();
	else
		maxHeight = height();


    openEditorButton = new QPushButton("...",this);
	openEditorButton->setToolTip("Open Editor Dialog");
	openEditorButton->setStatusTip("Open Editor Dialog");
	openEditorButton->setWhatsThis("Open Editor Dialog");
	openEditorButton->setFixedWidth(20);
	openEditorButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	layout->setAlignment(Qt::AlignRight);
	layout->addWidget(openEditorButton);

}

QAbstractVariantPropertyPopUpEditor::~QAbstractVariantPropertyPopUpEditor()
{
	delete openEditorButton;
}

