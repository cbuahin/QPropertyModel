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