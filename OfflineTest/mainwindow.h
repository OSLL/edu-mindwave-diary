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
    void on_MainWindow_iconSizeChanged(const QSize &iconSize);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    //Слот, который срабатывает при переполнении таймера
    void timer_overflow();

private:
    Ui::MainWindow *ui;
};

extern double testVariable;

#endif // MAINWINDOW_H
