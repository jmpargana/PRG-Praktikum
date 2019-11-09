#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "gameoflifewidget.h"

#include "../code/include/cellular_automaton.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow // empty shell
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNextLife();
    void clearout();
    void onTimeoutChanged(int newSeconds);
    void newColumnsSize(int newColumnSize);
    void newRowSize(int newRowSize);
    void importFile();
    void exportFile();

private:
    Ui::MainWindow *ui; // contains all widgets // properties of main window
    CellularAutomaton m_automaton;//object of class cellularautomaton
    GameOfLifeWidget *m_golWidget;
    QTimer m_timer;
};
#endif // MAINWINDOW_H
