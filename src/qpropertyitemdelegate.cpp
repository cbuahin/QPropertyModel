/*!
 * \file qpropertyitemdelegate.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of QPropertyItemDelegate.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */


#include "qpropertyitemdelegate.h"
#include "qcustomeditors.h"
#include "qenumpropertyitem.h"
#include "qfontfamilypropertyitem.h"
#include "qchildpropertyitems.h"
#include "qcustomeditors.h"
#include <QPainter>
#include <QLineEdit>
#include <QKeySequenceEdit>
#include <QPen>
#include <QTextItem>
#include <QApplication>
#include <QStyle>
#include <QMetaEnum>
#include "qcustomeditors.h"

QPropertyItemDelegate::QPropertyItemDelegate(QObject *parent)
   : QStyledItemDelegate(parent)
{
   QItemEditorFactory* factory = new QItemEditorFactory(*QItemEditorFactory::defaultFactory());

   this->setItemEditorFactory(factory);

   factory->registerEditor(QMetaType::QColor, new QStandardItemEditorCreator<QColorPropertyItemEditor>());

   factory->registerEditor(QMetaType::QFont, new QStandardItemEditorCreator<QFontPropertyItemEditor>());

   factory->registerEditor(QMetaType::QPixmap, new QStandardItemEditorCreator<QImagePropertyItemEditor>());

   factory->registerEditor(QMetaType::QImage, new QStandardItemEditorCreator<QImagePropertyItemEditor>());

   factory->registerEditor(QMetaType::QBitmap, new QStandardItemEditorCreator<QImagePropertyItemEditor>());

   factory->registerEditor(QMetaType::QIcon, new QStandardItemEditorCreator<QImagePropertyItemEditor>());

   factory->registerEditor(QMetaType::QStringList, new QStandardItemEditorCreator<QStringListPropertyItemEditor>());

   factory->registerEditor(QMetaType::QVariantList, new QStandardItemEditorCreator<QVariantListPropertyItemEditor>());

   int type = qMetaTypeId<QList<QObject*>>();
   factory->registerEditor(type , new QStandardItemEditorCreator<QObjectListPropertyItemEditor>());

   factory->registerEditor(QMetaType::QKeySequence, new QItemEditorCreator<QKeySequenceEdit>("keySequence"));

   factory->registerEditor(QMetaType::QCursor, new QStandardItemEditorCreator<QCursorPropertyItemEditor>());

   factory->registerEditor(QMetaType::QPalette, new QStandardItemEditorCreator<QPalettePropertyItemEditor>());

   factory->registerEditor(QMetaType::QString, new QItemEditorCreator<QLineEdit>("text"));

   factory->registerEditor(QMetaType::Double, new QStandardItemEditorCreator<QCustomDoubleSpinBox>());

   factory->registerEditor(QMetaType::Float, new QStandardItemEditorCreator<QCustomDoubleSpinBox>());

   factory->registerEditor(QMetaType::Int, new QStandardItemEditorCreator<QCustomSpinBox>());

   factory->registerEditor(QMetaType::UInt, new QStandardItemEditorCreator<QCustomSpinBox>());

   factory->registerEditor(QMetaType::QDateTime, new QItemEditorCreator<QCustomDateTimeEdit>("dateTime"));

   factory->registerEditor(QMetaType::QDate, new QItemEditorCreator<QCustomDateEdit>("dateTime"));

   factory->registerEditor(QMetaType::QTime, new QItemEditorCreator<QCustomTimeEdit>("time"));

}

QPropertyItemDelegate::~QPropertyItemDelegate()
{

}

void QPropertyItemDelegate::registerCustomTypeEditorCreator(QMetaType::Type type, QItemEditorCreatorBase* creator)
{
   this->itemEditorFactory()->registerEditor(type, creator);
}


