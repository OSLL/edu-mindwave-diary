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

    const QString CurrConcValue = QString::number(currConcentration);
    ui->LabelCurrConc->setText(CurrConcValue);
    const QString CurrMedValue = QString::number(currMeditation);
    ui->LabelCurrMed->setText(CurrMedValue);

    YConcentration[Period] = currConcentration;
    YMeditation[Period] = currMeditation;

    if (ui->radioButton->isChecked()) // Choose selected button to calculate new average value for chosen activity
    {
        person[selectedPerson].NumSleep++;
        person[selectedPerson].AvConcSleep += currConcentration;
        person[selectedPerson].AvMedSleep += currMeditation;
        ui->label_4->setText("now you say that you're sleeping");
    }

    if (ui->radioButton_2->isChecked())
    {
        person[selectedPerson].NumRun++;
        person[selectedPerson].AvConcRun += currConcentration;
        person[selectedPerson].AvMedRun += currMeditation;
        ui->label_4->setText("now you say that you're running");
    }

    if (ui->radioButton_3->isChecked())
    {
        person[selectedPerson].NumRead++;
        person[selectedPerson].AvConcRead += currConcentration;
        person[selectedPerson].AvMedRead += currMeditation;
        ui->label_4->setText("now you say that you're reading");
    }

    if (ui->radioButton_4->isChecked())
    {
        person[selectedPerson].NumPlay++;
        person[selectedPerson].AvConcPlay += currConcentration;
        person[selectedPerson].AvMedPlay += currMeditation;
        ui->label_4->setText("now you say that you're playing");
    }

    if (ui->radioButton_5->isChecked())
    {
        ui->label_4->setText("");
    }

    if (Period >= 100) // Changing period
        NoPeriod++;
    Period = (Period + 1) % NUMBER_OF_POINTS;

    if (person[selectedPerson].AvConcSleep != 0)
        ui->label_5->setText(QString::number(person[selectedPerson].FracSleepConc()));

    if (person[selectedPerson].AvConcRun != 0)
        ui->label_6->setText(QString::number(person[selectedPerson].FracRunConc()));

    if (person[selectedPerson].AvConcRead != 0)
        ui->label_7->setText(QString::number(person[selectedPerson].FracReadConc()));

    if (person[selectedPerson].AvConcPlay != 0)
        ui->label_8->setText(QString::number(person[selectedPerson].FracPlayConc()));

    if (person[selectedPerson].AvMedSleep != 0)
        ui->label_14->setText(QString::number(person[selectedPerson].FracSleepMed()));

    if (person[selectedPerson].AvMedRun != 0)
        ui->label_15->setText(QString::number(person[selectedPerson].FracRunMed()));

    if (person[selectedPerson].AvMedRead != 0)
        ui->label_16->setText(QString::number(person[selectedPerson].FracReadMed()));

    if (person[selectedPerson].AvMedPlay != 0)
        ui->label_17->setText(QString::number(person[selectedPerson].FracPlayMed()));

    MainWindow::on_buttonRefresh_clicked(); // Update graphic

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
    char str [1024];
    for (int i = 0; i < 4; ++i)
    {
        dataFile.write(str, person[i].NumSleep);
        dataFile.write(str, person[i].NumRun);
        dataFile.write(str, person[i].NumRead);
        dataFile.write(str, person[i].NumPlay);
        dataFile.write(str, person[i].AvConcSleep);
        dataFile.write(str, person[i].AvConcRun);
        dataFile.write(str, person[i].AvConcRead);
        dataFile.write(str, person[i].AvConcPlay);
        dataFile.write(str, person[i].AvMedSleep);
        dataFile.write(str, person[i].AvMedRun);
        dataFile.write(str, person[i].AvMedRead);
        dataFile.write(str, person[i].AvMedPlay);
    }

    close();
}

