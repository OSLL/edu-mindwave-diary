#include "mainwindow.h"
#include <QApplication>

double TestVariable, AverageValue;
double XGlobal[101], YGlobal[101];
int Period, NoPeriod;
int Num1, Num2, Num3, Num4; //Количество запусков при нажатой кнопки.
double Av1, Av2, Av3, Av4; //Среднее значение при нажатой кнопки.

int main(int argc, char *argv[])
{
    AverageValue = 0;
    NoPeriod = 0;
    Num1 = 0;
    Num2 = 0;
    Num3 = 0;
    Num4 = 0;
    Av1 = 0;
    Av2 = 0;
    Av3 = 0;
    Av4 = 0;
    Period = 0;
    TestVariable = 0;
    for (int i=0; i<101; ++i)
    {
      XGlobal[i] = i/50.0 - 1; // Задаем х, пусть он рассположен от -1 до 1.
      YGlobal[i] = 0; // начальные значения у.
    }

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
