#ifndef QPENPROPERTYITEM_H
#define QPENPROPERTYITEM_H

#include "qvariantpropertyItem.h"

class QPenPropertyItem : public QVariantPropertyItem
{
	Q_OBJECT

public:
	QPenPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);
	~QPenPropertyItem();

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

#endif // QPENPROPERTYITEM_H
