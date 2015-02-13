#ifndef QCHILDPOINTPROPERTYITEM_H
#define QCHILDPOINTPROPERTYITEM_H


#include "qpropertyitem.h"

class QChildPointPropertyItem : public QPropertyItem
{
	Q_OBJECT

public:
	QChildPointPropertyItem(const QVariant& value, const QString& name, QPropertyItem *parent);
	~QChildPointPropertyItem();

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

#endif // QCHILDPOINTPROPERTYITEM_H
