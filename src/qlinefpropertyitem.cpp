#include "stdafx.h"
#include "qlinefpropertyitem.h"
#include "qpropertymodel.h"
#include "qchildpropertyitems.h"

QLineFPropertyItem::QLineFPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
   : QVariantPropertyItem(value, metaProperty, parent), m_isSettingChildren(false)
{

}

QLineFPropertyItem::~QLineFPropertyItem()
{

}

QVariant QLineFPropertyItem::data(int column, Qt::ItemDataRole  role) const
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
                  QLineF v = qvariant_cast<QLineF>(m_metaProperty.read(m_parent->qObject()));
                  QString label = QString("P1=[X=%1, Y=%2], P2=[X=%3, Y=%4]").arg(v.p1().x()).arg(v.p1().y()).arg(v.p2().x()).arg(v.p2().y());
                  return label;
               }
               break;
         }

         break;
   }
   return QVariant();
}

void QLineFPropertyItem::setChildValues()
{
   if (!m_isSettingChildren)
   {
      m_isSettingChildren = true;

      QLineF line = qvariant_cast<QLineF>(m_metaProperty.read(m_parent->qObject()));

      for (int i = 0; i < m_children.count(); i++)
      {
         QPropertyItem* child = m_children[i];
         QString propertyName = child->name();
         QVariant tval;

         if (propertyName == "P1")
         {
            tval = line.p1();
         }
         else if (propertyName == "P2")
         {
            tval = line.p2();
         }


         m_model->setData(child->index(), tval);
      }


      m_isSettingChildren = false;
   }
}

bool QLineFPropertyItem::hasChildren()
{
   if (!m_childrenSet)
   {
      m_childrenSet = true;

      QLineF line = qvariant_cast<QLineF>(m_metaProperty.read(m_parent->qObject()));

      QChildPointFPropertyItem* p1 = new QChildPointFPropertyItem(qvariant_cast<QVariant>(line.p1()), "P1", this);
      m_children.append(p1);
      connect(p1, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
              SLOT(onChildItemValueChanged(const QString&, const QVariant&)));


      QChildPointFPropertyItem* p2 = new QChildPointFPropertyItem(qvariant_cast<QVariant>(line.p1()), "P2", this);
      m_children.append(p2);
      connect(p2, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
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

Qt::ItemFlags QLineFPropertyItem::flags() const
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

void QLineFPropertyItem::onChildItemValueChanged(const QString& name, const QVariant& value)
{
   if (!m_isSettingChildren)
   {
      m_isSettingChildren = true;

      QLineF line = qvariant_cast<QLineF>(m_metaProperty.read(m_parent->qObject()));

      if (name == "P1")
      {
         line.setP1(qvariant_cast<QPointF>(value));
      }
      else if (name == "P2")
      {
         line.setP2(qvariant_cast<QPointF>(value));
      }

      m_model->setData(m_index, line);

      m_isSettingChildren = false;

   }
}
