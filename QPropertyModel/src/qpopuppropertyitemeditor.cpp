#include "stdafx.h"
#include "qcustomeditors.h"
#include <QDebug>

QPopUpPropertyItemEditor::QPopUpPropertyItemEditor(QWidget *parent)
   : QBasePropertyItemEditor(parent)
{
   
   m_openEditorButton = new QPushButton("...", this);
   m_openEditorButton->setToolTip("Open Editor Dialog");
   m_openEditorButton->setStatusTip("Open Editor Dialog");
   m_openEditorButton->setWhatsThis("Open Editor Dialog");
   m_openEditorButton->setFixedWidth(20);
   m_openEditorButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
   
   static_cast<QHBoxLayout*>(layout())->insertWidget(0,m_openEditorButton,0, Qt::AlignRight);
   
   connect(m_openEditorButton, SIGNAL(clicked()), this, SLOT(onOpenEditorClicked()));
}

QPopUpPropertyItemEditor::~QPopUpPropertyItemEditor()
{
   
}

QVariant QPopUpPropertyItemEditor::getValue() const
{
   return  m_valueProperty.read(m_editorDialog);
}

void QPopUpPropertyItemEditor::onOpenEditorClicked()
{
   if(m_editorDialog)
   {
      m_editorDialog->exec();
   }
}
