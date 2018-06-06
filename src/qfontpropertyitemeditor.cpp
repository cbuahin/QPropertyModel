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
#include <QFontDialog>
#include "qcustomeditors.h"

QFontPropertyItemEditor::QFontPropertyItemEditor(QWidget *parent)
   : QPopUpPropertyItemEditor(parent)
{
   m_editorDialog = new QFontDialog(this);
   qobject_cast<QFontDialog*>(m_editorDialog)->setOption(QFontDialog::ScalableFonts);
   qobject_cast<QFontDialog*>(m_editorDialog)->setOption(QFontDialog::NonScalableFonts);
   qobject_cast<QFontDialog*>(m_editorDialog)->setOption(QFontDialog::MonospacedFonts);
   qobject_cast<QFontDialog*>(m_editorDialog)->setOption(QFontDialog::ProportionalFonts);
   qobject_cast<QFontDialog*>(m_editorDialog)->setOption(QFontDialog::DontUseNativeDialog);

   m_valueProperty = qobject_cast<QFontDialog*>(m_editorDialog)->metaObject()->userProperty();
   connect(qobject_cast<QFontDialog*>(m_editorDialog), SIGNAL(accepted()), this, SLOT(onColorAccepted()));
   int pIndex = m_editorDialog->metaObject()->indexOfProperty("currentFont");
   m_valueProperty = m_editorDialog->metaObject()->property(pIndex);
}

QFontPropertyItemEditor::~QFontPropertyItemEditor()
{

}

void QFontPropertyItemEditor::setValue(const QVariant& value)
{
   if (value.canConvert<QFont>())
   {
      QFont c = qvariant_cast<QFont>(value);
      qobject_cast<QFontDialog*>(m_editorDialog)->setCurrentFont(c);
   }
}

void QFontPropertyItemEditor::onColorAccepted()
{
   emit valueChanged(this);
}
