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
