#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
#include <QString>

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
    //Обновляем значение времени на форме
    ui->label_3->setText(QTime::currentTime().toString());//Выводим текущее время.
    ui->label->setText(QString::number((Period + 100*NoPeriod)));//Выводим количество произведенных считываний.

    const QString str = QString::number(1 + sin(TestVariable));//Имитируем поступивший сигнал.
    TestVariable += rand() % 100;
    ui->textBrowser->setText(str);
    YGlobal[Period] = 1 + sin(TestVariable);

    if(ui->radioButton->isChecked())//Разбираем Варианты, какая кнопка нажата, для исчисления среднего.
    {
        Num1++;
        Av1 += 1 + sin(TestVariable);
        ui->label_4->setText("now you say that you're sleeping");
    }

    if(ui->radioButton_2->isChecked())
    {
        Num2++;
        Av2 += 1 + sin(TestVariable);
        ui->label_4->setText("now you say that you're running");
    }
    if(ui->radioButton_3->isChecked())
    {
        Num3++;
        Av3 += 1 + sin(TestVariable);
        ui->label_4->setText("now you say that you're reading");
    }
    if(ui->radioButton_4->isChecked())
    {
        Num4++;
        Av4 += 1 + sin(TestVariable);
        ui->label_4->setText("now you say that you're playing");
    }
    if(ui->radioButton_5->isChecked())
    {
        ui->label_4->setText("");
    }

    if (Period >= 100)//Подсчет периода.
        NoPeriod++;
    Period = (Period + 1) % 101;

    if (Av1 != 0)
        ui->label_5->setText(QString::number(Av1/Num1));

    if (Av2 != 0)
        ui->label_6->setText(QString::number(Av2/Num2));

    if (Av3 != 0)
        ui->label_7->setText(QString::number(Av3/Num3));

    if (Av4 != 0)
        ui->label_8->setText(QString::number(Av4/Num4));

    MainWindow::on_pushButton_5_clicked();//Вывод графика.
    AverageValue += 1 + sin(TestVariable);//Подсчет среднего значения.

    ui->horizontalSlider->setRange(100, 1000);
    ui->label_2->setText("");//Убераем надпись Pause.
    ui->label->setStyleSheet("color: rgb(0, 0, 0)");//Переводим надпись с числом циклов в черный цвет.

    if (ui->checkBox->isChecked())
        MainWindow::on_pushButton_7_clicked();
}

void MainWindow::timer_overflow()
{
    MainWindow::on_pushButton_clicked();//Вывод графика.

    ui->horizontalSlider->setRange(100, 1000);//Обновление частоты запуска.
    timer->start(ui->horizontalSlider->value());

}

void MainWindow::on_pushButton_2_clicked()
{
    // кнопка 'start'
    // запускаем таймер с интервалом 500 мк/с или 1 сек
    // он будет каждую секунду выполнять действия,
    // которые прописанные в нашей функции
    timer->start(ui->horizontalSlider->value());
    ui->pushButton->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
}

void MainWindow::on_pushButton_3_clicked()
{
    // кнопка 'stop'
    // останавливает таймер и, следовательно, выполнение нашей функции
    QFont font = ui->label_2->font();
    font.setPointSize(50);
    ui->label_2->setFont(font);
    ui->label_2->setText("Pause");//Пишем, что начилось пауза.
    ui->label_2->setStyleSheet("color: rgb(250, 10, 10)");
    ui->label->setStyleSheet("color: rgb(200, 0, 0)");//Переводим надпись с количеством циклов в красный цвет.
    timer->stop();
    ui->pushButton->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
}

void MainWindow::on_pushButton_4_clicked()
{
    // кнопка 'exit'
    // выход из программы
    close();
}

void MainWindow::on_pushButton_5_clicked()
{
    //Graphic
    QVector<double> x1(101), y1(101); // Задаем массив средних значений.
    int a;//Позиция с которой будем рисовать всреднее значение.
    if (NoPeriod == 0)
    {
       a = Period;
    }
    else
        a = 100;

    for (int i = 100 - a; i < 100; ++i)
    {
      x1[i] = i/50.0 - 1;
      y1[i] = AverageValue / (Period + 100*NoPeriod); // Рисуем только там, где уже были значения.
    }
    //Рисуем график.
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x1, y1);

    QPen pen;
    pen.setColor(QColor(50, 50, 100));// Цвет контура столбца
    ui->widget->graph(0)->setPen(pen);

    //Называем оси. Задаем масштаб координат.
    ui->widget->xAxis->setLabel("time");
    ui->widget->yAxis->setLabel("value");
    // set axes ranges, so we see all data:
    ui->widget->xAxis->setRange(-1, 1);
    ui->widget->yAxis->setRange(0, 2);
    ui->widget->replot();

    QVector<double> x2(101), y2(101); //Рисуем второй график. Со значениями.
    for (int i = 0; i < 101; ++i)
    {
      x2[i] = XGlobal[i]; // Копируем значения глобального графика со сдвигом.
      y2[i] = YGlobal[(i + Period) % 101];
    }
    ui->widget->addGraph();
    ui->widget->graph(1)->setData(x2, y2);
    ui->widget->replot();
}


void MainWindow::on_pushButton_6_clicked()
{
    AverageValue = 0;
    NoPeriod = 0;
    Period = 0;
    TestVariable = 0;
    for (int i=0; i<101; ++i)
    {
      XGlobal[i] = i/50.0 - 1; // Задаем х, пусть он рассположен от -1 до 1.
      YGlobal[i] = 0; // начальные значения у.
    }
    ui->label->setText("");
    ui->label_2->setText("");
    ui->label_3->setText("");
    ui->textBrowser->setText("");
    MainWindow::on_pushButton_5_clicked();//Обновление.
}

void MainWindow::on_pushButton_7_clicked()
{
    double a = abs(AverageValue - Av1);
    if (a > abs(AverageValue - Av2))
            a = abs(AverageValue - Av2);
    if (a > abs(AverageValue - Av3))
            a = abs(AverageValue - Av3);
    if (a > abs(AverageValue - Av4))
            a = abs(AverageValue - Av4);
    if (a == abs(AverageValue - Av1))
        ui->label_9->setText("I think, your are sleeping");

    if (a == abs(AverageValue - Av2))
        ui->label_9->setText("I think, your are running");

    if (a == abs(AverageValue - Av3))
        ui->label_9->setText("I think, your are reading");

    if (a == abs(AverageValue - Av4))
        ui->label_9->setText("I think, your are playing");
}
