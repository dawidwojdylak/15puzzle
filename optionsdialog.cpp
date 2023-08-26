#include "optionsdialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QTextEdit>
#include <QVBoxLayout>

OptionsDialog::OptionsDialog(QWidget *parent) : QDialog(parent) {
        setWindowTitle("15puzzle options");

        QLabel *playerNameLabel = new QLabel("Player Name:");
        QLineEdit *playerNameLineEdit = new QLineEdit;

        QPushButton *saveGameStateButton = new QPushButton("Save Game State");
        QPushButton *loadGameStateButton = new QPushButton("Load Game State");

        QPushButton *loadImageBtn = new QPushButton("Load Image");

        QCheckBox *pauseGameCheckBox = new QCheckBox("Pause Game");

        QLabel *rankingLabel = new QLabel("Ranking:");
        QTextEdit *rankingTextEdit = new QTextEdit;

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(playerNameLabel);
        layout->addWidget(playerNameLineEdit);
        layout->addWidget(saveGameStateButton);
        layout->addWidget(loadGameStateButton);
        layout->addWidget(loadImageBtn);
        layout->addWidget(pauseGameCheckBox);
        layout->addWidget(rankingLabel);
        layout->addWidget(rankingTextEdit);

        setLayout(layout);

        connect(loadImageBtn, &QPushButton::clicked, this, &OptionsDialog::loadImageClicked);
    }
