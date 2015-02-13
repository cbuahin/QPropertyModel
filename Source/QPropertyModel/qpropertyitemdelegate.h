#ifndef QPROPERTYITEMDELEGATE_H
#define QPROPERTYITEMDELEGATE_H

#include <qpropertymodel_global.h>
#include <QStyledItemDelegate>
#include <QItemEditorFactory>

class QPROPERTYMODEL_EXPORT QPropertyItemDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	QPropertyItemDelegate(QObject *parent);
	~QPropertyItemDelegate();

	QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const Q_DECL_OVERRIDE;
	void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const Q_DECL_OVERRIDE;
	void setEditorData(QWidget * editor, const QModelIndex & index) const Q_DECL_OVERRIDE;
	void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const Q_DECL_OVERRIDE;
	QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const Q_DECL_OVERRIDE;
	void updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const Q_DECL_OVERRIDE;

private slots:
	void onEditorValueChanged(QWidget* widget);

};

#endif // QPROPERTYITEMDELEGATE_H
