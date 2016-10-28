#include <chrono>
#include "r_time.h"
#include "SDL2/SDL.h"

namespace r_time
{
    typedef std::chrono::high_resolution_clock _clock;

    unsigned r_time::system_time()
    {
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epoch = ms.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();
    }

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

    RTime::RTime()
    {
        Update();
    }
}