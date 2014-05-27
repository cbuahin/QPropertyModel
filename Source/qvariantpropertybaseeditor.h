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


#ifndef QVARIANTPROPERTYBASEEDITOR_H
#define QVARIANTPROPERTYBASEEDITOR_H

#include <QWidget>
#include <qvariantproperty.h>

class QVariantPropertyBaseEditor : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QVariant Value READ  getValue WRITE setValue  NOTIFY valueChangedSignal  USER true);

public:
	QVariantPropertyBaseEditor(QWidget *parent, QWidget* const editorWidget, const QString& name, const QStyleOptionViewItem &option, const QModelIndex &index);
	~QVariantPropertyBaseEditor();

	void setValue(const QVariant& value);
	QVariant getValue() const;

protected:
	void focusInEvent(QFocusEvent * event);

private slots:
    void valueChangedSlot();
	void hideEvent(QHideEvent * event);

signals:
	void valueChangedSignal();

protected:
	QWidget* editorWidget;
	QMetaProperty editorMetaProperty;
	QString valuePropertyName;
	QVariantProperty* property;
	QPushButton* resetButton;
	QModelIndex index;
};

Q_DECLARE_METATYPE(QVariantPropertyBaseEditor*);
#endif // QVARIANTPROPERTYBASEEDITOR_H
