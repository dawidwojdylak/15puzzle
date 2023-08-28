#include "gametimer.h"

GameTimer::GameTimer(QObject *parent) : QObject(parent), m_elapsedSecondsCount(0) 
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &GameTimer::updateTimer);
}

void GameTimer::start() 
{
    m_timer->start(1000); 
}

void GameTimer::pause() 
{
    m_timer->stop();
}

void GameTimer::reset() 
{
    m_elapsedSecondsCount = 0;
    emit timeUpdated(m_elapsedSecondsCount);
}

int GameTimer::elapsedSeconds() const
{
    return m_elapsedSecondsCount;
}

void GameTimer::setElapsedSeconds(int seconds)
{
    m_elapsedSecondsCount = seconds;
}

bool GameTimer::isActive() const
{
    return m_timer->isActive();
}

void GameTimer::updateTimer() 
{
    emit timeUpdated(++m_elapsedSecondsCount);
}
