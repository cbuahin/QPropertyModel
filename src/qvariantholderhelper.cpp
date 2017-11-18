#include "stdafx.h"
#include "qvariantholderhelper.h"

QVariantHolderHelper::QVariantHolderHelper(const QVariant& value, QObject* parent)
   :QObject(parent), m_value(value)
{

}

QVariantHolderHelper::~QVariantHolderHelper()
{

}

QVariant QVariantHolderHelper::value() const
{
   return m_value;
}

void QVariantHolderHelper::setValue(const QVariant& value)
{
   m_value = value;
   emit valueChanged();
}

QModelIndex QVariantHolderHelper::modelIndex() const
{
   return m_index;
}

void QVariantHolderHelper::setModelIndex(const QModelIndex& index)
{
   m_index = index;
}

QString QVariantHolderHelper::objectName() const
{
   return QObject::objectName();
}




