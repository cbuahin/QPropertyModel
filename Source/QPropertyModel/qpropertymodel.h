#ifndef QPROPERTYMODEL_H
#define QPROPERTYMODEL_H

#include <qpropertymodel_global.h>
#include <qabstractitemmodel.h>
#include <qpropertyitem.h>

class QPROPERTYMODEL_EXPORT QPropertyModel : public QAbstractItemModel
{

public:
	QPropertyModel(QObject* parent);

	QPropertyModel(QObject* item, QObject* parent);

	QPropertyModel(const QVariant& item, QObject* parent);

	~QPropertyModel();

	void setParentData(const QVariant& item);

	int	columnCount(const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;

	int rowCount(const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;

	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

	bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

	QModelIndex	index(int row, int column, const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;

	QModelIndex	parent(const QModelIndex & index) const Q_DECL_OVERRIDE;

	Qt::ItemFlags flags(const QModelIndex & index) const Q_DECL_OVERRIDE;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

	bool hasChildren(const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;

	void clear();

	QPropertyItem* rootPropertyItem() const;

	QVariant rootQVariantItem() const;

public slots:
	void onDataChanged(const QModelIndex & index);

private:
	void initializeParentRootItem();

private:
	QPropertyItem* m_rootPropertyItem;
	QVariant m_rootQVariantItem;
};

#endif // QPROPERTYMODEL_H
