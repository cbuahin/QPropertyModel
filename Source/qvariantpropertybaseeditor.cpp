/****************************************************************************
**
**  Copyright (C) 2014 Caleb Amoa Buahin
**  Contact: calebgh@gmail.com
** 
**  This file is part of QPropertGrid.exe and QPropertGrid.dll
**
**  QPropertGrid.exe and QPropertGrid.dll and its associated files is free software; you can redistribute it and/or modify
**  it under the terms of the Lesser GNU General Public License as published by
**  the Free Software Foundation; either version 3 of the License, or
**  (at your option) any later version.
**
**  QPropertGrid.exe and QPropertGrid.dll and its associated files is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  Lesser GNU General Public License for more details.
**
**  You should have received a copy of the Lesser GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>
**
****************************************************************************/

#include "stdafx.h"
#include "qvariantpropertybaseeditor.h"



QVariantPropertyBaseEditor::QVariantPropertyBaseEditor(QWidget *parent, QWidget* const editorWidget,const QString& name, const QStyleOptionViewItem &option, const QModelIndex &index)
	: QWidget(parent)
{
	if(parent != nullptr)
	{
		parent->setObjectName("t");
	}
	this->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);
	

	valuePropertyName = name;
	this->editorWidget = editorWidget;
	int maxHeight = option.rect.height() - this->contentsMargins().bottom() - this->contentsMargins().top();
	this->index = index;

	const QMetaObject* editorMetaObject = editorWidget->metaObject();

	property = static_cast<QVariantProperty*>(index.internalPointer());

	int pcount = editorMetaObject->propertyCount();

	if(property != nullptr)
	{
		QVariant value =property->getData();

		for(int i =0 ; i < pcount ; i++)
		{
			QMetaProperty tempProp = editorMetaObject->property(i);

			if(tempProp.name() == valuePropertyName)
			{
				editorMetaProperty = tempProp;

				if(editorMetaProperty.hasNotifySignal())
				{
				  QMetaMethod signalMethod = tempProp.notifySignal();
				  QMetaMethod slotMethod = this->metaObject()->method(this->metaObject()->indexOfSlot("valueChangedSlot()"));
				  connect(editorWidget,signalMethod, this, slotMethod,Qt::DirectConnection);
				}

				editorWidget->blockSignals(true);
				editorMetaProperty.write(editorWidget,value);
				editorWidget->blockSignals(false);
				
				break;
			}
		}
	}

	editorWidget->setParent(this);
	editorWidget->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);

	QIcon eng;
	eng.addFile(":/QtPropertyGrid/resetInactive", QSize(100,100), QIcon::Mode::Disabled,QIcon::State::Off);
	eng.addFile(":/QtPropertyGrid/resetActive", QSize(100,100), QIcon::Mode::Active,QIcon::State::On);
	eng.addFile(":/QtPropertyGrid/resetActive", QSize(100,100), QIcon::Mode::Normal,QIcon::State::On);
	eng.addFile(":/QtPropertyGrid/resetActive", QSize(100,100), QIcon::Mode::Selected,QIcon::State::On);

    resetButton = new QPushButton(this);
	resetButton->setIcon(eng);

	this->setToolTip("Reset Property");
	this->setStatusTip("Reset Property");
	this->setWhatsThis("Reset Property");
	resetButton->setEnabled(property->canReset());
		
	resetButton->setFixedWidth(20);
	resetButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setSpacing(0);
	layout->setAlignment(Qt::AlignBottom);
	layout->setContentsMargins(0,0,0,0);
	layout->addWidget(editorWidget);
	layout->addWidget(resetButton);

	connect(resetButton, SIGNAL(clicked()), property , SLOT(refreshDataSlot())); 
}

QVariantPropertyBaseEditor::~QVariantPropertyBaseEditor()
{
	delete editorWidget;
}

void QVariantPropertyBaseEditor::setValue(const QVariant& value)
{
	editorMetaProperty.write(editorWidget, value);
}

QVariant QVariantPropertyBaseEditor::getValue() const 
{
   QVariant prop = editorMetaProperty.read(editorWidget);
   return prop ;
} 

void QVariantPropertyBaseEditor::focusInEvent(QFocusEvent * event)
{
	editorWidget->setFocus(Qt::FocusReason::MouseFocusReason);
}

void QVariantPropertyBaseEditor:: hideEvent(QHideEvent * event)
{
	QVariant value = editorMetaProperty.read(editorWidget);
	property->setData(value);
	emit valueChangedSignal();
}

void QVariantPropertyBaseEditor::valueChangedSlot()
{ 
	QVariant value = editorMetaProperty.read(editorWidget);
	property->setData(value);
	emit valueChangedSignal();
}
