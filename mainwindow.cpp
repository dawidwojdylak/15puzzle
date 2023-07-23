#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("15puzzle");

    QPointer<QFrame> frame = new QFrame;
//    QPointer<QHBoxLayout> frameLayout = new QHBoxLayout(frame);

    m_puzzle = new Puzzle(3, 400, frame);

    resize(400, 400);
//    frameLayout->addWidget(m_puzzle);

    setCentralWidget(frame);

    loadImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage()
{
    QPixmap img;
    img.load("./img/sample1.png");
    m_image = img;
    m_puzzle->setup(m_image);
}

