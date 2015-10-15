#include "RTimer.h"
#include "SDL2/SDL.h"

void RTimer::Start()
{
    _started = true;
    _paused = false;
    
    _startTicks = SDL_GetTicks();
    _pauseTicks = 0;
}

void RTimer::Stop()
{
    _started = false;
    _paused = false;
    _startTicks = 0;
    _pauseTicks = 0;
}

void RTimer::Pause()
{
    if( _started && !_paused )
    {
        _paused = true;
        
        _pauseTicks = SDL_GetTicks() - _startTicks;
        _startTicks = 0;
    }
}

void RTimer::Unpause()
{
    if(_started && _paused)
    {
        _paused = false;
        
        _startTicks = SDL_GetTicks() - _pauseTicks;
        _pauseTicks = 0;
    }
}

uint32_t RTimer::GetTicks()
{
    uint32_t time = 0;
    
    if (_started)
    {
        if (_paused)
        {
            time = _pauseTicks;
        }
        else
        {
            time = SDL_GetTicks() - _startTicks;
        }
    }
    return time;
}

bool RTimer::IsStarted()
{
    return _started;
}

bool RTimer::IsPaused()
{
    return _paused && _started;
}

RTimer::RTimer(EntityID id) : Component(id)
{
    _startTicks = 0;
    _startTicks = 0;
    _started = false;
    _paused = false;   
}
