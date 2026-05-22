/*!
 * \file qcolorpropertyitemeditor.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of color property editor.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */


#include <QColorDialog>
#include <QHBoxLayout>
#include "qcustomeditors.h"


QColorPropertyItemEditor::QColorPropertyItemEditor(QWidget *parent)
   : QBasePropertyItemEditor(parent),
     m_previewButton(new QPushButton(this)),
     m_color(Qt::white)
{
   m_previewButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   m_previewButton->setToolTip(tr("Pick colour"));
   m_previewButton->setAutoFillBackground(true);
   m_previewButton->setFocusPolicy(Qt::StrongFocus);

   // Insert the preview button at the leftmost position so it occupies the
   // full row width left of the reset button (added by the base ctor).
   if (auto *lay = qobject_cast<QHBoxLayout*>(layout()))
      lay->insertWidget(0, m_previewButton);

   restylePreviewButton();
   connect(m_previewButton, &QPushButton::clicked,
           this, &QColorPropertyItemEditor::onPickColor);
}

QColorPropertyItemEditor::~QColorPropertyItemEditor()
{
}

void QColorPropertyItemEditor::setValue(const QVariant& value)
{
   if (value.canConvert<QColor>())
   {
      m_color = qvariant_cast<QColor>(value);
      if (!m_color.isValid()) m_color = QColor(Qt::white);
      restylePreviewButton();
   }
}

QVariant QColorPropertyItemEditor::getValue() const
{
   return QVariant::fromValue(m_color);
}

void QColorPropertyItemEditor::onPickColor()
{
   m_dialogOpen = true;
   const QColor picked = QColorDialog::getColor(
      m_color.isValid() ? m_color : QColor(Qt::white),
      this,
      tr("Pick colour"),
      QColorDialog::ShowAlphaChannel);
   m_dialogOpen = false;

   if (!picked.isValid()) return;          // user cancelled
   if (picked == m_color)  return;         // no change

   m_color = picked;
   restylePreviewButton();
   emit valueChanged(this);
}

void QColorPropertyItemEditor::restylePreviewButton()
{
   // Background-coloured push-button with a contrasting text label that
   // shows the hex / RGBA value, matching the colour-button convention
   // used by the host application's PreferencesDialog.
   const QString hex = m_color.name(m_color.alpha() == 255
                                       ? QColor::HexRgb
                                       : QColor::HexArgb).toUpper();
   const QString text = (m_color.alpha() == 255)
                            ? hex
                            : QString("%1  (a=%2)").arg(hex).arg(m_color.alpha());
   const QString fg = (m_color.lightness() > 128 && m_color.alpha() > 96)
                          ? QStringLiteral("black")
                          : QStringLiteral("white");
   const QString css = QStringLiteral(
       "QPushButton { background-color: %1; color: %2; "
       "border: 1px solid #777; padding: 2px 6px; text-align: left; }")
       .arg(m_color.name(QColor::HexArgb), fg);
   m_previewButton->setStyleSheet(css);
   m_previewButton->setText(text);
}
