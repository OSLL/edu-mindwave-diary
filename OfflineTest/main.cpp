#include "mainwindow.h"
#include <QApplication>

double testVariable;

int main(int argc, char *argv[])
{
    testVariable = 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
