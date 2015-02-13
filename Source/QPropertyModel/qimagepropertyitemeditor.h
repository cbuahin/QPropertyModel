#ifndef QIMAGEPROPERTYITEMEDITOR_H
#define QIMAGEPROPERTYITEMEDITOR_H

#include "qpopuppropertyitemeditor.h"

class QImagePropertyItemEditor : public QPopUpPropertyItemEditor
{
	Q_OBJECT


public:

	QImagePropertyItemEditor(QWidget *parent);
	~QImagePropertyItemEditor();

private slots:
     void onOpenEditorClicked() Q_DECL_OVERRIDE;

	 void setUpChildWidget() Q_DECL_OVERRIDE;

	 void setValue(const QVariant& value) Q_DECL_OVERRIDE;

	 QVariant getValue() const Q_DECL_OVERRIDE;

private:
	QMetaType::Type m_imageType;

};

#endif // QIMAGEPROPERTYITEMEDITOR_H
