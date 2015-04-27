#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "libraries.h"

#define NUMBER_OF_POINTS 101

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTimer *timer;

private slots:
    void on_buttonWrite_clicked();

    void on_buttonStart_clicked();

    void on_buttonStop_clicked();

    void on_buttonExit_clicked();

    void on_buttonRefresh_clicked();

    // Function for alarm
    void timer_overflow();

    void on_buttonRestart_clicked();

    void on_buttonAnswer_clicked();

private:
    Ui::MainWindow *ui;

};

struct PersonalData
{
    int NumSleep = 1, NumRun = 1, NumRead = 1, NumPlay = 1; // Number of data packets
    double AvConcSleep = 0, AvConcRun = 0, AvConcRead = 0, AvConcPlay = 0; // Average value of concentration
    double AvMedSleep = 0, AvMedRun = 0, AvMedRead = 0, AvMedPlay = 0; // Average value of meditation

    double FracSleepConc ()
    {
        return (this->AvConcSleep / this->NumSleep);
    }

    double FracRunConc ()
    {
        return (this->AvConcRun / this->NumRun);
    }

    double FracReadConc ()
    {
        return (this->AvConcRead / this->NumRead);
    }

    double FracPlayConc ()
    {
        return (this->AvConcPlay / this->NumPlay);
    }

    double FracSleepMed ()
    {
        return (this->AvMedSleep / this->NumSleep);
    }

    double FracRunMed ()
    {
        return (this->AvMedRun / this->NumRun);
    }

    double FracReadMed ()
    {
        return (this->AvMedRead / this->NumRead);
    }

    double FracPlayMed ()
    {
        return (this->AvMedPlay / this->NumPlay);
    }
};

extern PersonalData first;
extern int Period, NoPeriod; // Past period, number of current period
extern double TestVariable; // Random value for graphic
extern double AverageValueConc, AverageValueMed; // Current average values
extern double XMeditation[101], YMeditation[101]; // Global array for points in graphic
extern double XConcentration[101], YConcentration[101]; // Global array for points in graphic

#endif // MAINWINDOW_H
