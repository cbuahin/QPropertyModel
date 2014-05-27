/****************************************************************************
**
**  Copyright (C) 2014 Caleb Amoa Buahin
**  Contact: calebgh@gmail.com
** 
**  This file is part of QPropertGrid.exe and QPropertGrid.dll
**
**  QPropertGrid.exe and QPropertGrid.dll and its associated files is free software; you can redistribute it and/or modify
**  it under the terms of the Lesser GNU General Public License as published by
**  the Free Software Foundation; either version 3 of the License, or
**  (at your option) any later version.
**
**  QPropertGrid.exe and QPropertGrid.dll and its associated files is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  Lesser GNU General Public License for more details.
**
**  You should have received a copy of the Lesser GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>
**
****************************************************************************/



#ifndef QVARIANTPROPERTY_H
#define QVARIANTPROPERTY_H

struct StaticQtMetaObject : public QObject
{
    static inline const QMetaObject& get() {return staticQtMetaObject;}
};

#include <QObject>

class QVariantProperty : public QObject
{
	Q_OBJECT

	//register common enums;

public:
	enum Column
	{
		PropertyNameColumn = 0,
		PropertyValueColumn = 1,
	};

	QVariantProperty(const QVariant& value, const QMetaProperty& metaProperty, QVariantProperty *parent = nullptr);
	virtual ~QVariantProperty();

	virtual bool setData(const QVariant & value,Qt::ItemDataRole role, Column column);
    virtual void setData(const QVariant& value);
	
	QVariant getData() const ;
	virtual QVariant getData(Qt::ItemDataRole role , Column column);


	virtual QObject* getObject() const ;
	QMetaProperty getMetaProperty() const;
	QAbstractItemModel* getModel() const;
	QModelIndex getModelIndex() const;

	virtual bool canReset();
	

	void setModel(QAbstractItemModel* const& model);
	void setModelIndex(const QModelIndex& modelIndex);

	const QList<QVariantProperty*>& childProperties() ;
	int getRowInParent() const;

    void setRowInParent(int row); 
	void setPropertyName(const QString& propName);
	QString getPropertyName() const;

	virtual bool hasChildren() ;

	int getRowCount() const;
    int getColumnCount() const;

	virtual Qt::ItemFlags flags() const;

	virtual void setDefaultFlags(Qt::ItemFlags flags);

	virtual QString getQualifiedVariantPropertyName() const;


protected:
	virtual void setupChildProperties();
	

public slots:
	//connect to refresh button
	virtual bool refreshDataSlot();

private slots:
	//updates unregistered child properties in parent. Parent responsible for calling appropriate set functions
	virtual void childPropertyValueChangedSlot(const QString& propertyName, const QVariant& value);
	//gets edits from external sources
	virtual void getDataFromParentSlot();


signals:
	//used to notify parent of unregistered manually created properties
	void valueChangedSignal();
	void valueChangedSignal(const QString& propertyName, const QVariant& value);
    

protected:
	QList<QVariantProperty*> children;
	QAbstractItemModel* model;
	QModelIndex modelIndex;
	QMetaProperty metaProperty;
	QString propertyName;
	QVariant value;
	int columnCount;
	int rowInParent;
    bool propertiesSet;
	bool canreset;
	bool editable;
	bool childPropertyCalledUpdate;
	QVariant resetValue;
	Qt::ItemFlags defaultFlags;

};

Q_DECLARE_METATYPE(QVariantProperty*);

#endif // QVARIANTPROPERTY_H
