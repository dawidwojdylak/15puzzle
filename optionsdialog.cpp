#include "optionsdialog.h"


OptionsDialog::OptionsDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("15puzzle options");

    QLabel *playerNameLabel = new QLabel("Player Name:");
    playerNameLineEdit = new QLineEdit(); 
    playerNameLineEdit->insert("Player 1");

    QLabel *gridSizeLabel = new QLabel("Side size:");
    gridSizeComboBox = new QComboBox;
    for (int size = 2; size <= 20; ++size) {
        gridSizeComboBox->addItem(QString::number(size));
    }

    saveGameStateButton = new QPushButton("Save Game State"); 
    connect(saveGameStateButton, &QPushButton::clicked, this, &OptionsDialog::saveGameStateClicked);

    loadGameStateButton = new QPushButton("Load Game State"); 
    connect(loadGameStateButton, &QPushButton::clicked, this, &OptionsDialog::loadGameStateClicked);

    QPushButton *loadImageBtn = new QPushButton("Load Image");
    connect(loadImageBtn, &QPushButton::clicked, this, &OptionsDialog::loadImageClicked);

    QLabel *rankingLabel = new QLabel("Ranking:");
    QTextEdit *rankingTextEdit = new QTextEdit();


    connect(gridSizeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OptionsDialog::gridSizeChanged);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(playerNameLabel);
    layout->addWidget(playerNameLineEdit);
    layout->addWidget(gridSizeLabel);
    layout->addWidget(gridSizeComboBox);
    layout->addWidget(saveGameStateButton);
    layout->addWidget(loadGameStateButton);
    layout->addWidget(loadImageBtn);
    layout->addWidget(rankingLabel);
    layout->addWidget(rankingTextEdit);

    setLayout(layout);
}

void OptionsDialog::playerNameChanged(const QString &text) {
    qDebug() << "playerNameChanged";
}

void OptionsDialog::saveGameStateClicked() {
    qDebug() << "saveGameStateClicked";
}

void OptionsDialog::loadGameStateClicked() {
    qDebug() << "loadGameStateClicked";
}


void OptionsDialog::gridSizeChanged(int index) {
    qDebug() << "gridSizeChanged";
    int selectedSize = gridSizeComboBox->itemText(index).toInt();
}

