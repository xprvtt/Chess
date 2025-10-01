#pragma once
#include "Core.h"

class countdownTimer 
{
private:
    Clock clock;         // Таймер
    Time duration;       // Длительность отсчета
    float timeLeft;      // Оставшееся время в секундах 

public:


    countdownTimer();

    void setTimer(float second);

    bool timerExpired();
};