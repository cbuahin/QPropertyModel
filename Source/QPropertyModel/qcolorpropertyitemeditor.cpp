#include "stdafx.h"
#include "qcolorpropertyitemeditor.h"
#include "qcolordialog.h"


QColorPropertyItemEditor::QColorPropertyItemEditor(QWidget *parent)
	: QPopUpPropertyItemEditor(parent)
{
	m_editorWidget = new QColorDialog(this);
	qobject_cast<QColorDialog*>(m_editorWidget)->setOption(QColorDialog::ShowAlphaChannel);
	connect(qobject_cast<QColorDialog*>(m_editorWidget), SIGNAL(accepted()), this, SLOT(onColorAccepted()));
	int pIndex = m_editorWidget->metaObject()->indexOfProperty("currentColor");
	m_valueProperty = m_editorWidget->metaObject()->property(pIndex);

}

QColorPropertyItemEditor::~QColorPropertyItemEditor()
{

}

void QColorPropertyItemEditor::setValue(const QVariant& value)
{
	if (value.canConvert<QColor>())
	{
		QColor c = qvariant_cast<QColor>(value);
	
		qobject_cast<QColorDialog*>(m_editorWidget)->setCurrentColor(c);
	}
}

void QColorPropertyItemEditor::onColorAccepted()
{
	emit valueChanged(this);
}
