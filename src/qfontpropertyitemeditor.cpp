/*!
 * \file qfontpropertyitemeditor.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of font property editor.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
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
