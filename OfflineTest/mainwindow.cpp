#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(on_pushButton_2_clicked()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(on_pushButton_3_clicked()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(on_pushButton_4_clicked()));
    timer = new QTimer;
    //Связываем сигнал переполнения таймера со слотом
    QObject::connect(timer,SIGNAL(timeout()), this, SLOT(timer_overflow()));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    const QString str = QString::number(1 + sin(testVariable));
    testVariable += rand() % 100;
    ui->textBrowser->setText(str);
}

void MainWindow::on_MainWindow_iconSizeChanged(const QSize &icoinnSize)
{

}

void MainWindow::timer_overflow()
{
 //Обновляем значение времени на форме
 ui->label->setText(QTime::currentTime().toString());
 const QString str = QString::number(1 + sin(testVariable));
 testVariable += rand() % 100;
 ui->textBrowser->setText(str);
}

void MainWindow::on_pushButton_2_clicked()
{
    // кнопка 'start'
    // запускаем таймер с интервалом 1000 мк/с или 1 сек
    // он будет каждую секунду выполнять действия,
    // которые прописанные в нашей функции
    timer->start(1000);
}

void MainWindow::on_pushButton_3_clicked()
{
    // кнопка 'stop'
    // останавливает таймер и, следовательно, выполнение нашей функции
    timer->stop();
}

void MainWindow::on_pushButton_4_clicked()
{
    // кнопка 'exit'
    // выход из программы
    close();
}
