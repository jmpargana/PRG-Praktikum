#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "gameoflifewidget.h"
#include "visualcryptpicturewidget.h"

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
    void onVisualCryptModeChanged(int index);
// VisCrypt
// encryption screen
    void enc_importOriginalFile();
    void enc_importKeyFile();
    void enc_encrypt();
    void enc_save();
    void enc_generateRandomKey();
    void enc_saveRandomkeyPic();

// decryption screen
    void dec_importEncryptedPicture();
    void dec_importKeyPicture();
    void dec_decrypt();
    void dec_save();


private:
    Ui::MainWindow *ui; // contains all widgets // properties of main window
    CellularAutomaton m_automaton;//object of class cellularautomaton
    GameOfLifeWidget *m_golWidget;
    QTimer m_timer;

    // VisCrypt
    // encryption screen
    NBild m_encOrigPicture;
    CBild m_encKeyPicture;
    CBild m_encEncryptedPicture;
    VisualCryptPictureWidget *m_encOrigPictureWidget;
    VisualCryptPictureWidget *m_encLoadKeyWidget;
    VisualCryptPictureWidget *m_encEncryptedWidget;
    // decryption screen
    CBild m_decEncryptedPicture;
    CBild m_decKeyPicture;
    NBild m_decDecryptedPicture;
    VisualCryptPictureWidget *m_decEncryptedPictureWidget;
    VisualCryptPictureWidget *m_decKeyPictureWidget;
    VisualCryptPictureWidget *m_decDecryptedPictureWidget;


};
#endif // MAINWINDOW_H
