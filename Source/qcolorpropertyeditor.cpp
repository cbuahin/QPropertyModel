#include "stdafx.h"
#include "qcolorpropertyeditor.h"

QColorPropertyEditor::QColorPropertyEditor(QWidget *parent)
	: QAbstractVariantPropertyPopUpEditor(parent)
{
	
	colorDialog = new QColorDialog(this);
  	
	colorDialog->setOptions(QColorDialog::ColorDialogOption::ShowAlphaChannel);
	connect(openEditorButton, SIGNAL(clicked()), colorDialog , SLOT(show()));
	connect(colorDialog , SIGNAL(colorSelected(QColor)),this,SLOT(colorSelected(QColor)));
}

QColorPropertyEditor::~QColorPropertyEditor()
{
	delete colorDialog;
}

void QColorPropertyEditor::setValue(const QVariant& value)
{
	colorDialog->blockSignals(true);
	colorDialog->setCurrentColor(qvariant_cast<QColor>(value));
	colorDialog->blockSignals(false);
}

QVariant QColorPropertyEditor::getValue() const
{
	return colorDialog->currentColor();
}

void QColorPropertyEditor::colorSelected(const QColor& color)
{
	emit valueChanged();
}