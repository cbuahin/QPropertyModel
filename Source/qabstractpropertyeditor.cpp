#include "stdafx.h"
#include "qabstractpropertyeditor.h"

QAbstractPropertyEditor::QAbstractPropertyEditor(QWidget*parent)
	: QWidget(parent)
{
	this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

QAbstractPropertyEditor::~QAbstractPropertyEditor()
{

}
