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
    
    // crop the image to square
    int sideLength = qMin(img.width(), img.height());
    QPixmap imgSqr(sideLength, sideLength);

    QPainter painter(&imgSqr);
    painter.drawImage((sideLength - img.width()) / 2, (sideLength - img.height()) / 2, img.toImage());

    m_image = imgSqr;
    m_puzzle->clearPuzzle();
    m_puzzle->setup(m_image);
}

void MainWindow::onActionOpenTriggered()
{
    QString filter = "Images (*.png *.jpg *.jpeg *.bmp *.gif)";
    QString path = QFileDialog::getOpenFileName(this, "Open Image", "", filter);
    loadImage(path);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) 
    {
        case Qt::Key_Down:
            m_puzzle->movePieceByKey(Puzzle::KEY_DOWN);
            break;
        case Qt::Key_Up:
            m_puzzle->movePieceByKey(Puzzle::KEY_UP);
            break;
        case Qt::Key_Left:
            m_puzzle->movePieceByKey(Puzzle::KEY_LEFT);
            break;
        case Qt::Key_Right:
            m_puzzle->movePieceByKey(Puzzle::KEY_RIGHT);
            break;
        default:
            QMainWindow::keyPressEvent(event); 
            break;
    }
}