#include "stdafx.h"
#include "qimagepropertyitemeditor.h"
#include <QFileDialog>
#include <QBitmap>
#include <QIcon>

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