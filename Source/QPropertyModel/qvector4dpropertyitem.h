#ifndef QVECTOR4DPROPERTYITEM_H
#define QVECTOR4DPROPERTYITEM_H

#include "qvariantpropertyitem.h"

class QVector4DPropertyItem : public QVariantPropertyItem
{
	Q_OBJECT

public:
	QVector4DPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);
	~QVector4DPropertyItem();

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
#endif // QVECTOR4DPROPERTYITEM_H
