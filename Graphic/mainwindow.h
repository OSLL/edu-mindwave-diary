#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <iostream>
#include <cmath>
#include<QTime>
#include<QTimer>

namespace Ui {
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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    //Слот, который срабатывает при переполнении таймера
    void timer_overflow();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;

};
extern int Period, NoPeriod; //Прошедший период, и количество периодов.
extern double TestVariable; //Переменная которая выбирается рандомно каждую цикл.
extern double AverageValue; //Среднее значение.
extern double XGlobal[101], YGlobal[101]; //Глабальный массив, в котором храняться значения
extern int Num1, Num2, Num3, Num4; //Количество запусков при нажатой кнопки.
extern double Av1, Av2, Av3, Av4; //Среднее значение при нажатой кнопки.

#endif // MAINWINDOW_H
