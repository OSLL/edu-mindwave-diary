#include "mainwindow.h"
#include <QApplication>

// Extern variables from mainwindow.h
double AverageValueConc = 0, AverageValueMed = 0;
double XMeditation[NUMBER_OF_POINTS], YMeditation[NUMBER_OF_POINTS];
double XConcentration[NUMBER_OF_POINTS], YConcentration[NUMBER_OF_POINTS];
int Period = 0, NoPeriod = 0, selectedPerson = 0;
QVector <PersonalData> person (4);

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
