#include "widget.h"
#include <QApplication>
#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    printf("\nLoading..\n");

    Widget w;
    w.show();

    return a.exec();
}
