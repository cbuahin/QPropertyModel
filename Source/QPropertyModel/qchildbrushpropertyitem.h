#ifndef QCHILDBRUSHPROPERTYITEM_H
#define QCHILDBRUSHPROPERTYITEM_H

#include "qpropertyitem.h"

class QChildBrushPropertyItem : public QPropertyItem
{
	Q_OBJECT

public:
	QChildBrushPropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent);
	~QChildBrushPropertyItem();


	bool hasChildren() Q_DECL_OVERRIDE;

	Qt::ItemFlags flags() const Q_DECL_OVERRIDE;


protected:
	void setChildValues() Q_DECL_OVERRIDE;

	private slots:
	void onChildItemValueChanged(const QString& name, const QVariant& value);

private:
	bool m_isSettingChildren;
	
};

#endif // QCHILDBRUSHPROPERTYITEM_H
