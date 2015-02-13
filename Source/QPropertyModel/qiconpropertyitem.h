#ifndef QICONPROPERTYITEM_H
#define QICONPROPERTYITEM_H

#include <QVariantPropertyItem.h>

class QIconPropertyItem : public QVariantPropertyItem
{
	Q_OBJECT

public:
	QIconPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);
	~QIconPropertyItem();

	QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const Q_DECL_OVERRIDE;

	bool hasChildren() Q_DECL_OVERRIDE;

protected:
	void setChildValues() Q_DECL_OVERRIDE;

private slots:
	void onChildItemValueChanged(const QString& name, const QVariant& value);

private:
	bool m_isSettingChildren;
};

#endif // QICONPROPERTYITEM_H
