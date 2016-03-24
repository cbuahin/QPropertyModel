#ifndef QVECTOR2DPROPERTYITEM_H
#define QVECTOR2DPROPERTYITEM_H

#include "qvariantpropertyitem.h"

class QVector2DPropertyItem : public QVariantPropertyItem
{
	Q_OBJECT

public:
	QVector2DPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

	virtual ~QVector2DPropertyItem();

	QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

	bool hasChildren() override;

	Qt::ItemFlags flags() const override;


protected:
	void setChildValues() override;

	private slots:
	void onChildItemValueChanged(const QString& name, const QVariant& value);

private:
	bool m_isSettingChildren;

};

#endif // QVECTOR2DPROPERTYITEM_H
