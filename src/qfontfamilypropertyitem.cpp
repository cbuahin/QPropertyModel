/*!
 * \file qfontfamilypropertyitem.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of QFontFamilyPropertyItem.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */


#include "qfontfamilypropertyitem.h"

QFontFamilyPropertyItem::QFontFamilyPropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent)
	: QPropertyItem(value,name,parent)
{

}

QFontFamilyPropertyItem::~QFontFamilyPropertyItem()
{

}
