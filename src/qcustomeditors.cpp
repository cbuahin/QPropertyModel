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


#include "qcustomeditors.h"
#include <climits>

QCustomDoubleSpinBox::QCustomDoubleSpinBox(QWidget *parent)
   : QDoubleSpinBox(parent)
{
   setDecimals(6);
   setSingleStep(0.1);
   setRange(-1e9, 1e9);
   setKeyboardTracking(false);
}

QCustomSpinBox::QCustomSpinBox(QWidget *parent)
   : QSpinBox(parent)
{
   setRange(INT_MIN, INT_MAX);
   setKeyboardTracking(false);
}

QCustomDateTimeEdit::QCustomDateTimeEdit(QWidget *parent)
   : QDateTimeEdit(parent)
{
  setDisplayFormat("yyyy-MM-dd HH:mm:ss");
  setCalendarPopup(true);
}

QCustomDateEdit::QCustomDateEdit(QWidget *parent)
   : QDateEdit(parent)
{
  setDisplayFormat("yyyy-MM-dd");
  setCalendarPopup(true);
}


QCustomTimeEdit::QCustomTimeEdit(QWidget *parent)
   : QTimeEdit(parent)
{
  setDisplayFormat("HH:mm:ss");
}
