#include "stdafx.h"
#include "qbrushpropertyitem.h"
#include "qpropertymodel.h"
#include <QBrush>
#include "qchildenumpropertyitem.h"
#include "qchildimagepropertyitem.h"

QBrushPropertyItem::QBrushPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
	: QVariantPropertyItem(value, metaProperty, parent), m_isSettingChildren(false)
{

}

QBrushPropertyItem::~QBrushPropertyItem()
{

}


void QBrushPropertyItem::setChildValues()
{
	if (!m_isSettingChildren)
	{
		m_isSettingChildren = true;

		QBrush brush = qvariant_cast<QBrush>(m_metaProperty.read(m_parent->qObject()));

		for (int i = 0; i < m_children.count(); i++)
		{
			QPropertyItem* child = m_children[i];
			QString propertyName = child->name();
			QVariant tval;

			if (propertyName == "Color")
			{
				tval = brush.color();
			}
			else if (propertyName == "Brush Style")
			{
				tval = (int)brush.style();
			}
			else if (propertyName == "Texture")
			{
				tval = brush.texture();
			}

			m_model->setData(child->index(), tval);
		}


		m_isSettingChildren = false;
	}
}

bool QBrushPropertyItem::hasChildren()
{
	if (!m_childrenSet)
	{
		m_childrenSet = true;

		QBrush brush = qvariant_cast<QBrush>(m_metaProperty.read(m_parent->qObject()));

		QPropertyItem* width = new QPropertyItem(brush.color(), "Color", this);
		m_children.append(width);
		connect(width, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
			SLOT(onChildItemValueChanged(const QString&, const QVariant&)));

		
		int index = staticQtMetaObject.indexOfEnumerator("BrushStyle");
		QMetaEnum enumeration = staticQtMetaObject.enumerator(index);
		QChildEnumPropertyItem* brushStyle = new QChildEnumPropertyItem((int)brush.style(), "Brush Style",enumeration , this);
		m_children.append(brushStyle);
		connect(brushStyle, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
			SLOT(onChildItemValueChanged(const QString&, const QVariant&)));


		QChildImagePropertyItem* textureImage = new QChildImagePropertyItem(brush.texture(), "Texture", this);
		m_children.append(textureImage);
		connect(textureImage, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
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

Qt::ItemFlags QBrushPropertyItem::flags() const
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

void QBrushPropertyItem::onChildItemValueChanged(const QString& name, const QVariant& value)
{
	if (!m_isSettingChildren)
	{
		m_isSettingChildren = true;

		QBrush brush = qvariant_cast<QBrush>(m_metaProperty.read(m_parent->qObject()));

		if (name == "Color")
		{
			brush.setColor(qvariant_cast<QColor>(value));
		}
		else if (name == "Brush Style")
		{
			brush.setStyle((Qt::BrushStyle) value.toInt());
		}
		else if (name == "Texture")
		{
			brush.setTexture(qvariant_cast<QPixmap>(value));
		}

		m_model->setData(m_index, brush);

		m_isSettingChildren = false;

	}
}