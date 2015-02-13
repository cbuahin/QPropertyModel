#include "stdafx.h"
#include "qfontpropertyitemeditor.h"
#include <QFontDialog>

QFontPropertyItemEditor::QFontPropertyItemEditor(QWidget *parent)
	: QPopUpPropertyItemEditor(parent)
{
	m_editorWidget = new QFontDialog(this);
	qobject_cast<QFontDialog*>(m_editorWidget)->setOption(QFontDialog::ScalableFonts);
	qobject_cast<QFontDialog*>(m_editorWidget)->setOption(QFontDialog::NonScalableFonts);
	qobject_cast<QFontDialog*>(m_editorWidget)->setOption(QFontDialog::MonospacedFonts);
	qobject_cast<QFontDialog*>(m_editorWidget)->setOption(QFontDialog::ProportionalFonts);

	connect(qobject_cast<QFontDialog*>(m_editorWidget), SIGNAL(accepted()), this, SLOT(onColorAccepted()));
	int pIndex = m_editorWidget->metaObject()->indexOfProperty("currentFont");
	m_valueProperty = m_editorWidget->metaObject()->property(pIndex);
}

QFontPropertyItemEditor::~QFontPropertyItemEditor()
{

}

void QFontPropertyItemEditor::setValue(const QVariant& value)
{
	if (value.canConvert<QFont>())
	{
		QFont c = qvariant_cast<QFont>(value);
		qobject_cast<QFontDialog*>(m_editorWidget)->setCurrentFont(c);
	}
}

void QFontPropertyItemEditor::onColorAccepted()
{
	emit valueChanged(this);
}