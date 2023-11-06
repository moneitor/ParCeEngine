#include "Timer.h"
#include <SDL2/SDL.h>

Timer* Timer::Instance()
{
    static Timer* timerObject = new Timer();
	return timerObject;
}

Timer::Timer()
:m_dt{0.0f},
m_lastTime{0.0f}
{

}

void Timer::Tick()
{
    m_dt = (SDL_GetTicks() - m_lastTime) * (TARGET_FPS/1000.0f);

    if(m_dt > TARGET_DELTATIME)
    {
        m_dt = TARGET_DELTATIME;
    }

    m_lastTime = SDL_GetTicks();
}

float Timer::GetDeltaTime()
{
    return m_dt;
}

float Timer::GetCurrentTime()
{
    return m_lastTime;
}
