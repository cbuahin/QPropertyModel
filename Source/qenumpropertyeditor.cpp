#include "stdafx.h"
#include "qenumpropertyeditor.h"

QEnumPropertyEditor::QEnumPropertyEditor(QWidget *parent)
	: QPropertyFromListEditor(parent)
{

}

QEnumPropertyEditor::~QEnumPropertyEditor()
{

}

void QEnumPropertyEditor::setValue(const QVariant& value)
{
	comboBox->blockSignals(true);
	QString valueToFind = metaEnum.valueToKey(value.toInt());
	int index = comboBox->findData(valueToFind, Qt::EditRole);

	if(index > -1)
	{
		comboBox->setCurrentIndex(index);
	}

	comboBox->blockSignals(false);
}

QVariant QEnumPropertyEditor::getValue() const
{
	QVariant value = comboBox->itemData(comboBox->currentIndex() , Qt::EditRole);
    return metaEnum.keyToValue(value.toString().toStdString().c_str());
}


void QEnumPropertyEditor::setupModel(const QMetaEnum& metaProp)
{
	this->metaEnum = metaProp;

	comboBox->blockSignals(true);

	int max = metaProp.keyCount();

	for(int i = 0 ; i < max ; i++)
	{
		comboBox->addItem(metaProp.key(i));
	}
	
	comboBox->blockSignals(false);
}