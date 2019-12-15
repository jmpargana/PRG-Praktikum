#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void importdata();
    void events_for_training();
    void events_for_test();
    void quantity_of_epochs();
    void batch_size();
    void neural_net_mode();
    void draw();
    void progress();
};
#endif // MAINWINDOW_H
