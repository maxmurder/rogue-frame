#ifndef RCURSESMANAGER
#define RCURSESMANAGER

namespace rcurses_manager
{
        class screen_manager
        {
                vector<SCREEN *> screens; //list of current terminal screens
                
                public:
                        int screen_manager();
                        void ~screen_manager();
                        
                        SCREEN * AddScreen(); // add new terminal screen
                        void RemoveScreen(SCREEN * t); //remove terminal screen by pointer
                        void RemoveScreen(int t); //remove terminal screen by index
                        
                        vector<SCREEN *> GetScreens(); //returns screens list    
        };
};

#endif
