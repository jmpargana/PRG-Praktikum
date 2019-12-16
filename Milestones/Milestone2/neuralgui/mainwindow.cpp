#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QComboBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_import, &QPushButton::clicked,
            this, &MainWindow::importdata);
    connect(ui->comboBox_draw, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::draw);
    connect(ui->pushButton_startTraining, &QPushButton::clicked,
            this, &MainWindow::startTraining);
    // TODO connections

    m_controller.moveToThread(&m_networkThread);
    m_networkThread.start();

    // we are going to modify this one later :)
    ui->mainGraph->addGraph();

    draw(); // make sure we paint what the GUI has selected
}

MainWindow::~MainWindow()
{
    m_networkThread.quit();
    m_networkThread.wait();
    delete ui;
}



void MainWindow::importdata()
{
    QString fileName = QFileDialog::getExistingDirectory(this, "Choose a data Directory");
    if (fileName.isNull())
        return;
    std::string fileNameStd = fileName.toStdString();
    // TODO
}

void MainWindow::events_for_training()
{

}


void MainWindow::events_for_test()
{

}


void MainWindow::quantity_of_epochs()
{

}

void MainWindow::batch_size()
{

}


void MainWindow::neural_net_mode()
{

}

void MainWindow::draw()
{
    // needs to match combo box item position
    const int xSquareOption = 0;
    const int xPowerOfThreeOption = 1;
    ui->mainGraph->xAxis->setLabel("x");
    ui->mainGraph->yAxis->setLabel("y");
    ui->mainGraph->xAxis->setRange(-5, 5);
    if (ui->comboBox_draw->currentIndex() == xSquareOption) {
        QVector<double> xs, ys;
        for (double x = -5; x <= 5; x += 10.0 / 100.0) {
            xs.append(x);
            ys.append(x * x);
        }
        ui->mainGraph->graph(0)->setData(xs, ys);
        ui->mainGraph->yAxis->setRange(0, 5*5);
    } else if (ui->comboBox_draw->currentIndex() == xPowerOfThreeOption) {
        QVector<double> xs, ys;
        for (double x = -5; x <= 5; x += 10.0 / 100.0) {
            xs.append(x);
            ys.append(x * x * x);
        }
        ui->mainGraph->graph(0)->setData(xs, ys);
        ui->mainGraph->yAxis->setRange(-5*5*5, 5*5*5);
    }
    ui->mainGraph->replot();
}

void MainWindow::progress()
{

}

void MainWindow::startTraining()
{
    // thread safety :)
    QMetaObject::invokeMethod(&m_controller, "startTraining");
}
