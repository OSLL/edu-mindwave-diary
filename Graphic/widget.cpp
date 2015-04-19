#include <Widget.h>
#include <QtWidgets>
#include <QtCore>
#include <QtGui>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //объявляем переменную таймера
    timer = new QTimer(this);

    //Подключаем сигнал таймера к слоту, которым выступает наша функция
    connect(timer, SIGNAL(timeout()), this, SLOT(myTimer()));

    //устанавливаем таймер в 0
    timer->stop();
}

void Widget::myTimer()
{
    // объявляем переменную дата/время и передаем ей параметры
    // текущего времени на компьютере
    QTime myTime = QTime::currentTime();

    // записываем текущее время в listWidget
    ui->listWidget->addItem(myTime.toString());
}