void MainWindow::on_buttonRefresh_clicked()
{
    // Upgrade graphic

    AverageValueConc = 0;
    QVector<double> x2(NUMBER_OF_POINTS), y2(NUMBER_OF_POINTS); // Points to concentrarion graphic
    for (int i = 0; i < NUMBER_OF_POINTS; ++i)
    {
      x2[i] = XConcentration[i]; // We get our values from global array
      y2[i] = YConcentration[(i + Period) % NUMBER_OF_POINTS];
      AverageValueConc += y2[i];
    }

    QVector <double> x1(2), y1(2); // Array for average concentration line
    if (NoPeriod == 0)
    {
        x1[0] = 1 - Period / 50.0;
        y1[0] = AverageValueConc / Period;
    }
    else
    {
        x1[0] = -1;
        y1[0] = AverageValueConc / NUMBER_OF_POINTS;
    }
    x1[1] = 1;
    y1[1] = y1[0];

    // Display graphic
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x1, y1);
    ui->widget->addGraph();
    ui->widget->graph(1)->setData(x2, y2);

    QPen pen;
    pen.setColor(QColor(210, 10, 10));

    ui->widget->graph(1)->setPen(pen);
    ui->widget->graph(0)->setPen(pen);

    // Here some operation to change graphic view
    ui->widget->xAxis->setLabel("time");
    ui->widget->yAxis->setLabel("value");
    // Set axes ranges, so we see all data
    ui->widget->xAxis->setRange(-1, 1);
    ui->widget->yAxis->setRange(0, 100);
    ui->widget->replot();

    AverageValueMed = 0;
    QVector<double> x3(NUMBER_OF_POINTS), y3(NUMBER_OF_POINTS); // Points to meditation graphic
    for (int i = 0; i < NUMBER_OF_POINTS; ++i)
    {
      x3[i] = XMeditation[i];
      y3[i] = YMeditation[(i + Period) % NUMBER_OF_POINTS];
      AverageValueMed += y3[i];
    }    

    QVector<double> x4(2), y4(2); // Array for average meditation line
    if (NoPeriod == 0)
    {
        x4[0] = 1 - Period / 50.0;
        y4[0] = AverageValueMed / Period;
    }
    else
    {
        x4[0] = -1;
        y4[0] = AverageValueMed / NUMBER_OF_POINTS;
    }
    x4[1] = 1;
    y4[1] = y4[0];

    // Display graphic
    ui->widget->addGraph();
    ui->widget->graph(2)->setData(x3, y3);
    ui->widget->addGraph();
    ui->widget->graph(3)->setData(x4, y4);

    pen.setColor(QColor(10, 10, 210));

    ui->widget->graph(2)->setPen(pen);
    ui->widget->graph(3)->setPen(pen);

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
    ui->LabelCurrConc->setText("");
    ui->LabelCurrMed->setText("");

    MainWindow::on_buttonRefresh_clicked(); // Refresh graphic
}

void MainWindow::on_buttonAnswer_clicked()
{
    double a = std::min(abs(AverageValueConc - person[selectedPerson].AvConcSleep),
                        abs(AverageValueConc - person[selectedPerson].AvConcRun));
    a = std::min(a, (double)abs(AverageValueConc - person[selectedPerson].AvConcRead));
    a = std::min(a, (double)abs(AverageValueConc - person[selectedPerson].AvConcPlay));

    double b = std::min(abs(AverageValueMed - person[selectedPerson].AvMedSleep),
                        abs(AverageValueMed - person[selectedPerson].AvMedRun));
    b = std::min(b, (double)abs(AverageValueMed - person[selectedPerson].AvMedRead));
    b = std::min(b, (double)abs(AverageValueMed - person[selectedPerson].AvMedPlay));

    if (a == abs(AverageValueConc - person[selectedPerson].AvConcSleep))
        ui->label_9->setText("I think, you are sleeping");

    if (a == abs(AverageValueConc - person[selectedPerson].AvConcRun))
        ui->label_9->setText("I think, you are running");

    if (a == abs(AverageValueConc - person[selectedPerson].AvConcRead))
        ui->label_9->setText("I think, you are reading");

    if (a == abs(AverageValueConc - person[selectedPerson].AvConcPlay))
        ui->label_9->setText("I think, you are playing");

}
