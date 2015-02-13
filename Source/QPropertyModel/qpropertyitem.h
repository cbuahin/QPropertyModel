#ifndef QPROPERTYITEM_H
#define QPROPERTYITEM_H

#include <QObject>
#include <QModelIndex>
#include <QBrush>
#include <QFont>
#include <QIcon>

class QPropertyModel;

class QPropertyItem : public QObject
{
	friend class QPropertyModel;

	Q_OBJECT;
	Q_PROPERTY(QPropertyModel* Model READ  model);
	Q_PROPERTY(QPropertyItem* Parent READ  parent);
	Q_PROPERTY(QString Name READ  name);
	Q_PROPERTY(QModelIndex Index READ  index);
	Q_PROPERTY(int RowCount READ  rowCount);
	Q_PROPERTY(bool HasChildren READ  hasChildren);
	Q_PROPERTY(Qt::ItemFlags Flags READ  flags);
	Q_PROPERTY(bool IsCheckable READ  isCheckable);
	Q_PROPERTY(bool IsEditable READ  isEditable);
	Q_PROPERTY(bool IsEnabled READ  isEnabled);
	Q_PROPERTY(bool IsSelectable READ  isSelectable);
	Q_PROPERTY(bool IsTristate READ  isTristate);
	Q_PROPERTY(QMetaType::Type Type READ  type);
	Q_PROPERTY(QList<QPropertyItem*> ChildPropertyItems READ  childPropertyItems);


public:

	enum ColumnType
	{
		Property,
		Value,
	};

	QPropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent);

	virtual ~QPropertyItem();

	QPropertyModel* model() const;

	QPropertyItem* parent() const;

	QString name() const;

	QModelIndex index() const;

	virtual QVariant data(int column = 1 , Qt::ItemDataRole  role = Qt::UserRole) const;

	QVariant data() const;

	virtual bool setData(const QVariant & value, Qt::ItemDataRole role = Qt::UserRole);

	int rowCount() const;

	virtual bool hasChildren();

	virtual Qt::ItemFlags flags() const;

	void setFlags(Qt::ItemFlags flags);

	bool isCheckable() const;

	bool isEditable() const;

	bool isEnabled() const;

	bool isSelectable() const;

	bool isTristate() const;

	QMetaType::Type type() const;

	QList<QPropertyItem*> childPropertyItems() const;

	QPropertyItem* childPropertyItem(int index) const ;

	bool canReset() const;

	virtual void resetData();

signals:
	void valueChanged(const QString& propertyName, const QVariant& value);

protected:
	virtual void setChildValues();

protected:
	void setCheckable(bool checkable);
	void setEditable(bool editable);
	void setEnabled(bool enabled);
	void setSelectable(bool selectable);
	void setTriState(bool tristate);
	
protected:
	QList<QPropertyItem*> m_children;
	QPropertyModel* m_model;
	QPropertyItem* m_parent;
	QModelIndex m_index;
	QVariant m_value;
	QVariant m_resetValue;
	QString m_name;
	bool m_isCheckable, m_isEditable, m_isEnabled, m_isSelectable, m_isTristate, m_childrenSet, m_canReset;
};

Q_DECLARE_METATYPE(QPropertyItem*);

#endif // QPROPERTYITEM_H
