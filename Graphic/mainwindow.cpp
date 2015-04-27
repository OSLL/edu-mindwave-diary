#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "values.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->buttonWrite,SIGNAL(clicked()),this,SLOT(on_buttonWrite_clicked()));
    connect(ui->buttonStart,SIGNAL(clicked()),this,SLOT(on_buttonStart_clicked()));
    connect(ui->buttonStop,SIGNAL(clicked()),this,SLOT(on_buttonStop_clicked()));
    connect(ui->buttonExit,SIGNAL(clicked()),this,SLOT(on_buttonExit_clicked()));

    timer = new QTimer;

    ui->labelPause->setText("");

    // Slot will be refreshed, then alarm will ring
    QObject::connect(timer,SIGNAL(timeout()), this, SLOT(timer_overflow()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonWrite_clicked()
{
    // Refresh timer
    ui->label_3->setText(QTime::currentTime().toString()); // Show current time
    ui->label->setText(QString::number((Period + 100 * NoPeriod))); // Show number of data packets

    int currConcentration = getConcentrationValue();
    int currMeditation = getMeditationValue();
    currConcentration = getConcentrationValue();
    currMeditation = getMeditationValue();

    const QString str = QString::number(currConcentration); // Imitation data packet
    ui->textBrowser->setText(str);
    YConcentration[Period] = currConcentration;
    YMeditation[Period] = currMeditation;

    if (ui->radioButton->isChecked()) // Choose selected button to calculate new average value for chosen activity
    {
        first.NumSleep++;
        first.AvConcSleep += currConcentration;
        first.AvMedSleep += currMeditation;
        ui->label_4->setText("now you say that you're sleeping");
    }

    if (ui->radioButton_2->isChecked())
    {
        first.NumRun++;
        first.AvConcRun += currConcentration;
        first.AvMedRun += currMeditation;
        ui->label_4->setText("now you say that you're running");
    }

    if (ui->radioButton_3->isChecked())
    {
        first.NumRead++;
        first.AvConcRead += currConcentration;
        first.AvMedRead += currMeditation;
        ui->label_4->setText("now you say that you're reading");
    }

    if (ui->radioButton_4->isChecked())
    {
        first.NumPlay++;
        first.AvConcPlay += currConcentration;
        first.AvMedPlay += currMeditation;
        ui->label_4->setText("now you say that you're playing");
    }

    if (ui->radioButton_5->isChecked())
    {
        ui->label_4->setText("");
    }

    if (Period >= 100) // Changing period
        NoPeriod++;
    Period = (Period + 1) % NUMBER_OF_POINTS;

    if (first.AvConcSleep != 0)
        ui->label_5->setText(QString::number(first.FracSleepConc()));

    if (first.AvConcRun != 0)
        ui->label_6->setText(QString::number(first.FracRunConc()));

    if (first.AvConcRead != 0)
        ui->label_7->setText(QString::number(first.FracReadConc()));

    if (first.AvConcPlay != 0)
        ui->label_8->setText(QString::number(first.FracPlayConc()));

    if (first.AvMedSleep != 0)
        ui->label_14->setText(QString::number(first.FracSleepMed()));

    if (first.AvMedRun != 0)
        ui->label_15->setText(QString::number(first.FracRunMed()));

    if (first.AvMedRead != 0)
        ui->label_16->setText(QString::number(first.FracReadMed()));

    if (first.AvMedPlay != 0)
        ui->label_17->setText(QString::number(first.FracPlayMed()));

    MainWindow::on_buttonRefresh_clicked(); // Update graphic

    // Calculating of average values
    if (NoPeriod > 0)
    {
        AverageValueConc += currConcentration - YConcentration[0];
        AverageValueMed += currMeditation - YMeditation[0];
    }
    else
    {

    }

    ui->horizontalSlider->setRange(100, 1000);
    ui->labelPause->setText("");
    ui->label->setStyleSheet("color: rgb(0, 0, 0)");

    if (ui->checkBox->isChecked())
        MainWindow::on_buttonAnswer_clicked();
}

void MainWindow::timer_overflow()
{
    MainWindow::on_buttonWrite_clicked(); // Update graphic

    ui->horizontalSlider->setRange(100, 1000); // Refresh speed of displaying
    timer->start(ui->horizontalSlider->value());
}

void MainWindow::on_buttonStart_clicked()
{
    // Here the program upgrading automatically
    timer->start(ui->horizontalSlider->value());
    ui->buttonWrite->setEnabled(false);
    ui->buttonRefresh->setEnabled(false);
}

void MainWindow::on_buttonStop_clicked()
{
    // Now you should upgrade program by yourself
    QFont font = ui->labelPause->font();
    font.setPointSize(50);
    ui->labelPause->setFont(font);
    ui->labelPause->setText("Pause");
    ui->labelPause->setStyleSheet("color: rgb(250, 10, 10)");
    ui->label->setStyleSheet("color: rgb(200, 0, 0)");
    timer->stop();
    ui->buttonWrite->setEnabled(true);
    ui->buttonRefresh->setEnabled(true);
}

void MainWindow::on_buttonExit_clicked()
{
    close();
}

void MainWindow::on_buttonRefresh_clicked()
{
    // Upgrade graphic
    QVector <double> x1(2), y1(2); // Array for average concentration line
    int a; // Position to set average value in OX
    if (NoPeriod == 0)
       a = Period;
    else
        a = 100;
    x1[0] = 1 - a / 50.0;
    x1[1] = 1;
    y1[0] = AverageValueConc / NUMBER_OF_POINTS;
    y1[1] = y1[0];

    // Display graphic
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x1, y1);

    QPen pen;
    pen.setColor(QColor(50, 50, 100));
    ui->widget->graph(0)->setPen(pen);

    // Here some operation to change graphic view
    ui->widget->xAxis->setLabel("time");
    ui->widget->yAxis->setLabel("value");
    // Set axes ranges, so we see all data
    ui->widget->xAxis->setRange(-1, 1);
    ui->widget->yAxis->setRange(0, 100);
    ui->widget->replot();

    QVector<double> x2(NUMBER_OF_POINTS), y2(NUMBER_OF_POINTS); // Points to concentrarion graphic
    for (int i = 0; i < NUMBER_OF_POINTS; ++i)
    {
      x2[i] = XConcentration[i]; // We get our values from global array
      y2[i] = YConcentration[(i + Period) % NUMBER_OF_POINTS];
    }

    ui->widget->addGraph();
    ui->widget->graph(1)->setData(x2, y2);

    QVector<double> x3(NUMBER_OF_POINTS), y3(NUMBER_OF_POINTS); // Points to meditation graphic
    for (int i = 0; i < NUMBER_OF_POINTS; ++i)
    {
      x3[i] = XMeditation[i];
      y3[i] = YMeditation[(i + Period) % NUMBER_OF_POINTS];
    }
    ui->widget->addGraph();
    pen.setColor(QColor(210, 10, 10));
    ui->widget->graph(2)->setPen(pen);
    ui->widget->graph(2)->setData(x3, y3);

    QVector<double> x4(2), y4(2); // Array for average meditation line
    x4[0] = 1 - a/50.0;
    x4[1] = 1;
    y4[0] = AverageValueMed / NUMBER_OF_POINTS;
    y4[1] = y4[0];

    // Displaying graphic
    ui->widget->addGraph();
    ui->widget->graph(3)->setData(x4, y4);


    ui->widget->replot();
}


void MainWindow::on_buttonRestart_clicked()
{
    AverageValueConc = 0;
    AverageValueMed = 0;
    NoPeriod = 0;
    Period = 0;
    for (int i = 0; i < NUMBER_OF_POINTS; ++i)
    {
      XConcentration[i] = i/50.0 - 1; // Let X be in range from -1 to 1
      YConcentration[i] = 0;
      XMeditation[i] = i/50.0 - 1; //
      YMeditation[i] = 0;
    }
    ui->label->setText("");
    ui->labelPause->setText("");
    ui->label_3->setText("");
    ui->textBrowser->setText("");
    MainWindow::on_buttonRefresh_clicked(); // Refresh graphic
}

void MainWindow::on_buttonAnswer_clicked()
{
    double a = std::min(abs(AverageValueConc - first.AvConcSleep), abs(AverageValueConc - first.AvConcRun));
    a = std::min(a, (double)abs(AverageValueConc - first.AvConcRead));
    a = std::min(a, (double)abs(AverageValueConc - first.AvConcPlay));

    double b = std::min(abs(AverageValueMed - first.AvMedSleep), abs(AverageValueMed - first.AvMedRun));
    b = std::min(b, (double)abs(AverageValueMed - first.AvMedRead));
    b = std::min(b, (double)abs(AverageValueMed - first.AvMedPlay));

    if (a == abs(AverageValueConc - first.AvConcSleep))
        ui->label_9->setText("I think, you are sleeping");

    if (a == abs(AverageValueConc - first.AvConcRun))
        ui->label_9->setText("I think, you are running");

    if (a == abs(AverageValueConc - first.AvConcRead))
        ui->label_9->setText("I think, you are reading");

    if (a == abs(AverageValueConc - first.AvConcPlay))
        ui->label_9->setText("I think, you are playing");

}
