#pragma once

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;

class Timer
{
public:
    static Timer* Instance();
    void Tick();

    float GetDeltaTime();
    float GetCurrentTime();
    

private:
    Timer();
	Timer(const Timer&);
	Timer& operator=(const Timer&);

    float m_dt;
    float m_lastTime;
};