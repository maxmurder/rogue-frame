#ifndef RTIMER_H
#define TTIMER_H

#include <iostream>
#include "r_entity/r_component.h"

class RTimer : public Component
{
    public:
        void Start();
        void Stop();
        void Pause();
        void Unpause();
        
        uint32_t GetTicks();
        
        bool IsStarted();
        bool IsPaused();
        
        RTimer();
        
    private:
        uint32_t _startTicks;
        uint32_t _pauseTicks;
        
        bool _paused;
        bool _started;
};
COMPONENT_REGISTER(RTimer, "RTimer");
#endif
