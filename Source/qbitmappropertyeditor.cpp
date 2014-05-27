#include "stdafx.h"
#include "qbitmappropertyeditor.h"

QBitmapPropertyEditor::QBitmapPropertyEditor(QWidget *parent)
	: QAbstractVariantPropertyPopUpEditor(parent)
{
		connect(openEditorButton, SIGNAL(clicked()), this , SLOT(buttonClicked()));
}

QBitmapPropertyEditor::~QBitmapPropertyEditor()
{

}

void QBitmapPropertyEditor::setValue(const QVariant& value)
{
	if(value.canConvert<QBitmap>())
	{
	   bitmap = qvariant_cast<QBitmap>(value);
	 
	}
}
QVariant QBitmapPropertyEditor::getValue() const
{
	return bitmap;
}

void QBitmapPropertyEditor::buttonClicked()
{
	QString filename = QFileDialog::getOpenFileName( 
        this, 
        tr("Open Pixmap"), 
        QDir::currentPath(), 
        tr("All Pixmaps (*.bmp *.gif *.ico *.jpeg *.jpg *.mng *.pbm *.pgm *.svg *.svgz *.ico *.tga *.tif *.tiff *.wbmp *.xbm *.xpm)") );
    if( !filename.isNull())
	{
		QBitmap temp = QBitmap(filename);
		if(!temp.isNull())
		{
			bitmap = temp;
			emit valueChanged();
		}
	}
}