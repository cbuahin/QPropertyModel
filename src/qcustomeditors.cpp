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

QCustomTimespanEdit::QCustomTimespanEdit(QWidget *parent)
   : QWidget(parent)
{
   auto *lay = new QHBoxLayout(this);
   lay->setContentsMargins(0, 0, 0, 0);

   m_daysSpin = new QSpinBox(this);
   m_daysSpin->setRange(0, 365);
   m_daysSpin->setSuffix(QStringLiteral(" d"));
   m_daysSpin->setKeyboardTracking(false);

   m_timeEdit = new QTimeEdit(this);
   m_timeEdit->setDisplayFormat(QStringLiteral("HH:mm:ss"));

   lay->addWidget(m_daysSpin);
   lay->addWidget(m_timeEdit, 1);

   connect(m_daysSpin, qOverload<int>(&QSpinBox::valueChanged),
           this, &QCustomTimespanEdit::onSubWidgetChanged);
   connect(m_timeEdit, &QTimeEdit::timeChanged,
           this, &QCustomTimespanEdit::onSubWidgetChanged);
}

qint64 QCustomTimespanEdit::totalSeconds() const
{
   const QTime t = m_timeEdit->time();
   return static_cast<qint64>(m_daysSpin->value()) * 86400
          + t.hour()   * 3600
          + t.minute() * 60
          + t.second();
}

int QCustomTimespanEdit::maximumDays() const
{
   return m_daysSpin->maximum();
}

void QCustomTimespanEdit::setMaximumDays(int days)
{
   m_daysSpin->setMaximum(qMax(0, days));
}

void QCustomTimespanEdit::setTotalSeconds(qint64 secs)
{
   if (secs < 0) secs = 0;
   const qint64 days = secs / 86400;
   const qint64 rem  = secs % 86400;
   const int h = static_cast<int>(rem / 3600);
   const int m = static_cast<int>((rem % 3600) / 60);
   const int s = static_cast<int>(rem % 60);

   // Block sub-widget signals so we emit one combined totalSecondsChanged
   // instead of two intermediate ones.
   const bool b1 = m_daysSpin->blockSignals(true);
   const bool b2 = m_timeEdit->blockSignals(true);
   if (days > m_daysSpin->maximum())
      m_daysSpin->setMaximum(static_cast<int>(days));
   m_daysSpin->setValue(static_cast<int>(days));
   m_timeEdit->setTime(QTime(h, m, s));
   m_daysSpin->blockSignals(b1);
   m_timeEdit->blockSignals(b2);

   emit totalSecondsChanged(totalSeconds());
}

void QCustomTimespanEdit::onSubWidgetChanged()
{
   emit totalSecondsChanged(totalSeconds());
}
