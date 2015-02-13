#ifndef QOBJECTCLASSPROPERTYITEM_H
#define QOBJECTCLASSPROPERTYITEM_H

#include <qpropertyitem.h>
#include <QMetaObject>

class QObjectClassPropertyItem : public QPropertyItem
{
	Q_OBJECT

public:
	QObjectClassPropertyItem(QObject* const value, const QMetaObject* metaObject, QPropertyItem * parent);
	
	virtual ~QObjectClassPropertyItem();

	QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const Q_DECL_OVERRIDE;

	bool setData(const QVariant & value, Qt::ItemDataRole role = Qt::UserRole) Q_DECL_OVERRIDE;

	bool hasChildren() Q_DECL_OVERRIDE;

	QObject* qObject() const;

private:
	const QMetaObject* m_metaObject;
	QObject* m_objectvalue; 
	static QColor s_backgroundColor;
	static QColor s_foregroundColor;
};

#endif // QOBJECTCLASSPROPERTYITEM_H
