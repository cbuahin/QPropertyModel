#ifndef QFLAGSPROPERTYITEM_H
#define QFLAGSPROPERTYITEM_H

#include "qvariantpropertyitem.h"

class QFlagsPropertyItem : public QVariantPropertyItem
{
	Q_OBJECT

public:
	QFlagsPropertyItem(const QVariant& value, const QMetaEnum& metaEnumProperty, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);
	~QFlagsPropertyItem();

	QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const Q_DECL_OVERRIDE;

	//bool setData(const QVariant & value, Qt::ItemDataRole role = Qt::UserRole) Q_DECL_OVERRIDE;

	bool hasChildren() Q_DECL_OVERRIDE;

	Qt::ItemFlags flags() const Q_DECL_OVERRIDE;


	QMetaEnum QFlagsPropertyItem::enumerator() const;
	
protected:
	void setChildValues() Q_DECL_OVERRIDE;

private slots:
void onChildItemValueChanged(const QString& name, const QVariant& value);

private:
	QMetaEnum m_metaEnum;
	bool m_isSettingChildren;
};

#endif // QFLAGSPROPERTYITEM_H
