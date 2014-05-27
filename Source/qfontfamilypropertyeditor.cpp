#include "stdafx.h"
#include "qfontfamilypropertyeditor.h"
#include "qfontfamilyproperty.h"

QFontFamilyPropertyEditor::QFontFamilyPropertyEditor(QWidget *parent)
	: QPropertyFromListEditor(parent)
{

	setupModel();
}

QFontFamilyPropertyEditor::~QFontFamilyPropertyEditor()
{
	
}

void QFontFamilyPropertyEditor::setupModel()
{
	QFontDatabase dbase;
	QStringList familyList = dbase.families(QFontDatabase::WritingSystem::Any);

	comboBox->blockSignals(true);

	comboBox->addItems(familyList);

	for(int i = 0 ; i < familyList.count() ; i++)
	{
		comboBox->setItemData(i,familyList[i],Qt::FontRole);
	}

	comboBox->blockSignals(false);
}
