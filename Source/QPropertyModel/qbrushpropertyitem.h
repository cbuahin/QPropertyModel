#ifndef QBRUSHPROPERTYITEM_H
#define QBRUSHPROPERTYITEM_H

#include "qvariantpropertyItem.h"

class QBrushPropertyItem : public QVariantPropertyItem
{
	Q_OBJECT

public:
	QBrushPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);
	~QBrushPropertyItem();


	bool hasChildren() Q_DECL_OVERRIDE;

	Qt::ItemFlags flags() const Q_DECL_OVERRIDE;


protected:
	void setChildValues() Q_DECL_OVERRIDE;

	private slots:
	void onChildItemValueChanged(const QString& name, const QVariant& value);

private:
	bool m_isSettingChildren;
	
};

#endif // QBRUSHPROPERTYITEM_H
