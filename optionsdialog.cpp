#include "optionsdialog.h"


OptionsDialog::OptionsDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("15puzzle options");

    QLabel *m_playerNameLabel = new QLabel("Player Name:");
    m_playerNameLineEdit = new QLineEdit();
    m_playerNameLineEdit->insert("Player 1");

    QLabel *gridSizeLabel = new QLabel("Side size:");
    m_gridSizeComboBox = new QComboBox;
    for (int size = 2; size <= 20; ++size) {
        m_gridSizeComboBox->addItem(QString::number(size));
    }

    m_saveGameStateButton = new QPushButton("Save Game State"); 
    connect(m_saveGameStateButton, &QPushButton::clicked, this, &OptionsDialog::saveGameStateClicked);

    m_loadGameStateButton = new QPushButton("Load Game State"); 
    connect(m_loadGameStateButton, &QPushButton::clicked, this, &OptionsDialog::loadGameStateClicked);

    QPushButton *loadImageBtn = new QPushButton("Load Image");
    // connect(loadImageBtn, &QPushButton::clicked, this, &OptionsDialog::loadImageClicked);

    QLabel *rankingLabel = new QLabel("Ranking:");
    QTextEdit *rankingTextEdit = new QTextEdit();


    connect(m_gridSizeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OptionsDialog::gridSizeChanged);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_playerNameLineEdit);
    layout->addWidget(m_playerNameLineEdit);
    layout->addWidget(gridSizeLabel);
    layout->addWidget(m_gridSizeComboBox);
    layout->addWidget(m_saveGameStateButton);
    layout->addWidget(m_loadGameStateButton);
    layout->addWidget(loadImageBtn);
    layout->addWidget(rankingLabel);
    layout->addWidget(rankingTextEdit);

    setLayout(layout);
}

void OptionsDialog::playerNameChanged(const QString &text) 
{
    qDebug() << "playerNameChanged";
}

void OptionsDialog::saveGameStateClicked() 
{
    emit saveGameState();
}

void OptionsDialog::loadGameStateClicked() 
{
    emit loadGameState();
}


void OptionsDialog::gridSizeChanged(int index) 
{
    qDebug() << "gridSizeChanged";
    int selectedSize = m_gridSizeComboBox->itemText(index).toInt();
}

