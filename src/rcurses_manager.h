#ifndef RCURSES_MANAGER
#define RCURSES_MANAGER

#include <map>
#include <ncurses.h>

namespace rcurses_manager
{

    //std::map<int, SCREEN *> screens; //map of current screens

    class screen_manager
    {   
        public:
            std::map<int, SCREEN *> screens; //map of current screens
            int AddScreen(); // add new terminal screen
            void RemoveScreen(int screen_index); //remove terminal screen by index
            SCREEN * GetScreen(int screen_index);//get screen pointer
            screen_manager();
            ~screen_manager();
    };
    class element_manager
    {
        public:
            int AddWindow(int screen_index, int height, int width, int startx, int starty); //add a new window to a screen
            void RemoveWindow(int screen_index, int window_index); //remove a window
            //void RefreshWindow(int window_index);
            //~element_manager();
            std::map<int, WINDOW *> windows;
    };
};

#endif
