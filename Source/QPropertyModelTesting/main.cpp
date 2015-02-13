#include "stdafx.h"
#include "qpropertymodeltesting.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QPropertyModelTesting w;
	w.show();
	return a.exec();
}
