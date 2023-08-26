#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QPointer>
#include <QHBoxLayout>
#include "user.h"
#include "puzzle.h"
#include "optionsdialog.h"


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

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    QPointer<Puzzle> m_puzzle;
    QPixmap m_image;
    OptionsDialog * m_optionsDialog;
};
#endif // MAINWINDOW_H
