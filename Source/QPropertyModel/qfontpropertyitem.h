#ifndef QFONTPROPERTYITEM_H
#define QFONTPROPERTYITEM_H

#include "qvariantpropertyitem.h"

class QFontPropertyItem : public QVariantPropertyItem
{
	Q_OBJECT

public:
	QFontPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);
	~QFontPropertyItem();

	QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const Q_DECL_OVERRIDE;

    bool hasChildren() Q_DECL_OVERRIDE;
	
protected: 
	void setChildValues() Q_DECL_OVERRIDE;

private slots:	
    void onChildItemValueChanged(const QString& name, const QVariant& value);

private:
	bool m_settingChildren;
};

#endif // QFONTPROPERTYITEM_H
