/*!
 * \file qimagepropertyitemeditor.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of image property editor.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */

#include <QFileDialog>
#include <QBitmap>
#include <QIcon>
#include "qcustomeditors.h"

QImagePropertyItemEditor::QImagePropertyItemEditor(QWidget *parent)
   : QPopUpPropertyItemEditor(parent)
{

}

QImagePropertyItemEditor::~QImagePropertyItemEditor()
{

}

void QImagePropertyItemEditor::onOpenEditorClicked()
{
   QString filename = QFileDialog::getOpenFileName(
            this,
            tr("Open Image"),
            QDir::homePath(),
            tr("All Images (*.bmp *.gif *.ico *.jpeg *.jpg *.mng *.pbm *.pgm *.png *.svg *.svgz *.tga *.tif *.tiff *.wbmp *.xbm *.xpm)"),
            nullptr,
            QFileDialog::DontUseNativeDialog);

   if (!filename.isNull())
   {
      switch (m_imageType)
      {
         case QMetaType::QPixmap:
            {
               QPixmap pixmap = QPixmap(filename);
               m_value.setValue(pixmap);
            }
            break;
         case QMetaType::QBitmap:
            {
               QBitmap icon = QBitmap(filename);
               m_value.setValue(icon);
            }
            break;
         case QMetaType::QIcon:
            {
               QIcon icon = QIcon(filename);
               m_value.setValue(icon);
            }
            break;
         case QMetaType::QImage:
            {
               QImage image = QImage(filename);
               m_value.setValue(image);
            }
            break;
         default:
            break;
      }

      emit valueChanged(this);
   }
}

void QImagePropertyItemEditor::setUpChildWidget()
{
   m_value = m_propertyItem->data(1, Qt::EditRole);
   m_imageType = (QMetaType::Type)m_value.userType();
}

void QImagePropertyItemEditor::setValue(const QVariant& value)
{
   m_value = value;
}

QVariant QImagePropertyItemEditor::getValue() const
{
   return m_value;
}
