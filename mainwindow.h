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

    void loadImage(const QString & imgPath);

private slots:
    void onActionOpenTriggered();
    void openOptionsDialog();
    void toggleTimer();
    void resetTimer();
    void updateStatusBar(int seconds);

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

};
#endif // MAINWINDOW_H
