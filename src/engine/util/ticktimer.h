#ifndef TICKTIMER_H
#define TICKTIMER_H

class TickTimer
{
public:
    TickTimer(float secondsUntilTrue, bool allowOverflow);

    void tick(float secondsPassed);
    bool isTime();
    bool isTime(float secondsPassed);

    void setSecondsUntilTrue(float secondsUntilTrue);
    void reset();

private:
    float m_secondsUntilTrue;
    const bool m_allowOverflow;
    float m_currentTime;
};

#endif // TICKTIMER_H
