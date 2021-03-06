#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QtCore>
#include <QtGui>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:

    // функция, которая будет выполняться по таймеру
    void myTimer();

private:
    Ui::Widget *ui;

    // переменная таймера
    QTimer *timer;
};

#endif // WIDGET_H
