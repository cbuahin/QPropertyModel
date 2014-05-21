#include "stdafx.h"
#include "qfontpropertyeditor.h"

QFontPropertyEditor::QFontPropertyEditor(QWidget *parent)
	: QAbstractVariantPropertyPopUpEditor(parent)
{
	fontDialog = new QFontDialog(this);
	connect (openEditorButton,SIGNAL(clicked()), fontDialog,SLOT(show())); 
	connect(fontDialog , SIGNAL(fontSelected(QFont)),this,SLOT(fontSelected(QFont)));
}

QFontPropertyEditor::~QFontPropertyEditor()
{
	delete fontDialog;
}

void QFontPropertyEditor::setValue(const QVariant& value)
{
	fontDialog->blockSignals(true);
	fontDialog->setCurrentFont(qvariant_cast<QFont>(value));
	fontDialog->blockSignals(false);
}

QVariant QFontPropertyEditor::getValue() const
{
	return fontDialog->currentFont();
}

void QFontPropertyEditor::fontSelected(const QFont& font)
{
	emit valueChanged();
}