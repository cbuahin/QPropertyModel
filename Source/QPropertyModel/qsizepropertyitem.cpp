#include "stdafx.h"
#include "qsizepropertyitem.h"
#include "qpropertymodel.h"

QSizePropertyItem::QSizePropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
	: QVariantPropertyItem(value, metaProperty, parent), m_isSettingChildren(false)
{

}

QSizePropertyItem::~QSizePropertyItem()
{

}

QVariant QSizePropertyItem::data(int column, Qt::ItemDataRole  role) const
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
		case Qt::EditRole:
		{
			return  m_metaProperty.read(m_parent->qObject());
			
		}break;
		case Qt::DisplayRole:
		case Qt::ToolTipRole:
		case Qt::StatusTipRole:
		case Qt::WhatsThisRole:
		{
			QSize size = qvariant_cast<QSize>( m_metaProperty.read(m_parent->qObject()));
			QString dis = QString::number(size.width()) + " X " + QString::number(size.height());
			return dis;
		}
			break;
		}

		break;
	}
	return QVariant();
}


void QSizePropertyItem::setChildValues()
{
	if (!m_isSettingChildren)
	{
		m_isSettingChildren = true;

		QSize size = qvariant_cast<QSize>( m_metaProperty.read(m_parent->qObject()));
		
		for (int i = 0; i < m_children.count(); i++)
		{
			QPropertyItem* child = m_children[i];
			QString propertyName = child->name();
			QVariant tval;

			if (propertyName == "Width")
			{
				tval = size.width();
			}
			else if (propertyName == "Height")
			{
				tval = size.height();
			}

			m_model->setData(child->index(), tval);
		}


		m_isSettingChildren = false;
	}
}

bool QSizePropertyItem::hasChildren()
{
	if (!m_childrenSet)
	{
		m_childrenSet = true;

		QSize size = qvariant_cast<QSize>( m_metaProperty.read(m_parent->qObject()));
		
		QPropertyItem* width = new QPropertyItem(size.height(), "Width", this);
		m_children.append(width);
		connect(width, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
			SLOT(onChildItemValueChanged(const QString&, const QVariant&)));

		QPropertyItem* height = new QPropertyItem(size.height(), "Height", this);
		m_children.append(height);

		connect(height, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
			SLOT(onChildItemValueChanged(const QString&, const QVariant&)));
			
		return true;
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

Qt::ItemFlags QSizePropertyItem::flags() const
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

void QSizePropertyItem::onChildItemValueChanged(const QString& name, const QVariant& value)
{
	if (!m_isSettingChildren)
	{
		m_isSettingChildren = true;

		QSize size = qvariant_cast<QSize>(m_metaProperty.read(m_parent->qObject()));

		if (name == "Width")
		{
			size.setWidth(value.toInt());
		}
		else if (name == "Height")
		{
			size.setHeight(value.toInt());
		}

		m_model->setData(m_index, size);

		m_isSettingChildren = false;

	}
}