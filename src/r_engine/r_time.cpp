#include "r_time.h"
#include "SDL2/SDL.h"

void RTime::Update()
{
    startTicks = currentTicks;
    double actual = SDL_GetTicks();
    elapsedTicks = actual - currentTicks;
    currentTicks = actual;
}

unsigned RTime::CurrentTime()
{
    return currentTicks;
}

unsigned RTime::ElapsedTime()
{
    return elapsedTicks;
}

double RTime::Delta()
{
    return (currentTicks - startTicks) * 0.001;
}
