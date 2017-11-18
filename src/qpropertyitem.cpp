#include "stdafx.h"
#include "qpropertyitem.h"
#include "qpropertymodel.h"

QPropertyItem::QPropertyItem(const QVariant& value, const QString& name, QPropertyItem *parent)
   : QObject(parent),
     m_isSelectable(true),
     m_isEnabled(true),
     m_isEditable(true),
     m_isCheckable(false),
     m_isTristate(false),
     m_childrenSet(false)
{
   m_value = value;
   m_resetValue = QVariant::fromValue(value);
   m_name = name;
   m_parent = parent;

   if (parent)
   {

      m_model = parent->model();
   }
}

QPropertyItem::~QPropertyItem()
{
   qDeleteAll(m_children);
   m_children.clear();
}

QPropertyModel* QPropertyItem::model() const
{
   return m_model;
}

QPropertyItem* QPropertyItem::parent() const
{
   return m_parent;
}

QString QPropertyItem::name() const
{
   return m_name;
}

QModelIndex QPropertyItem::index() const
{
   return m_index;
}

int QPropertyItem::rowCount() const
{
   return m_children.count();
}

QVariant QPropertyItem::data() const
{
   return m_value;
}

QVariant QPropertyItem::data(int column, Qt::ItemDataRole  role) const
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
            case Qt::EditRole:
            case Qt::ToolTipRole:
            case Qt::StatusTipRole:
            case Qt::WhatsThisRole:
               return m_value;
               break;
         }

         break;
   }
   return QVariant();
}

bool QPropertyItem::setData(const QVariant & value, Qt::ItemDataRole role)
{
   switch (role)
   {
      case Qt::EditRole:
         {
            m_value = value;

            setChildValues();

            emit valueChanged(m_name, m_value);

            return true;
         }
         break;
   }

   return false;
}

bool QPropertyItem::hasChildren()
{
   return false;
}

Qt::ItemFlags QPropertyItem::flags() const
{
   Qt::ItemFlags  flags;

   if (m_isCheckable)
      flags = flags | Qt::ItemFlag::ItemIsUserCheckable;
   if (m_isEnabled)
      flags = flags | Qt::ItemFlag::ItemIsEnabled;
   if (m_isEditable)
      flags = flags | Qt::ItemFlag::ItemIsEditable;
   if (m_isEnabled)
      flags = flags | Qt::ItemFlag::ItemIsEnabled;
   if (m_isSelectable)
      flags = flags | Qt::ItemFlag::ItemIsSelectable;
   if (m_isTristate)
      flags = flags | Qt::ItemFlag::ItemIsTristate;

   return flags;
}

void QPropertyItem::setFlags(Qt::ItemFlags flags)
{
   m_isCheckable = flags.testFlag(Qt::ItemFlag::ItemIsUserCheckable);
   m_isEnabled = flags.testFlag(Qt::ItemFlag::ItemIsEnabled);
   m_isEditable = flags.testFlag(Qt::ItemFlag::ItemIsEditable);
   m_isEnabled = flags.testFlag(Qt::ItemFlag::ItemIsEnabled);
   m_isSelectable = flags.testFlag(Qt::ItemFlag::ItemIsSelectable);
   m_isTristate = flags.testFlag(Qt::ItemFlag::ItemIsTristate);
}

bool QPropertyItem::isCheckable() const
{
   return m_isCheckable;
}

void QPropertyItem::setCheckable(bool checkable)
{
   m_isCheckable = checkable;
}

bool QPropertyItem::isEditable() const
{
   return m_isEditable;
}

void QPropertyItem::setEditable(bool editable)
{
   m_isEditable = editable;
}

bool QPropertyItem::isEnabled() const
{
   return m_isEnabled;
}

void QPropertyItem::setEnabled(bool enabled)
{
   m_isEnabled = enabled;
}

bool QPropertyItem::isSelectable() const
{
   return m_isSelectable;
}

void QPropertyItem::setSelectable(bool selectable)
{
   m_isSelectable = selectable;
}

bool QPropertyItem::isTristate() const
{
   return m_isTristate;
}

void QPropertyItem::setTriState(bool tristate)
{
   m_isTristate = tristate;
}

QMetaType::Type	QPropertyItem::type() const
{
   int mtype = m_value.userType();
   return (QMetaType::Type) mtype;
}

QList<QPropertyItem*> QPropertyItem::childPropertyItems() const
{
   return m_children;
}

QPropertyItem* QPropertyItem::childPropertyItem(int index) const
{
   return m_children[index];
}

bool QPropertyItem::canReset() const
{
   return m_canReset;
}

void QPropertyItem::resetData()
{
   if (m_canReset)
      this->m_model->setData(m_index, m_resetValue);
}

void QPropertyItem::setChildValues()
{

}
