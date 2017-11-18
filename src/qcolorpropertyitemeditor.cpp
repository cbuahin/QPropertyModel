#include "stdafx.h"
#include <QColorDialog>
#include "qcustomeditors.h"


QColorPropertyItemEditor::QColorPropertyItemEditor(QWidget *parent)
   : QPopUpPropertyItemEditor(parent)
{
   m_editorDialog = new QColorDialog(this);
   qobject_cast<QColorDialog*>(m_editorDialog)->setOption(QColorDialog::ShowAlphaChannel);
   m_valueProperty = qobject_cast<QColorDialog*>(m_editorDialog)->metaObject()->userProperty();
   connect(m_editorDialog, SIGNAL(accepted()), this, SLOT(onColorAccepted()));
   int pIndex = m_editorDialog->metaObject()->indexOfProperty("currentColor");
   m_valueProperty = m_editorDialog->metaObject()->property(pIndex);
}

QColorPropertyItemEditor::~QColorPropertyItemEditor()
{

}

void QColorPropertyItemEditor::setValue(const QVariant& value)
{
   if (value.canConvert<QColor>())
   {
      QColor c = qvariant_cast<QColor>(value);

      qobject_cast<QColorDialog*>(m_editorDialog)->setCurrentColor(c);
   }
}

void QColorPropertyItemEditor::onColorAccepted()
{
   emit valueChanged(this);
}
