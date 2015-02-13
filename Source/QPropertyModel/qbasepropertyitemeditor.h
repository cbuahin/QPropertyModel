#ifndef QBASEPROPERTYITEMEDITOR_H
#define QBASEPROPERTYITEMEDITOR_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QMetaProperty>
#include "qpropertyitem.h"

class QBasePropertyItemEditor : public QWidget
{
	Q_OBJECT;
	Q_PROPERTY(QVariant Value READ getValue WRITE setValue NOTIFY valueChanged USER true);

public:
	enum ItemType
	{
		Enum,
		Font,
		Unknown
	};

public:
	QBasePropertyItemEditor(QWidget *parent);

	QBasePropertyItemEditor(QWidget* const childEditor,  QPropertyItem* const propertyItem, QWidget *parent);

	virtual ~QBasePropertyItemEditor();

	void setPropertyItem(QPropertyItem* const propertyItem);

	virtual void setValue(const QVariant& value);

	virtual QVariant getValue() const;

protected:
	void focusOutEvent(QFocusEvent * event) Q_DECL_OVERRIDE;


private:
	virtual void setUpChildWidget();

private slots:
	void onRefresh();

signals:
	void valueChanged(QWidget* widget);

protected:
	QVariant m_value;
	QPropertyItem*  m_propertyItem;
	QPushButton* m_resetPushButton;
	QWidget* m_editorWidget;
	QMetaProperty m_valueProperty;
	ItemType m_itemType;
};

#endif // QBASEPROPERTYITEMEDITOR_H
