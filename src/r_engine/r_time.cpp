#include "r_time.h"
#include "SDL2/SDL.h"

void RTime::Update()
{
    unsigned actual = SDL_GetTicks();
    ticksLastFrame = actual - currentTicks;
    currentTicks = actual;
}

unsigned RTime::GetCurrentTicks()
{
    return currentTicks;
}

unsigned RTime::GetElapsedTicks()
{
    return ticksLastFrame;
}
