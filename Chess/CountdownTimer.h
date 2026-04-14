#pragma once
#include "Core.h"

class countdownTimer 
{
public:
    countdownTimer();
    void setTimer(float second);
    bool timerExpired();

private:
    sf::Clock clock;     // Таймер
    sf::Time duration;   // Длительность отсчета
    float timeLeft;      // Оставшееся время в секундах 
};