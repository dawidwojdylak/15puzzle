#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QPointer>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "user.h"
#include "puzzle.h"
#include "optionsdialog.h"
#include "gametimer.h"

#define DEFAULT_IMAGE_PATH "./img/sample1.png"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadImage();

public slots:
    void OpenUserGame();
    void SaveUserGame();

private slots:
    void onActionOpenTriggered();
    void openOptionsDialog();
    void toggleTimer();
    void resetTimer();
    void updateStatusBar(int seconds);
    void updateStatusBarWithSteps(int steps);
    void puzzleFinished();
    void restartGame();
    void changeGridSize(int size);
   
protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    struct PauseMessageBox : public QMessageBox 
    {
    protected:
        void keyPressEvent(QKeyEvent *event) override 
        {
            if (event->key() == Qt::Key_P) 
                accept();
            else QMessageBox::keyPressEvent(event);
        }
    };

    Ui::MainWindow *ui;
    QPointer<Puzzle> m_puzzle;
    QPixmap m_image;
    OptionsDialog * m_optionsDialog;
    GameTimer * m_gameTimer;
    QLabel * m_timerLabel;
    PauseMessageBox * m_pauseMessageBox;
    int m_steps;
    int m_seconds;
    QString m_imgPath;

};
#endif // MAINWINDOW_H
