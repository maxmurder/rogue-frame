#ifndef R_TIME_H
#define R_TIME_H

namespace r_time
{
    unsigned system_time(); //returns the system time

    /* 
    * Simple time keeping class.
    */
    class RTime
    {
        public:
            void Update(); //updates the time
            unsigned CurrentTime(); //returns current time in ms at last update 
            unsigned ElapsedTime(); //returns time between last two updates
            double Delta(); //returns the delta between last two updates (fraction of a second)
            RTime();
            ~RTime(){};
            
        private:
            unsigned currentTicks = 0;
            unsigned elapsedTicks = 0;
            unsigned startTicks = 0;
    };
}

#endif

