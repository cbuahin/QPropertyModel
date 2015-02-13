#ifndef QSIZEPROPERTYITEM_H
#define QSIZEPROPERTYITEM_H

#include "qvariantpropertyitem.h"

class QSizePropertyItem : public QVariantPropertyItem
{
	Q_OBJECT

public:
	QSizePropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);
	~QSizePropertyItem();

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

#endif // QSIZEPROPERTYITEM_H
