#pragma once
#include "Core.h"

class CountdownTimer 
{
private:
    Clock clock;         // Таймер
    Time duration;       // Длительность отсчета
    float timeLeft;      // Оставшееся время в секундах

public:


    CountdownTimer();

    void SetTimer(float second);

    bool TimerExpired();
};