#ifndef RCURSES-MANAGER
#define RCURSES-MANAGER

namespace rcurses-manager
{
        class screen-manager
        {
                vector<SCREEN *> screens; //list of current terminal screens
                
                public:
                        int screen-manager();
                        void ~screen-manager();
                        
                        SCREEN * AddScreen(); // add new terminal screen
                        void RemoveScreen(SCREEN * t); //remove terminal screen by pointer
                        void RemoveScreen(int t); //remove terminal screen by index
                        
                        vector<SCREEN *> GetScreens(); //returns screens list    
        };
};

#endif
