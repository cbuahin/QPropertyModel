#include "stdafx.h"
#include "qpropertyfromlisteditor.h"

QPropertyFromListEditor::QPropertyFromListEditor(QWidget *parent)
	: QAbstractPropertyEditor(parent)
{
	comboBox = new QComboBox(this);
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(comboBox);

	comboBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	connect(comboBox , SIGNAL(currentIndexChanged(int)), this,SLOT(currentIndexChanged(int)));
}

QPropertyFromListEditor::~QPropertyFromListEditor()
{
	delete comboBox;
}

void QPropertyFromListEditor::setValue(const QVariant& value)
{
	comboBox->blockSignals(true);

	int index = comboBox->findData(value, Qt::EditRole);

	if(index > -1)
	{
		comboBox->setCurrentIndex(index);
	}

	comboBox->blockSignals(false);
}

QVariant QPropertyFromListEditor::getValue() const
{
	QVariant value = comboBox->itemData(comboBox->currentIndex() , Qt::EditRole);
    return value;
}

void QPropertyFromListEditor::currentIndexChanged(int index)
{
	emit valueChanged();
}