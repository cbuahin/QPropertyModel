#include "stdafx.h"
#include "qpropertymodeltesting.h"
#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   a.setStyle("fusion");

   QPropertyModelTesting w;
   w.show();
   return a.exec();
}
