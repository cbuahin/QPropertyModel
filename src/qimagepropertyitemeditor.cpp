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
            QDir::currentPath(),
            tr("All Images (*.bmp *.gif *.ico *.jpeg *.jpg *.mng *.pbm *.pgm *.svg *.svgz *.ico *.tga *.tif *.tiff *.wbmp *.xbm *.xpm)"));
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
