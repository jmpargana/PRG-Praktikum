#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gameoflifewidget.h"

#include <QFileDialog>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_automaton() // default value from cellularautomaton(30,30)
{
    ui->setupUi(this); // creating all the widgets

    m_golWidget = new GameOfLifeWidget(this);
    m_golWidget->setMatrix(&m_automaton);
    QHBoxLayout* gameBoxLayout = new QHBoxLayout;
    gameBoxLayout->addWidget(m_golWidget);
    ui->gameBox->setLayout(gameBoxLayout);

    int cols = ui->spinBox_columns->value();
    int rows = ui->spinBox_row->value();
    m_automaton = CellularAutomaton(rows, cols); //default size from spinbox

    m_timer.setInterval(ui->spinBox_timer->value() * 1000); // get default value from spinbox
    connect(&m_timer, &QTimer::timeout,
            this, &MainWindow::onNextLife);
    m_timer.start(); // start the timer

    connect(ui->QPushButton_stop, &QPushButton::clicked,
            &m_timer, &QTimer::stop);

    connect(ui->QPushButton_start, &QPushButton::clicked,// sender and signal
            &m_timer, QOverload<>::of(&QTimer::start)); // receiver with slot

    connect(ui->QPushButton_clean_up,&QPushButton::clicked,
            this, &MainWindow::clearout);

    connect(ui->spinBox_timer, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onTimeoutChanged);

    connect(ui->spinBox_columns, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::newColumnsSize);

    connect(ui->spinBox_row, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::newRowSize);

    connect(ui->QPushButton_import_2, &QPushButton::clicked,
            this, &MainWindow::importFile);

    connect(ui->QPushButton_export_2, &QPushButton::clicked,
            this, &MainWindow::exportFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNextLife()
{
    ++m_automaton; // change data: calculate next step in game of life
    m_golWidget->update(); // tell Game of Life widget that the data changed
}

void MainWindow::clearout()
{
    int cols = m_automaton.get_cols();
    int rows = m_automaton.get_rows();
    CellularAutomaton empty{cols, rows};
    m_automaton = empty;
    m_golWidget->update();
}

void MainWindow::onTimeoutChanged(int newSeconds)
{
    m_timer.setInterval(newSeconds * 1000);
}

void MainWindow::newColumnsSize(int newColumnSize)
{
    CellularAutomaton newCa(m_automaton.get_rows(), newColumnSize);
    for (int i = 0; i < std::min(m_automaton.get_cols(), newColumnSize); i++) { // copy old value to new value
        for (int j = 0; j < m_automaton.get_rows(); ++j) {
            newCa[j][i] = m_automaton[j][i];// row->j , column->i
        }
    }
    m_automaton = newCa; // set new value equal to old value
    m_golWidget->update(); // repaint the grid
}

void MainWindow::newRowSize(int newRowSize)
{
    CellularAutomaton newCa(newRowSize, m_automaton.get_cols());
    for (int i = 0; i < std::min(m_automaton.get_rows(), newRowSize); i++) { // copy old value to new value
        for (int j = 0; j < m_automaton.get_cols(); j++) {
            newCa[i][j] = m_automaton[i][j]; // row->i, column ->j
        }
    }
    m_automaton = newCa; // set new value equal to old value
    m_golWidget->update();
}

void MainWindow::importFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose a Game of Life file");
    std::string fileNameStd = fileName.toStdString();
    std::ifstream ist{fileNameStd};
    if (!ist) {
        throw std::runtime_error("File not found");
    }
    ist >> m_automaton;
    ui->spinBox_columns->setValue(m_automaton.get_cols());
    ui->spinBox_row->setValue(m_automaton.get_rows());
    m_golWidget->update();
}

void MainWindow::exportFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Chose a file to save to");
    std::string fileNameStd = fileName.toStdString();
    std::ofstream ost{fileNameStd};
    if (!ost) {
        throw std::runtime_error("File not found");
    }
    ost << m_automaton;

}