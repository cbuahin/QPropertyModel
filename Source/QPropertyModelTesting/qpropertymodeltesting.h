#ifndef QPROPERTYMODELTESTING_H
#define QPROPERTYMODELTESTING_H

#include <QtWidgets/QMainWindow>
#include "ui_qpropertymodeltesting.h"

class QPropertyModelTesting : public QMainWindow
{
	Q_OBJECT

public:
	QPropertyModelTesting(QWidget *parent = 0);
	~QPropertyModelTesting();

private:
	Ui::QPropertyModelTestingClass ui;
};

#endif // QPROPERTYMODELTESTING_H
