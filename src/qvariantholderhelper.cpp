/*!
 * \file qvariantholderhelper.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of QVariantHolderHelper.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */


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




