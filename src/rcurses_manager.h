#ifndef RCURSESMANAGER
#define RCURSESMANAGER

#include <vector>

namespace rcurses_manager
{
        class screen_manager
        {
                std::vector<SCREEN *> screens; //list of current terminal screens
                
                public:
                        screen_manager();
                        ~screen_manager();
                        
                        SCREEN * AddScreen(); // add new terminal screen
                        void RemoveScreen(SCREEN * t); //remove terminal screen by pointer
                        void RemoveScreen(int t); //remove terminal screen by index
                        
                        std::vector<SCREEN *> GetScreens(); //returns screens list    
        };
};

#endif
