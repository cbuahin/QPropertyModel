/****************************************************************************
**
**  Copyright (C) 2014 Caleb Amoa Buahin
**  Contact: calebgh@gmail.com
** 
**  This file is part of QPropertGrid.exe and QPropertGrid.dll
**
**  QPropertGrid.exe and QPropertGrid.dll and its associated files is free software; you can redistribute it and/or modify
**  it under the terms of the Lesser GNU General Public License as published by
**  the Free Software Foundation; either version 3 of the License, or
**  (at your option) any later version.
**
**  QPropertGrid.exe and QPropertGrid.dll and its associated files is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  Lesser GNU General Public License for more details.
**
**  You should have received a copy of the Lesser GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>
**
****************************************************************************/
#include "stdafx.h"
#include "qpixmappropertyeditor.h"

QPixmapPropertyEditor::QPixmapPropertyEditor(QWidget *parent)
	: QAbstractVariantPropertyPopUpEditor(parent)
{
		connect(openEditorButton, SIGNAL(clicked()), this , SLOT(buttonClicked()));
}

QPixmapPropertyEditor::~QPixmapPropertyEditor()
{

}

void QPixmapPropertyEditor::setValue(const QVariant& value)
{
	if(value.canConvert<QPixmap>())
	{
	   pixmap = qvariant_cast<QPixmap>(value);
	 
	}
}
QVariant QPixmapPropertyEditor::getValue() const
{
	return pixmap;
}

void QPixmapPropertyEditor::buttonClicked()
{
	QString filename = QFileDialog::getOpenFileName( 
        this, 
        tr("Open Pixmap"), 
        QDir::currentPath(), 
        tr("All Pixmaps (*.bmp *.gif *.ico *.jpeg *.jpg *.mng *.pbm *.pgm *.svg *.svgz *.ico *.tga *.tif *.tiff *.wbmp *.xbm *.xpm)") );
    if( !filename.isNull())
	{
		QPixmap temp = QPixmap(filename);
		if(!temp.isNull())
		{
			pixmap = temp;
			emit valueChanged();
		}
	}
}