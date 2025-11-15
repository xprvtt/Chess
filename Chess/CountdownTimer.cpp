

#include "CountdownTimer.h"

countdownTimer::countdownTimer()
{
    duration = sf::seconds(0.0f);
    timeLeft = 0.0f;
    clock.restart();
}

void countdownTimer::setTimer(float second)
{
    duration = sf::seconds(second);
    timeLeft = second;
    clock.restart();
}
 
bool countdownTimer::timerExpired() 
{
    float elapsedTime = clock.getElapsedTime().asSeconds();
    timeLeft = duration.asSeconds() - elapsedTime;

    if (timeLeft <= 0) 
    {
        return true;
    }

    return false;
}