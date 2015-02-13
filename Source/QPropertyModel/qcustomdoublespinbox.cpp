#include "stdafx.h"
#include "qcustomdoublespinbox.h"

QCustomDoubleSpinBox::QCustomDoubleSpinBox(QWidget *parent)
	: QDoubleSpinBox(parent)
{
	setDecimals(10);
	setSingleStep(0.5);
}

QCustomDoubleSpinBox::~QCustomDoubleSpinBox()
{

}
