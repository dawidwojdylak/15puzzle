#include "gametimer.h"

GameTimer::GameTimer(QObject *parent) : QObject(parent), elapsedSecondsCount(0) 
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
    elapsedSecondsCount = 0;
    emit timeUpdated(elapsedSecondsCount);
}

int GameTimer::elapsedSeconds() const
{
    return elapsedSecondsCount;
}

bool GameTimer::isActive() const
{
    return m_timer->isActive();
}

void GameTimer::updateTimer() 
{
    elapsedSecondsCount++;
    emit timeUpdated(elapsedSecondsCount);
}
