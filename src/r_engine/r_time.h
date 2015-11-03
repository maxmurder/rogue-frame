#ifndef R_TIME_H
#define R_TIME_H

class RTime
{
    public:
        void Update();
        unsigned GetCurrentTicks();
        unsigned GetElapsedTicks();
    private:
        unsigned currentTicks = 0;
        unsigned ticksLastFrame = 0;
};

#endif

