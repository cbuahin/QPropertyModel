#include "stdafx.h"
#include "qpropertyfromlisteditor.h"

QPropertyFromListEditor::QPropertyFromListEditor(QWidget *parent)
	: QAbstractPropertyEditor(parent)
{
	comboBox = new QComboBox(this);
	comboBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	connect(comboBox , SIGNAL(currentIndexChanged(int)), this,SLOT(currentIndexChanged(int)));
}

QPropertyFromListEditor::~QPropertyFromListEditor()
{
	
}

void QPropertyFromListEditor::setupModel(QMetaType::Type type)
{
	
	if(type == QMetaType::type("QFontFamilyProperty"))
	{
		QFontDatabase dbase;
		QStringList familyList = dbase.families(QFontDatabase::WritingSystem::Any);
		comboBox->addItems(familyList);

		for(int i = 0 ; i < familyList.count() ; i++)
		{
			comboBox->setItemData(i,familyList[i],Qt::FontRole);
		}
	}
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
    return comboBox->itemData(comboBox->currentIndex() , Qt::EditRole);
}

void QPropertyFromListEditor::currentIndexChanged(int index)
{
	
	emit valueChanged();
}