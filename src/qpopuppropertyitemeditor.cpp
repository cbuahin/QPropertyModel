/*!
 * \author Caleb Amoa Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * \license
 * This file and its associated files, and libraries are free software.
 * You can redistribute it and/or modify it under the terms of the
 * Lesser GNU General Public License as published by the Free Software Foundation;
 * either version 3 of the License, or (at your option) any later version.
 * This file and its associated files is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.(see <http://www.gnu.org/licenses/> for details)
 * \copyright Copyright 2014-2018, Caleb Buahin, All rights reserved.
 * \date 2014-2018
 * \pre
 * \bug
 * \warning
 * \todo
 */

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
