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
    connect(ui->comboBox_Neural_Net_Mode, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::neural_net_mode);
    connect(ui->spinBox_noEpochs, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::setNoEpoch);
    // TODO connections

    m_controller.moveToThread(&m_networkThread);
    m_networkThread.start();

    connect(&m_controller, &Controller::epochTrained,
            ui->progressBar, &QProgressBar::setValue);

//    connect(source, signal, receiver, slot)
    connect(&m_controller, &Controller::newDataPoint,
            &m_storage, &DataStorage::acceptNewDatapoint);
    connect(&m_storage, &DataStorage::dataChanged,
            this, &MainWindow::draw);

    // we are going to modify this one later :)
    ui->mainGraph->addGraph();
    ui->lossGraph->addGraph();

    setNoEpoch(ui->spinBox_noEpochs->value());
    neural_net_mode();
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
    QMetaObject::invokeMethod(&m_controller, "setTrainingDataDirectory", Q_ARG(QString, fileName));
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
    const int oneHiddenLayer = 0;
    const int twoHiddenLayers = 1;
    const int threeHiddenLayers = 2;

    QVector<unsigned> networkConfiguration;
    switch (ui->comboBox_Neural_Net_Mode->currentIndex()) {
    case oneHiddenLayer:
        networkConfiguration = {224000, 2, 1};
        break;
    case twoHiddenLayers:
        networkConfiguration = {224000, 64, 2, 1};
        break;
    case threeHiddenLayers:
        networkConfiguration = {224000, 64, 64, 2, 1};
    }

    // m_controller.setTypology(networkConfiguration)
    // we do it this way for thread safety
    QMetaObject::invokeMethod(&m_controller, "setTypology", Q_ARG(const QVector<unsigned>&, networkConfiguration));

}

void MainWindow::draw()
{
    this->drawOnGraph(ui->mainGraph, ui->comboBox_draw->currentIndex());
    this->drawOnGraph(ui->lossGraph, 1 /* loss option */);
}

void MainWindow::progress()
{

}

void MainWindow::startTraining()
{
    // thread safety :)
    QMetaObject::invokeMethod(&m_controller, "startTraining");
}

void MainWindow::setNoEpoch(int epochs)
{
    ui->progressBar->setMaximum(epochs);
    ui->progressBar->setMinimum(0);
    QMetaObject::invokeMethod(&m_controller, "setEpochNo", Q_ARG(int, epochs));
}

void MainWindow::drawOnGraph(QCustomPlot *widget, int plotId)
{
    // needs to match combo box item position
    const int xTime = 0;
    const int xLoss = 1;
    const int xLossAcc = 2;
    widget->xAxis->setLabel("x");
    widget->yAxis->setLabel("y");
    widget->xAxis->setRange(-5, 5);
    double y_max = 2;
    double x_max = 5;
    QVector<double> xs, ys;
    if (plotId == xTime) {
        widget->xAxis->setLabel("epoch");
        widget->yAxis->setLabel("time [s]");
        for (int x = 0; x <= m_storage.data["time"].first.size(); x++) {
//            if (!m_storage.data["time"].first.isEmpty() && !m_storage.data["time"].second.isEmpty()) {
            xs.append(m_storage.data["time"].first); //.last());
            ys.append(m_storage.data["time"].second); //.last());
//            }
        }
    } else if (plotId == xLoss) {
        widget->xAxis->setLabel("epoch");
        widget->yAxis->setLabel("loss");
        for (int x = 0; x <= m_storage.data["loss"].first.size(); x++) {
            xs.append(m_storage.data["loss"].first);
            ys.append(m_storage.data["loss"].second);
        }
    } else if (plotId == xLossAcc) {
        widget->xAxis->setLabel("epoch");
        widget->yAxis->setLabel("accumulated loss");
        for (int x = 0; x < m_storage.data["loss"].first.size(); x++) {

            if (!m_storage.data["loss"].first.isEmpty() && !m_storage.data["loss"].second.isEmpty()) {
                xs.append(m_storage.data["loss"].first[x]);
                double y = 0;
                for (int i = 0; i < x; i++) {
                    y += m_storage.data["loss"].second[i];
                }
                ys.append(y);
            }
        }
    }

    if (!xs.isEmpty() && !ys.isEmpty()) {
        // update graph dimensions
        double max_x = std::ceil(xs.last());
        double max_y = std::ceil(*std::max_element(ys.constBegin(), ys.constEnd()));
        if (x_max <= max_x) x_max = max_x + 1;
        if (y_max < max_y) y_max = max_y + 1;
    }
    widget->graph(0)->setData(xs, ys);
    widget->xAxis->setRange(0, x_max);
    widget->yAxis->setRange(0, y_max);
    widget->replot();

}
