#include "r_time.h"
#include "SDL2/SDL.h"

unsigned currentTicks = 0;
unsigned ticksLastFrame = 0;


void r_time::Update()
{
    unsigned actual = SDL_GetTicks();
    ticksLastFrame = actual - currentTicks;
    currentTicks = actual;
}

unsigned r_time::GetCurrentTicks()
{
    return currentTicks;
}

unsigned r_time::GetLastTicks()
{
    return ticksLastFrame;
}
