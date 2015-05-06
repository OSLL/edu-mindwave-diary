#include "widget.h"
#include "ui_widget.h"
#include "../thinkgear.h"

int start_gear_main_main();

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    start_gear_main_main();
}

Widget::~Widget()
{
    delete ui;
}
