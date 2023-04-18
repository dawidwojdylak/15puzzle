#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("15puzzle");

    QPointer<QFrame> frame = new QFrame;
    QPointer<QHBoxLayout> frameLayout = new QHBoxLayout(frame);

    m_puzzle = new Puzzle();

    frameLayout->addWidget(m_puzzle);

    setCentralWidget(frame);
}

MainWindow::~MainWindow()
{
    delete ui;
}

