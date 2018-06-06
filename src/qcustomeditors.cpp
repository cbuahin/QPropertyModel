/*!
 * \author Caleb Amoa Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * \license
 * This file and its associated files, and libraries are free software.
 * You can redistribute it and/or modify it under the terms of the
 * Lesser GNU General Public License as published by the Free Software Foundation;
 * either version 3 of the License, or (at your option) any later version.
 * This file and its associated files is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.(see <http://www.gnu.org/licenses/> for details)
 * \copyright Copyright 2014-2018, Caleb Buahin, All rights reserved.
 * \date 2014-2018
 * \pre
 * \bug
 * \warning
 * \todo
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
