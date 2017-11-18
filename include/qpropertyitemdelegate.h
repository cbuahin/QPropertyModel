#ifndef QPROPERTYITEMDELEGATE_H
#define QPROPERTYITEMDELEGATE_H

#include "qpropertymodel_global.h"
#include <QStyledItemDelegate>
#include <QItemEditorFactory>

class QPROPERTYMODEL_EXPORT QPropertyItemDelegate : public QStyledItemDelegate
{
      Q_OBJECT

   public:
      QPropertyItemDelegate(QObject *parent);

      ~QPropertyItemDelegate();

      void registerCustomTypeEditorCreator(QMetaType::Type type, QItemEditorCreatorBase* creator);

      QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const override;

      void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const override;

      void setEditorData(QWidget * editor, const QModelIndex & index) const override;

      void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const override;

      QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const override;

      void updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const override;

   private slots:

      void onEditorValueChanged(QWidget* widget);

};

#endif // QPROPERTYITEMDELEGATE_H
