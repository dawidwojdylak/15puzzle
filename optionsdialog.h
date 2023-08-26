#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

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

signals:

};

#endif // OPTIONSDIALOG_H