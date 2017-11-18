#include "stdafx.h"
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

   factory->registerEditor(QMetaType::QString, new QItemEditorCreator<QLineEdit>("text"));

   factory->registerEditor(QMetaType::Double, new QStandardItemEditorCreator<QCustomDoubleSpinBox>());

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
   painter->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform );

   switch (value.type())
   {

      case QMetaType::QPen:
         {
            QPen pen = qvariant_cast<QPen>(value);
            painter->setPen(pen);
            int yhalf = option.rect.y() + (option.rect.height())*1.0 / 2.0;
            yhalf = yhalf + pen.widthF() / 2;
            QPoint p1(option.rect.left() + 5, yhalf);
            QPoint p2(option.rect.right() - 45 , yhalf);
            painter->drawLine(p1, p2);
         }
         break;

      case QMetaType::QBrush:
         {
            QBrush brush = qvariant_cast<QBrush>(value);
            painter->setBrush(brush);
            painter->setPen(QPen());

            QRect rect = QRect(option.rect);
            rect.setRight(rect.right() - 50);
            rect.setLeft(rect.left() + 5);
            rect.setTop(rect.top() + 2);
            rect.setBottom(rect.bottom() - 2);
            qreal rad = (rect.height()-4)*1.0 / 2.5;

            painter->drawRoundedRect(rect, rad, rad);
         }
         break;

      case QMetaType::QColor:
         {
            QColor color = qvariant_cast<QColor>(value);
            QBrush brush(color, Qt::BrushStyle::SolidPattern);
            painter->setBrush(brush);
            painter->setPen(QPen());
            QRect rect = QRect(option.rect);
            rect.setRight(rect.right() - 45);
            rect.setLeft(rect.left() + 5);
            rect.setTop(rect.top() + 2);
            rect.setBottom(rect.bottom() - 2);
            qreal rad = (rect.height()-4)*1.0 / 2.5;
            painter->drawRoundedRect(rect, rad, rad);
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

   switch (value.type())
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
