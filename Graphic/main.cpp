#include "mainwindow.h"
#include <QApplication>

#define NUMBER_OF_POINTS 101

// Extern variables from mainwindow.h
double TestVariable = 0, AverageValueConc = 0, AverageValueMed = 0;
double XMeditation[101], YMeditation[101];
double XConcentration[101], YConcentration[101];
int Period = 0, NoPeriod = 0;
PersonalData first;

int main(int argc, char *argv[])
{
    for (int i = 0; i < NUMBER_OF_POINTS; ++i)
    {
      XConcentration[i] = i/50.0 - 1; // Let x be in range from -1 to 1
      XMeditation[i] = i/50.0 - 1; //
      YConcentration[i] = 0; // start value of y
      YMeditation[i] = 0; //
     }

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
