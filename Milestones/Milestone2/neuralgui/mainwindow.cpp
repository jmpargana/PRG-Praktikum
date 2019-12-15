#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_import, &QPushButton::clicked,
            this, &MainWindow::importdata);


}

MainWindow::~MainWindow()
{
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

}


