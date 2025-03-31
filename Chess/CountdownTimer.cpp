

#include "CountdownTimer.h"

CountdownTimer::CountdownTimer()
{
    duration = seconds(0.0f);
    timeLeft = 0.0f;
    clock.restart();
}

void CountdownTimer::SetTimer(float second)
{
    duration = seconds(second);
    timeLeft = second;
    clock.restart();
}

bool CountdownTimer::TimerExpired() 
{
    float elapsedTime = clock.getElapsedTime().asSeconds();
    timeLeft = duration.asSeconds() - elapsedTime;

    if (timeLeft <= 0) {
        return true;
    }
    return false;
}