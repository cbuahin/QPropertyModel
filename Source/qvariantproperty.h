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

#include <qtpropertymodel.h>

class QVariantProperty : public QObject
{
	

	Q_OBJECT
	friend class QtPropertyModel;

	//register common enums;
public:
	enum Column
	{
		PropertyNameColumn = 0,
		PropertyValueColumn = 1,
	};
	
	QVariantProperty(const QVariant& invalue, const QMetaProperty& metaProperty, QtPropertyModel* const &  model, int row = 0, QVariantProperty *parent = nullptr);
	
	virtual ~QVariantProperty();

	virtual bool setData(const QVariant & value,Qt::ItemDataRole role = Qt::ItemDataRole::EditRole, Column column = Column::PropertyValueColumn);
	
	QVariant getData() const ;
	
	virtual QVariant getData(Qt::ItemDataRole role , Column column);

	virtual QObject* getObject() const ;

	QMetaProperty getMetaProperty() const;

	QtPropertyModel* getModel() const;

	QModelIndex getModelIndex() const;

	virtual bool canReset();

	void setModelIndex(const QModelIndex& index);

	void setPropertyName(const QString& propName);

	QString getPropertyName() const;

	virtual bool hasChildren() ;

	virtual int getRowCount();
	
	const QList<QVariantProperty*>& childProperties() ;
	
	int getRowInParent() const;

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
	void valueChangedSignal(const QString& propertyName, const QVariant& value);
    
protected:
	QVariantProperty* parentProperty;
    QtPropertyModel* model;
	QList<QVariantProperty*> children;
	QModelIndex modelIndex;
	QMetaProperty metaProperty;
	QString propertyName;
	QVariant value;
	int columnCount;
	int rowInParent;
	bool canreset;
	bool editable;
	int rowCount;
	QVariant resetValue;
	Qt::ItemFlags defaultFlags;
	bool childPropertiesSet;
};

Q_DECLARE_METATYPE(QVariantProperty*);

#endif // QVARIANTPROPERTY_H
