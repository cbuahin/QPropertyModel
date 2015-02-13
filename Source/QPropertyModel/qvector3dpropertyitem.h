#ifndef QVECTOR3DPROPERTYITEM_H
#define QVECTOR3DPROPERTYITEM_H


#include "qvariantpropertyitem.h"

class QVector3DPropertyItem : public QVariantPropertyItem
{
	Q_OBJECT

public:
	QVector3DPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);
	~QVector3DPropertyItem();

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

#endif // QVECTOR3DPROPERTYITEM_H
