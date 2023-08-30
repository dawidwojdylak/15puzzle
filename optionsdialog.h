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

    inline QString getPlayerName() const { return m_playerNameLineEdit->text(); }
    inline void setPlayerName(QString name) { m_playerNameLineEdit->setText(name); }

signals:
    void saveGameState();
    void loadGameState();
    void changeGridSize(int size);
    void numbersCheckBoxChecked(bool checked);
    void loadImageClicked();

private slots:
    void playerNameChanged(const QString &text); 
    void saveGameStateClicked(); 
    void loadGameStateClicked(); 
    void gridSizeChanged(int index); 
    void onLoadImageClicked();


private:
    QLineEdit *m_playerNameLineEdit;
    QPushButton *m_saveGameStateButton;
    QPushButton *m_loadGameStateButton;
    QComboBox *m_gridSizeComboBox;
    QCheckBox *m_numbersCheckBox;
};

#endif // OPTIONSDIALOG_H