QWidget * QPropertyItemDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
   QPropertyItem * propertyItem = static_cast<QPropertyItem*>(index.internalPointer());

   if (propertyItem)
   {
      QBasePropertyItemEditor* editor = nullptr;

      if (qobject_cast<QFontFamilyPropertyItem*>(propertyItem) ||
          qobject_cast<QEnumPropertyItem*>(propertyItem) ||
          qobject_cast<QChildEnumPropertyItem*>(propertyItem)
          )
      {
         editor = new QSelectFromListPropertyItemEditor(parent);
         editor->setPropertyItem(propertyItem);
      }
      else
      {
         QWidget* childEditor = QStyledItemDelegate::createEditor(parent, option, index);
         editor = qobject_cast<QBasePropertyItemEditor*>(childEditor);

         if (editor)
         {
            editor->setPropertyItem(propertyItem);
         }
         else
         {
            editor = new QBasePropertyItemEditor(childEditor, propertyItem, parent);
         }
      }

      connect(editor, SIGNAL(valueChanged(QWidget*)), this, SLOT(onEditorValueChanged(QWidget*)));

      return editor;

   }

   return  QStyledItemDelegate::createEditor(parent, option, index);
}

void QPropertyItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
   QVariant value = index.data(Qt::EditRole);
   painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform );

   switch (value.typeId())
   {

      case QMetaType::QPen:
         {
            // Draw background first
            QStyledItemDelegate::paint(painter, option, index);

            QPen pen = qvariant_cast<QPen>(value);
            painter->save();
            painter->setPen(pen);
            int yhalf = option.rect.y() + option.rect.height() / 2;
            QPoint p1(option.rect.left() + 5, yhalf);
            QPoint p2(option.rect.right() - 45, yhalf);
            painter->drawLine(p1, p2);
            painter->restore();
         }
         break;

      case QMetaType::QBrush:
         {
            // Draw selection/background
            QStyleOptionViewItem opt = option;
            initStyleOption(&opt, index);
            opt.text.clear();
            QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &opt, painter);

            QBrush brush = qvariant_cast<QBrush>(value);
            painter->save();

            // Small swatch on the left, then text — like Qt Creator
            int swatchSize = option.rect.height() - 4;
            QRect swatchRect(option.rect.left() + 2, option.rect.top() + 2, swatchSize, swatchSize);
            painter->setBrush(brush);
            painter->setPen(QPen(Qt::gray, 1));
            painter->drawRect(swatchRect);

            // Draw brush style name text
            int textLeft = swatchRect.right() + 6;
            QRect textRect(textLeft, option.rect.top(), option.rect.right() - textLeft - 40, option.rect.height());
            QMetaEnum brushEnum = QMetaEnum::fromType<Qt::BrushStyle>();
            const char* styleName = brushEnum.valueToKey((int)brush.style());
            QString text = styleName ? QString(styleName) : QString("BrushStyle(%1)").arg((int)brush.style());
            painter->setPen(option.palette.color(QPalette::Text));
            painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);

            painter->restore();
         }
         break;

      case QMetaType::QColor:
         {
            // Draw selection/background
            QStyleOptionViewItem opt = option;
            initStyleOption(&opt, index);
            opt.text.clear();
            QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &opt, painter);

            QColor color = qvariant_cast<QColor>(value);
            painter->save();

            // Small color swatch on the left — like Qt Creator
            int swatchSize = option.rect.height() - 4;
            QRect swatchRect(option.rect.left() + 2, option.rect.top() + 2, swatchSize, swatchSize);

            // Checkerboard background for alpha
            painter->setBrush(Qt::white);
            painter->setPen(Qt::NoPen);
            painter->drawRect(swatchRect);
            if (color.alpha() < 255)
            {
               QColor gray(192, 192, 192);
               int half = swatchSize / 2;
               painter->fillRect(swatchRect.left(), swatchRect.top(), half, half, gray);
               painter->fillRect(swatchRect.left() + half, swatchRect.top() + half, half, half, gray);
            }

            painter->setBrush(QBrush(color, Qt::SolidPattern));
            painter->setPen(QPen(Qt::gray, 1));
            painter->drawRect(swatchRect);

            // Draw RGBA text — like Qt Creator's QtColorPropertyManager
            int textLeft = swatchRect.right() + 6;
            QRect textRect(textLeft, option.rect.top(), option.rect.right() - textLeft - 40, option.rect.height());
            QString text;
            if (color.alpha() == 255)
               text = QString("(%1, %2, %3)").arg(color.red()).arg(color.green()).arg(color.blue());
            else
               text = QString("(%1, %2, %3, %4)").arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());
            painter->setPen(option.palette.color(QPalette::Text));
            painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);

            painter->restore();
         }
         break;

      case QMetaType::QIcon:
         {
            // Draw selection/background
            QStyleOptionViewItem opt = option;
            initStyleOption(&opt, index);
            opt.text.clear();
            opt.icon = QIcon();
            QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &opt, painter);

            QIcon icon = qvariant_cast<QIcon>(value);
            if (!icon.isNull())
            {
               int iconSize = option.rect.height() - 4;
               QRect iconRect(option.rect.left() + 2, option.rect.top() + 2, iconSize, iconSize);
               icon.paint(painter, iconRect, Qt::AlignCenter, QIcon::Normal, QIcon::On);
            }
         }
         break;

      case QMetaType::QPixmap:
         {
            QStyleOptionViewItem opt = option;
            initStyleOption(&opt, index);
            opt.text.clear();
            QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &opt, painter);

            QPixmap pixmap = qvariant_cast<QPixmap>(value);
            if (!pixmap.isNull())
            {
               int thumbSize = option.rect.height() - 4;
               QRect thumbRect(option.rect.left() + 2, option.rect.top() + 2, thumbSize, thumbSize);
               QPixmap scaled = pixmap.scaled(thumbSize, thumbSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
               painter->drawPixmap(thumbRect.topLeft(), scaled);
            }
         }
         break;

      case QMetaType::QImage:
         {
            QStyleOptionViewItem opt = option;
            initStyleOption(&opt, index);
            opt.text.clear();
            QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &opt, painter);

            QImage image = qvariant_cast<QImage>(value);
            if (!image.isNull())
            {
               int thumbSize = option.rect.height() - 4;
               QRect thumbRect(option.rect.left() + 2, option.rect.top() + 2, thumbSize, thumbSize);
               QImage scaled = image.scaled(thumbSize, thumbSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
               painter->drawImage(thumbRect.topLeft(), scaled);
            }
         }
         break;

      default:
         {
            QStyledItemDelegate::paint(painter, option, index);
         }
         break;
   }
}

void QPropertyItemDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
   QStyledItemDelegate::setEditorData(editor, index);
}

void QPropertyItemDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
{
   QStyledItemDelegate::setModelData(editor, model, index);
}

QSize QPropertyItemDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
   QVariant value = index.data(Qt::EditRole);

   switch (value.typeId())
   {
      case QMetaType::QFont:
         {
            QFont font = qvariant_cast<QFont>(value);
            QSize s = QStyledItemDelegate::sizeHint(option, index);

            if (font.pixelSize() + 4 > s.height())
            {
               s.setHeight(font.pixelSize() + 4);
            }

            return s;
         }
      case QMetaType::QPen:
         {
            QPen p = qvariant_cast<QPen>(value);
            QSize s = QStyledItemDelegate::sizeHint(option, index);

            if (p.widthF() + 4 > s.height())
            {
               s.setHeight(p.widthF() + 4);
            }

            return s;
         }
         break;
      default:
         {
            QSize s = QStyledItemDelegate::sizeHint(option, index);
            s.setHeight(s.height() + 4);
            return s;
         }
   }
}

void QPropertyItemDelegate::updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
   QStyledItemDelegate::updateEditorGeometry(editor, option, index);
}

void QPropertyItemDelegate::onEditorValueChanged(QWidget * editor)
{
   emit commitData(editor);
}
