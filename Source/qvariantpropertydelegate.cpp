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
#include <qfontfamilypropertyeditor.h>
#include <qdoublepropertyeditor.h>
#include <qpixmappropertyeditor.h>
#include <qbitmappropertyeditor.h>
#include <qenumpropertyeditor.h>
#include <qenumvariantproperty.h>
#include <qiconpropertyeditor.h>

QVariantPropertyDelegate::QVariantPropertyDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
{
	 factory = new QItemEditorFactory( *QItemEditorFactory::defaultFactory());
	 this->setItemEditorFactory(factory);

	 QItemEditorCreatorBase* color = new QStandardItemEditorCreator<QColorPropertyEditor>();
	 factory->registerEditor(QMetaType::QColor, color);

	 QItemEditorCreatorBase* font = new QStandardItemEditorCreator<QFontPropertyEditor>();
	 factory->registerEditor(QMetaType::QFont, font);

	 QItemEditorCreatorBase* doub = new QStandardItemEditorCreator<QDoublePropertyEditor>();
	 factory->registerEditor(QMetaType::Double, doub);

	 QItemEditorCreatorBase* flt = new QStandardItemEditorCreator<QDoublePropertyEditor>();
	 factory->registerEditor(QMetaType::Float, flt);

	 QItemEditorCreatorBase* pix = new QStandardItemEditorCreator<QPixmapPropertyEditor>();
	 factory->registerEditor(QMetaType::QPixmap, pix);

	 QItemEditorCreatorBase* bmp = new QStandardItemEditorCreator<QBitmapPropertyEditor>();
	 factory->registerEditor(QMetaType::QBitmap, bmp);

	 QItemEditorCreatorBase* keySeq = new QItemEditorCreator<QKeySequenceEdit>("keySequence");
	 factory->registerEditor(QMetaType::QKeySequence, keySeq);

	 QItemEditorCreatorBase* ico = new QStandardItemEditorCreator<QIconPropertyEditor>();
	 factory->registerEditor(QMetaType::QIcon, ico);

	 QItemEditorCreatorBase* fontfam = new QStandardItemEditorCreator<QFontFamilyPropertyEditor>();
	 registerCustomEditorCreator(QFontFamilyProperty::QualifiedVariantPropertyName,fontfam);

	 QItemEditorCreatorBase* enumf = new QStandardItemEditorCreator<QEnumPropertyEditor>();
	 registerCustomEditorCreator(QEnumVariantProperty::QualifiedVariantPropertyName,enumf);
}

QVariantPropertyDelegate::~QVariantPropertyDelegate()
{

}

QWidget *QVariantPropertyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QVariantProperty* property  = static_cast<QVariantProperty*>(index.internalPointer());
	
	if(property == nullptr || !property->getData().isValid())
		return nullptr;

	QItemEditorCreatorBase* editorBase = getRegisteredCustomEditorCreator(property->getQualifiedVariantPropertyName());
	QWidget* editor = nullptr;
	QString propName;

	if(editorBase != nullptr)
	{
		editor = editorBase->createWidget(parent);
		propName = "Value";

		//set properties for custom editors
		if(property->getQualifiedVariantPropertyName() == QEnumVariantProperty::QualifiedVariantPropertyName)
		{
			QEnumPropertyEditor* editorSpecial = static_cast<QEnumPropertyEditor*>(editor);
			QEnumVariantProperty* enumProperty =(QEnumVariantProperty*)property;

			if(editorSpecial != nullptr && enumProperty != nullptr)
			{
				QMetaEnum enumerator = enumProperty->getMetaEnum();
				editorSpecial->setupModel(enumProperty->getMetaEnum());
				editorSpecial->setValue(property->getData());
			}
		}

		
	}

	if(editor == nullptr)
	{
		editor = QStyledItemDelegate::createEditor(parent, option, index);
		propName = factory->valuePropertyName(property->getData().userType());
	}

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

void QVariantPropertyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	painter->setBrush(QBrush());
	painter->setPen(QPen());
	if(index.column() == 0)
	{
		QStyledItemDelegate::paint(painter, option, index);
		return;
	}

	QVariantProperty* property  = static_cast<QVariantProperty*>(index.internalPointer());
	QVariant value = property->getData();

	switch (value.type())
	{
	case QMetaType::Void:
	case QMetaType::Bool:
	case QMetaType::Int:
	case QMetaType::UInt:
	case QMetaType::LongLong:
	case QMetaType::ULongLong:
	case QMetaType::Double:
	case QMetaType::Long:
	case QMetaType::Short:
	case QMetaType::Char:
	case QMetaType::ULong:
	case QMetaType::UShort:
	case QMetaType::UChar:
	case QMetaType::Float:
	case QMetaType::SChar:
	case QMetaType::VoidStar:
	case QMetaType::QChar:
	case QMetaType::QString:
	case QMetaType::QStringList:
	case QMetaType::QByteArray:
	case QMetaType::QBitArray:
	case QMetaType::QDate:
	case QMetaType::QTime:
	case QMetaType::QDateTime:
	case QMetaType::QUrl:
	case QMetaType::QLocale:
	case QMetaType::QRect:
	case QMetaType::QRectF:
	case QMetaType::QSize:
	case QMetaType::QSizeF:
	case QMetaType::QLine:
	case QMetaType::QLineF:
	case QMetaType::QPoint:
	case QMetaType::QPointF:
	case QMetaType::QRegExp:
	case QMetaType::QEasingCurve:
	case QMetaType::QUuid:
	case QMetaType::QVariant:
	case QMetaType::QModelIndex:
	case QMetaType::QRegularExpression:
	case QMetaType::QJsonValue:
	case QMetaType::QJsonObject:
	case QMetaType::QJsonArray:
	case QMetaType::QJsonDocument:
	case QMetaType::QObjectStar:
	case QMetaType::QVariantMap:
	case QMetaType::QVariantList:
	case QMetaType::QVariantHash:
	case QMetaType::QFont:
	case QMetaType::QPixmap:
	case QMetaType::QPalette:
	case QMetaType::QIcon:
	case QMetaType::QImage:
	case QMetaType::QPolygon:
	case QMetaType::QRegion:
	case QMetaType::QBitmap:
	case QMetaType::QCursor:
	case QMetaType::QKeySequence:
	case QMetaType::QTextLength:
	case QMetaType::QTextFormat:
	case QMetaType::QMatrix:
	case QMetaType::QTransform:
	case QMetaType::QMatrix4x4:
	case QMetaType::QVector2D:
	case QMetaType::QVector3D:
	case QMetaType::QVector4D:
	case QMetaType::QQuaternion:
	case QMetaType::QPolygonF:
	case QMetaType::QSizePolicy:
	case QMetaType::UnknownType:
	case QMetaType::User:
		QStyledItemDelegate::paint(painter, option, index);
		break;
	case QMetaType::QPen:
		{
			QPen pen = qvariant_cast<QPen>(value);

			if(pen.widthF() > option.rect.height()-2)
			{
			    pen.setWidth(option.rect.height()-2);
			}
			
			painter->setPen(pen);

    		QRect test(option.rect.x() , option.rect.y()+1 , option.rect.width()-2, option.rect.height()-2);
			int yhalf  = test.y() + (test.height())*1.0/2.0;
			
			QPoint p1(test.x()+20,yhalf);
			QPoint p2(test.x()+ test.width()-20,yhalf);

			painter->drawLine(p1,p2);
			
			
		}
		break;
	case QMetaType::QBrush:
		{
			QBrush brush = qvariant_cast<QBrush>(value);
			QRect test(option.rect.x()+1 , option.rect.y()+1 , option.rect.width()-2, option.rect.height()-2);
			painter->setBrush(brush);
			painter->drawRect(test);
		}
		break;
	case QMetaType::QColor:
		{
		  QStyle* appstyle = QApplication::style();
		  QColor color = qvariant_cast<QColor>(value);
		  QStyleOption toption(option);
		  QBrush brush(color, Qt::BrushStyle::SolidPattern);
		  painter->setBrush(brush);

		  QRect test(toption.rect.x()+1 , toption.rect.y()+1 , 40 , toption.rect.height()-2);
		  painter->drawRect(test);

		  test.setRect(toption.rect.x() + 50 , toption.rect.y()+1,toption.rect.width() - 50, toption.rect.height()-2);
		  appstyle->drawItemText(painter,test,Qt::AlignmentFlag::AlignLeft,toption.palette, true,value.toString(),QPalette::ColorRole::Text);
		 
		}
		break;
	default:
		QStyledItemDelegate::paint(painter, option, index);
		break;
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

void QVariantPropertyDelegate::updateEditorGeometry ( QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
	editor->setGeometry(option.rect);
}