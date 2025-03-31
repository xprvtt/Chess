#pragma once
#include "Core.h"

class CountdownTimer 
{
private:
    Clock clock;         // ������
    Time duration;       // ������������ �������
    float timeLeft;      // ���������� ����� � ��������

public:


    CountdownTimer();

    void SetTimer(float second);

    bool TimerExpired();
};