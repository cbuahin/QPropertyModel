#include "stdafx.h"
#include "qdoublepropertyeditor.h"

QDoublePropertyEditor::QDoublePropertyEditor(QWidget *parent)
	: QAbstractPropertyEditor(parent)
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setMargin(0);

	lineEditor = new QLineEdit(this);
	lineEditor->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	originalStyle = lineEditor->styleSheet();


	layout->addWidget(lineEditor);


	connect(lineEditor, SIGNAL(textChanged(QString)), this , SLOT(textChanged(QString)));
}

QDoublePropertyEditor::~QDoublePropertyEditor()
{
	/*delete doubleSpinBox;
	delete precSpinBox;*/
}

void QDoublePropertyEditor::setValue(const QVariant& value)
{
	if(mostRecent != value.toDouble())
	{
		lineEditor->blockSignals(true);
		mostRecent = value.toDouble();
		lineEditor->setText(value.toString());
		lineEditor->blockSignals(false);
	}
}

QVariant QDoublePropertyEditor::getValue() const
{
	QString text = lineEditor->text();
	bool found = false;
	double value = text.toDouble(&found);

	if(found)
	{
		return value;
	}
	else
	{
		return mostRecent;
	}

	return text;
}

void QDoublePropertyEditor::textChanged(const QString & text)
{
	
	bool found = false;
	double value = text.toDouble(&found);

	if(found)
	{
		lineEditor->setStyleSheet(originalStyle);
		lineEditor->setToolTip("");
	}
	else
	{
		lineEditor->setStyleSheet(" border-style: outset; border-width: 4px; border-color: red;");
		lineEditor->setToolTip("Error in entry !");
	}
}
