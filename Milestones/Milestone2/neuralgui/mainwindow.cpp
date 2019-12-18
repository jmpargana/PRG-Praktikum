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
    // needs to match combo box item position
    const int xSquareOption = 0;
    const int xPowerOfThreeOption = 1;
    ui->mainGraph->xAxis->setLabel("x");
    ui->mainGraph->yAxis->setLabel("y");
    ui->mainGraph->xAxis->setRange(-5, 5);
    double y_max = 1;
    double x_max = 5;
    QVector<double> xs, ys;
    if (ui->comboBox_draw->currentIndex() == xSquareOption) {
        ui->mainGraph->xAxis->setLabel("epoch");
        ui->mainGraph->yAxis->setLabel("time [s]");
        for (int x = 0; x <= m_storage.data["time"].first.size(); x++) {
//        for (double x = -5; x <= 5; x += 10.0 / 100.0) {
//            xs.append(x);
//            ys.append(x * x);
            xs.append(m_storage.data["time"].first);
            ys.append(m_storage.data["time"].second);
        }
    } else if (ui->comboBox_draw->currentIndex() == xPowerOfThreeOption) {
        ui->mainGraph->xAxis->setLabel("epoch");
        ui->mainGraph->yAxis->setLabel("loss");
//        QVector<double> xs, ys;
        for (int x = 0; x <= m_storage.data["loss"].first.size(); x++) {
//        for (double x = -5; x <= 5; x += 10.0 / 100.0) {
//            xs.append(x);
//            ys.append(x * x * x);
            xs.append(m_storage.data["loss"].first);
            ys.append(m_storage.data["loss"].second);
        }
        ui->mainGraph->yAxis->setRange(-5*5*5, 5*5*5);
    }
    if (!xs.isEmpty() && !ys.isEmpty()) {
        // update graph dimensions
        double max_x = std::ceil(xs.last());
        double max_y = std::ceil(*std::max_element(ys.constBegin(), ys.constEnd()));
        if (x_max <= max_x) x_max = max_x + 1;
        if (y_max < max_y) y_max = max_y + 1;
    }
    ui->mainGraph->graph(0)->setData(xs, ys);
    ui->mainGraph->xAxis->setRange(0, x_max);
    ui->mainGraph->yAxis->setRange(0, y_max);
    ui->mainGraph->replot();
//    double testy = m_storage.data["time"].first[0];
//    std::cout << testy << std::endl;
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
