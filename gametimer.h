#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <QObject>
#include <QTimer>

class GameTimer : public QObject {
    Q_OBJECT

public:
    GameTimer(QObject *parent = nullptr);

    void start();
    void pause();
    void reset();   
    int elapsedSeconds() const;
    void setElapsedSeconds(int seconds);
    bool isActive() const;

signals:
    void timeUpdated(int seconds);


private slots:
    void updateTimer();

private:
    QTimer *m_timer;
    int m_elapsedSecondsCount;
};

#endif // GAMETIMER_H