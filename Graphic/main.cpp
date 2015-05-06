#include "mainwindow.h"
#include <QApplication>

// Extern variables from mainwindow.h
double AverageValueConc = 0, AverageValueMed = 0;
double XMeditation[NUMBER_OF_POINTS], YMeditation[NUMBER_OF_POINTS];
double XConcentration[NUMBER_OF_POINTS], YConcentration[NUMBER_OF_POINTS];
int Period = 0, NoPeriod = 0, selectedPerson = 0;
QVector <PersonalData> person (4);
QFile dataFile("data");

int main(int argc, char *argv[])
{    
    for (int i = 0; i < NUMBER_OF_POINTS; ++i)
    {
      XConcentration[i] = i/50.0 - 1; // Let x be in range from -1 to 1
      XMeditation[i] = i/50.0 - 1; //
      YConcentration[i] = 0; // start value of y
      YMeditation[i] = 0; //
    }

    char str [1024];
    for (int i = 0; i < 4; ++i)
    {
        person[i].NumSleep = dataFile.read(str, sizeof(str));
        person[i].NumRun = dataFile.read(str, sizeof(str));
        person[i].NumRead = dataFile.read(str, sizeof(str));
        person[i].NumPlay = dataFile.read(str, sizeof(str));
        person[i].AvConcSleep = dataFile.read(str, sizeof(str));
        person[i].AvConcRun = dataFile.read(str, sizeof(str));
        person[i].AvConcRead = dataFile.read(str, sizeof(str));
        person[i].AvConcPlay = dataFile.read(str, sizeof(str));
        person[i].AvMedSleep = dataFile.read(str, sizeof(str));
        person[i].AvMedRun = dataFile.read(str, sizeof(str));
        person[i].AvMedRead = dataFile.read(str, sizeof(str));
        person[i].AvMedPlay = dataFile.read(str, sizeof(str));
    }

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
