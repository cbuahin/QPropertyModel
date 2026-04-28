/*!
 * \file qpopuppropertyitemeditor.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of popup property editor base.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */


#include "qcustomeditors.h"

QPopUpPropertyItemEditor::QPopUpPropertyItemEditor(QWidget *parent)
   : QBasePropertyItemEditor(parent)
{
   m_editorDialog = nullptr;
   
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
      m_dialogOpen = true;
      m_editorDialog->exec();
      m_dialogOpen = false;
      emit valueChanged(this);
   }
}
