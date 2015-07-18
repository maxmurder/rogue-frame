#ifndef RCURSES_MANAGER
#define RCURSES_MANAGER

#include <vector>
#include <ncurses.h>

namespace rcurses_manager
{
    class screen_manager
    {   
        screen_manager();
        ~screen_manager();
        public:
            SCREEN *AddScreen(); // add new terminal screen
            void RemoveScreen(SCREEN * t); //remove terminal screen by pointer
            void RemoveScreen(int t); //remove terminal screen by index
            
            std::vector<SCREEN *> GetScreens(); //returns screens list    
    };
};

#endif
