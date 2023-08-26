#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_steps(0), m_seconds(0)
{
    ui->setupUi(this);
    setWindowTitle("15puzzle");

    m_optionsDialog = new OptionsDialog(this);
    m_gameTimer = new GameTimer(this);
    m_timerLabel = new QLabel("Steps: 0; Elapsed time: 0 seconds");
    m_pauseMessageBox = new PauseMessageBox();
    m_pauseMessageBox->setText("Game paused");
    
    
    this->statusBar()->addPermanentWidget(m_timerLabel);

    QPointer<QFrame> frame = new QFrame;
    m_puzzle = new Puzzle(3, 400, frame);
    resize(400, 400);
    setCentralWidget(frame);

    loadImage(DEFAULT_IMAGE_PATH);
    m_gameTimer->start();

    /* connects */
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onActionOpenTriggered);
    connect(ui->actionOptions, &QAction::triggered, this, &MainWindow::toggleTimer);
    connect(ui->actionOptions, &QAction::triggered, this, &MainWindow::openOptionsDialog);
    connect(m_optionsDialog, &QDialog::finished, this, &MainWindow::toggleTimer);
    connect(m_gameTimer, &GameTimer::timeUpdated, this, &MainWindow::updateStatusBar);
    connect(m_pauseMessageBox, &QMessageBox::accepted, this, &MainWindow::toggleTimer);
    connect(m_puzzle, &Puzzle::updateSteps, this, &MainWindow::updateStatusBarWithSteps);
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

void MainWindow::openOptionsDialog()
{
    m_optionsDialog->exec();
}

void MainWindow::toggleTimer() 
{
    qDebug() << "toggle " << m_gameTimer->isActive();
    if (m_gameTimer->isActive()) {
        m_gameTimer->pause();
    } else {
        m_gameTimer->start();
    }
}

void MainWindow::resetTimer() 
{
    m_gameTimer->reset();
}

void MainWindow::updateStatusBar(int seconds) 
{
    m_seconds = seconds;
    m_timerLabel->setText("Steps: " + QString::number(m_steps) 
        + "; Elapsed time: " + QString::number(m_seconds) + " seconds");
}

void MainWindow::updateStatusBarWithSteps(int steps)
{
    m_steps = steps;
    m_timerLabel->setText("Steps: " + QString::number(m_steps) 
        + "; Elapsed time: " + QString::number(m_seconds) + " seconds");
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) 
    {
        case Qt::Key_S:
        case Qt::Key_Down:
            m_puzzle->movePieceByKey(Puzzle::KEY_DOWN);
            break;
        case Qt::Key_W:
        case Qt::Key_Up:
            m_puzzle->movePieceByKey(Puzzle::KEY_UP);
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
            m_puzzle->movePieceByKey(Puzzle::KEY_LEFT);
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            m_puzzle->movePieceByKey(Puzzle::KEY_RIGHT);
            break;
        case Qt::Key_P:
            toggleTimer();
            m_pauseMessageBox->exec();
            break; 
        case Qt::Key_O:
            toggleTimer();
            openOptionsDialog();
            break;
        case Qt::Key_Z:
            if (event->modifiers() == Qt::ControlModifier) {
            }
            break;
        default:
            QMainWindow::keyPressEvent(event); 
            break;
    }
}
