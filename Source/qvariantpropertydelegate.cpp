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
#include "qvariantpropertydelegate.h"
#include <qvariantproperty.h>
#include <qvariantpropertybaseeditor.h>
#include <qcolorpropertyeditor.h>
#include <qfontpropertyeditor.h>

QVariantPropertyDelegate::QVariantPropertyDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
{
	 factory = new QItemEditorFactory( *QItemEditorFactory::defaultFactory());
	 this->setItemEditorFactory(factory);

	 QItemEditorCreatorBase* color = new QStandardItemEditorCreator<QColorPropertyEditor>();
	 factory->registerEditor(QMetaType::QColor, color);

	 QItemEditorCreatorBase* font = new QStandardItemEditorCreator<QFontPropertyEditor>();
	 factory->registerEditor(QMetaType::QFont, font);
}

QVariantPropertyDelegate::~QVariantPropertyDelegate()
{

}

QWidget *QVariantPropertyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QVariantProperty* property  = static_cast<QVariantProperty*>(index.internalPointer());
	
	if(property == nullptr)
		return nullptr;

	QItemEditorCreatorBase* editorBase = getRegisteredCustomEditorCreator(property->getQualifiedVariantPropertyName());
	QWidget* editor = nullptr;

	if(editorBase != nullptr)
	{
		editor = editorBase->createWidget(parent);
	}

	if(editor == nullptr)
	{
		editor = QStyledItemDelegate::createEditor(parent, option, index);
	}


	QByteArray propName = factory->valuePropertyName(property->getData().userType());
	QVariantPropertyBaseEditor* beditor = new QVariantPropertyBaseEditor(parent,editor,propName,option, index);
	
	return beditor;

}

void QVariantPropertyDelegate::setEditorData ( QWidget * editor, const QModelIndex & index ) const
{
	QVariantProperty* property  = static_cast<QVariantProperty*>(index.internalPointer());
	QVariantPropertyBaseEditor* editorT = static_cast<QVariantPropertyBaseEditor*>(editor);

	if(property!= nullptr && editorT != nullptr)
	{
		editorT->setValue(property->getData());
	}
}

void QVariantPropertyDelegate::setModelData ( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const
{
	QVariantPropertyBaseEditor* editorT = static_cast<QVariantPropertyBaseEditor*>(editor);

	if(editorT != nullptr)
	{
		QVariant value = editorT->getValue();
		model->setData(index,value);
	}

}

bool QVariantPropertyDelegate::registerCustomEditorCreator(QString& qproperty, QItemEditorCreatorBase* const & editor)
{
	if(editor !=nullptr)
	{
		if(!registeredWidgets.contains(qproperty))
		{
			registeredWidgets[qproperty] = editor;
			return true;
		}
	}

	return false;
}

QItemEditorCreatorBase* QVariantPropertyDelegate::getRegisteredCustomEditorCreator(QString& qproperty) const
{

	if(registeredWidgets.contains(qproperty))
	{
		return registeredWidgets[qproperty];
	}

	return nullptr;
}
