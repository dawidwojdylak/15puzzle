#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>

class OptionsDialog : public QDialog
{
    Q_OBJECT
public:
    OptionsDialog(QWidget *parent = nullptr);

signals:
    void loadImageRequested();

private slots:
    void loadImageClicked() {
        emit loadImageRequested();
    }

    void playerNameChanged(const QString &text); 
    void saveGameStateClicked(); 
    void loadGameStateClicked(); 
    void gridSizeChanged(int index); 

private:
    QLineEdit *playerNameLineEdit;
    QPushButton *saveGameStateButton;
    QPushButton *loadGameStateButton;
    QComboBox *gridSizeComboBox;
};

#endif // OPTIONSDIALOG_H
