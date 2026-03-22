/*!
 * \file qcustomeditors.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of custom Qt editor widgets.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */

#include "stdafx.h"
#include "qcustomeditors.h"

QCustomDoubleSpinBox::QCustomDoubleSpinBox(QWidget *parent)
   : QDoubleSpinBox(parent)
{
   setDecimals(15);
   setSingleStep(0.1);
}

QCustomDateTimeEdit::QCustomDateTimeEdit(QWidget *parent)
   : QDateTimeEdit(parent)
{
  setDisplayFormat("MM/dd/yyyy hh:mm:ss AP");
}

QCustomDateEdit::QCustomDateEdit(QWidget *parent)
   : QDateEdit(parent)
{
  setDisplayFormat("MM/dd/yyyy");
}


QCustomTimeEdit::QCustomTimeEdit(QWidget *parent)
   : QTimeEdit(parent)
{
  setDisplayFormat("hh:mm:ss AP");
}
