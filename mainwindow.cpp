#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("15puzzle");

    /* connects */
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onActionOpenTriggered);



    QPointer<QFrame> frame = new QFrame;
    m_puzzle = new Puzzle(3, 400, frame);
    resize(400, 400);
    setCentralWidget(frame);

    loadImage(DEFAULT_IMAGE_PATH);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage(const QString & imgPath)
{
    QPixmap img;
    img.load(imgPath);
    m_image = img;
    m_puzzle->clearPuzzle();
    m_puzzle->setup(m_image);
}

void MainWindow::onActionOpenTriggered()
{
    QString filter = "Images (*.png *.jpg *.jpeg *.bmp *.gif)";
    QString path = QFileDialog::getOpenFileName(this, "Open Image", "", filter);
    loadImage(path);
}
