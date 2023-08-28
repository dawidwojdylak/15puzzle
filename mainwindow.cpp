#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_steps(0), m_seconds(0),
    m_imgPath(DEFAULT_IMAGE_PATH)
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

    loadImage();
    m_gameTimer->start();

    /* connects */
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onActionOpenTriggered);
    connect(ui->actionOptions, &QAction::triggered, this, &MainWindow::toggleTimer);
    connect(ui->actionOptions, &QAction::triggered, this, &MainWindow::openOptionsDialog);
    connect(ui->actionRestart, &QAction::triggered, this, &MainWindow::restartGame);
    connect(m_optionsDialog, &QDialog::finished, this, &MainWindow::toggleTimer);
    connect(m_optionsDialog, &OptionsDialog::saveGameState, this, &MainWindow::SaveUserGame);
    connect(m_optionsDialog, &OptionsDialog::loadGameState, this, &MainWindow::OpenUserGame);
    connect(m_gameTimer, &GameTimer::timeUpdated, this, &MainWindow::updateStatusBar);
    connect(m_pauseMessageBox, &QMessageBox::accepted, this, &MainWindow::toggleTimer);
    connect(m_puzzle, &Puzzle::updateSteps, this, &MainWindow::updateStatusBarWithSteps);
    connect(m_puzzle, &Puzzle::puzzleFinished, this, &MainWindow::puzzleFinished);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage()
{
    QPixmap img;
    img.load(m_imgPath);
    
    // crop the image to square
    int sideLength = qMin(img.width(), img.height());
    QPixmap imgSqr(sideLength, sideLength);

    QPainter painter(&imgSqr);
    painter.drawImage((sideLength - img.width()) / 2, (sideLength - img.height()) / 2, img.toImage());

    m_image = imgSqr;
    m_puzzle->clearPuzzle();
    m_gameTimer->reset();
    m_puzzle->setup(m_image);
}

void MainWindow::OpenUserGame()
{
    QString filter = "(*.csv)";
    QString path = QFileDialog::getOpenFileName(this, "Open saved game", "", filter);
    QFile file(path);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) 
    {
        QTextStream stream(&file);
        QString line;
        while (!stream.atEnd()) 
        {
            line = stream.readLine();
        }
        
        QStringList fields = line.split(',');

        if (fields.size() >= 6) 
        {
            QVector<std::tuple<int, int>> history;

            QString playerName = fields[0];
            QString dateTime = fields[1];
            m_imgPath = fields[2];
            int elapsedSeconds = fields[3].toInt();
            int userSteps = fields[4].toInt();
            for (int i = 5; i < fields.size(); i++)
            {
                QStringList historyItem = fields[i].split(':');
                if (historyItem.size() == 2) 
                {
                    int first = historyItem[0].toInt();
                    int second = historyItem[1].toInt();
                    qDebug() << first << ", , " << second;
                    history.append(std::make_tuple(first, second));
                }
            }

            m_optionsDialog->setPlayerName(playerName);
            m_gameTimer->setElapsedSeconds(elapsedSeconds);
            m_puzzle->setUserSteps(userSteps);
            updateStatusBarWithSteps(userSteps);
            m_puzzle->setHistory(history);

            m_puzzle->setShuffleSteps(0u);
            loadImage();
            m_puzzle->setShuffleSteps(SHUFFLE_STEPS);
            m_puzzle->replaySteps();

        }

        file.close();
    }
}

void MainWindow::SaveUserGame()
{
    QString fileName = m_optionsDialog->getPlayerName() + ".csv";
    fileName.replace(' ', '_');

    
    // Get current date and time
    QDateTime dateTime = QDateTime::currentDateTime();
    QString formattedDateTime = dateTime.toString("dd-MM-yyyy hh:mm:ss");

    QFile file(fileName);

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);

        // Write data to CSV format
        stream << m_optionsDialog->getPlayerName() << ","
               << formattedDateTime << ","
               << m_imgPath << ","
               << m_gameTimer->elapsedSeconds() << ","
               << m_puzzle->getUserSteps() << ",";

        for (const auto& move : m_puzzle->getHistory()) {
            stream << std::get<0>(move) << ":" << std::get<1>(move) << ",";
        }

        stream << "\n";

        file.close();

        QMessageBox msgBox;
        msgBox.setText("Game saved as " + m_optionsDialog->getPlayerName() + ".csv");
        msgBox.exec();
    }  
}


void MainWindow::onActionOpenTriggered()
{
    QString filter = "Images (*.png *.jpg *.jpeg)";
    m_imgPath = QFileDialog::getOpenFileName(this, "Open Image", "", filter);
    loadImage();
}

void MainWindow::openOptionsDialog()
{
    m_optionsDialog->exec();
}

void MainWindow::toggleTimer() 
{
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
    m_steps = m_puzzle->getUserSteps();
    m_timerLabel->setText("Steps: " + QString::number(m_steps) 
        + "; Elapsed time: " + QString::number(m_seconds) + " seconds");
}

void MainWindow::puzzleFinished()
{
    QMessageBox msgBox;
    msgBox.setText("Congratulations, " + m_optionsDialog->getPlayerName() + "!");
    msgBox.exec();
}

void MainWindow::restartGame()
{
    m_puzzle->clearPuzzle();
    resetTimer();
    updateStatusBarWithSteps(0);
    loadImage();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) 
    {
        case Qt::Key_S:
        case Qt::Key_Down:
            if (event->modifiers() == Qt::ControlModifier) 
                SaveUserGame();
            else
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
            if (event->modifiers() == Qt::ControlModifier) 
                m_puzzle->undo();
            break;
        default:
            QMainWindow::keyPressEvent(event); 
            break;
    }
}
