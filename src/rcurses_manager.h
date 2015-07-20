#ifndef RCURSES_MANAGER
#define RCURSES_MANAGER

#include <map>
#include <unordered_map>
#include <ncurses.h>

namespace rcurses_manager
{
    class screen_manager
    {   
        public:
            std::map<int, SCREEN *> screens; //map of current screens
            std::unordered_map<SCREEN *, WINDOW *> windows; //hash table of windows
            
            int AddScreen(); // add new terminal screen
            void RemoveScreen(int screen_index); //remove terminal screen by index
            WINDOW * AddWindow(int screen_index, int height, int width, int startx, int starty); //add a new window to a screen
            void RemoveWindow(WINDOW * window_pointer); //remove a window
            
            SCREEN * GetScreen(int screen_index);//get screen pointer
            SCREEN * GetScreen(WINDOW * window_pointer);//get a windows parent screen
            screen_manager();
            ~screen_manager();
    };
};

#endif
