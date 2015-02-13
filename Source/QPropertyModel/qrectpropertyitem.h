#ifndef QRECTPROPERTYITEM_H
#define QRECTPROPERTYITEM_H

#include "qvariantpropertyitem.h"

class QRectPropertyItem : public QVariantPropertyItem
{
	Q_OBJECT

public:
	QRectPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);
	~QRectPropertyItem();

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

#endif // QRECTPROPERTYITEM_H
