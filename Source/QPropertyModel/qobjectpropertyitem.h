#ifndef QOBJECTPROPERTYITEM_H
#define QOBJECTPROPERTYITEM_H

#include <QPropertyItem.h>
#include <QMetaProperty>

class QObjectPropertyItem : public QPropertyItem
{
	Q_OBJECT

public:
	QObjectPropertyItem(QObject* const value, const QMetaProperty& prop, QPropertyItem * parent);

	virtual ~QObjectPropertyItem();

	QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const Q_DECL_OVERRIDE;


	bool setData(const QVariant & value, Qt::ItemDataRole role = Qt::UserRole) Q_DECL_OVERRIDE;

	bool hasChildren() Q_DECL_OVERRIDE;

	QObject* qObject() const;

private:
	QObject* m_objectvalue;
	QMetaProperty m_property;
	bool m_hasMetaProperty ;

};

#endif // QOBJECTPROPERTYITEM_H
