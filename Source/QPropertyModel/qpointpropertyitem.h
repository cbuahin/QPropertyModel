#ifndef QPOINTPROPERTYITEM_H
#define QPOINTPROPERTYITEM_H


#include "qvariantpropertyitem.h"

class QPointPropertyItem : public QVariantPropertyItem
{
	Q_OBJECT

public:
	QPointPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);
	~QPointPropertyItem();

	QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const Q_DECL_OVERRIDE;

	bool hasChildren() Q_DECL_OVERRIDE;

	Qt::ItemFlags flags() const Q_DECL_OVERRIDE;


protected:
	void setChildValues() Q_DECL_OVERRIDE;

	private slots:
	void onChildItemValueChanged(const QString& name, const QVariant& value);

private:
	bool m_isSettingChildren;

};
#endif // QPOINTPROPERTYITEM_H
