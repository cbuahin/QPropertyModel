/*!
 * \author Caleb Amoa Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * \license
 * This file and its associated files, and libraries are free software.
 * You can redistribute it and/or modify it under the terms of the
 * Lesser GNU Lesser General Public License as published by the Free Software Foundation;
 * either version 3 of the License, or (at your option) any later version.
 * This file and its associated files is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.(see <http://www.gnu.org/licenses/> for details)
 * \copyright Copyright 2014-2018, Caleb Buahin, All rights reserved.
 * \date 2014-2018
 * \pre
 * \bug
 * \warning
 * \todo
 */

#include "stdafx.h"
#include <QDebug>
#include "qflagspropertyitem.h"
#include "qchildpropertyitems.h"
#include "qpropertymodel.h"

QFlagsPropertyItem::QFlagsPropertyItem(const QVariant& value, const QMetaEnum& metaEnumProperty, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
	: QVariantPropertyItem(value, metaProperty, parent), m_isSettingChildren(false)
{
	m_metaEnum = metaEnumProperty;
	m_isEditable = false;
}

QFlagsPropertyItem::~QFlagsPropertyItem()
{

}

QVariant QFlagsPropertyItem::data(int column , Qt::ItemDataRole  role ) const
{
	switch (column)
	{
	case QPropertyItem::Property:
		switch (role)
		{
		case Qt::DisplayRole:
			return m_name;
			break;
		}

		break;
	case QPropertyItem::Value:
		switch (role)
		{
		case Qt::DisplayRole:
		case Qt::ToolTipRole:
		case Qt::StatusTipRole:
		case Qt::WhatsThisRole:
		{
			QVariant v = m_metaProperty.read(m_parent->qObject());
			QString name = m_metaEnum.valueToKeys(v.toInt());
			return name;
		}
		break;
		case Qt::EditRole:
		{
			return QVariant();
			return m_metaProperty.read(m_parent->qObject());
		}
			break;
		}

		break;
	}
	return QVariant();
}


void QFlagsPropertyItem::setChildValues()
{
	if (!m_isSettingChildren)
	{
		m_isSettingChildren = true;

		for (int i = 0; i < m_metaEnum.keyCount(); i++)
		{
			int flagVal = m_metaEnum.value(i);
			bool set = (m_value.toInt() & flagVal) == flagVal && (flagVal != 0 || m_value.toInt() == flagVal);
			m_model->setData(m_children[i]->index(), set);
		}

		m_isSettingChildren = false;
	}
}

bool QFlagsPropertyItem::hasChildren()
{
	if (!m_childrenSet)
	{
		m_childrenSet = true;

		m_value = m_metaProperty.read(m_parent->qObject());

		if (m_value.isValid())
		{
			for (int i = 0; i < m_metaEnum.keyCount(); i++)
			{
				QString name = m_metaEnum.key(i);
				int flagVal = m_metaEnum.value(i);

				bool set = (m_value.toInt() & flagVal) == flagVal && (flagVal != 0 || m_value.toInt() == flagVal);
				QChildBoolPropertyItem* childItem = new QChildBoolPropertyItem(set, name, this);
				m_children.append(childItem);
				connect(childItem, SIGNAL(valueChanged(const QString&, const QVariant&)), this, SLOT(onChildItemValueChanged(const QString&, const QVariant&)));

			}

			return true;
		}
	}
	else
	{
		if (m_children.count() > 0)
		{
			return true;
		}
	}

	return false;
}

Qt::ItemFlags QFlagsPropertyItem::flags() const
{
	Qt::ItemFlags  flags;

	if (m_isCheckable)
		flags = flags | Qt::ItemFlag::ItemIsUserCheckable;
	if (m_isEnabled)
		flags = flags | Qt::ItemFlag::ItemIsEnabled;
	//if (m_isEditable)
	//	flags = flags | Qt::ItemFlag::ItemIsEditable;
	if (m_isEnabled)
		flags = flags | Qt::ItemFlag::ItemIsEnabled;
	if (m_isSelectable)
		flags = flags | Qt::ItemFlag::ItemIsSelectable;
	if (m_isTristate)
		flags = flags | Qt::ItemFlag::ItemIsTristate;

	return flags;
}


QMetaEnum QFlagsPropertyItem::enumerator() const
{
	return m_metaEnum;
}

void QFlagsPropertyItem::onChildItemValueChanged(const QString& name, const QVariant& value)
{
	if (!m_isSettingChildren)
	{
		m_isSettingChildren = true;

		m_value = m_metaProperty.read(m_parent->qObject());

		int tvalue = 0;

		for (int i = 0; i < m_children.count(); i++)
		{
			QString name = m_metaEnum.key(i);
			int flagVal = m_metaEnum.value(i);
			QVariant v = m_children[i]->data(1, Qt::CheckStateRole);


			if (v.toBool())
			{
				bool set = (tvalue & flagVal) == flagVal && (flagVal != 0 || tvalue == flagVal);

				if (!set)
				{
					QString tempName = m_children[i]->name();
					int valtoapp = m_metaEnum.keyToValue(tempName.toStdString().c_str());
					tvalue = tvalue | valtoapp;
				}
			}
		}

		m_model->setData(m_index, tvalue , Qt::EditRole);

		m_isSettingChildren = false;

	}
}
