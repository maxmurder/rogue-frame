#ifndef RCURSES_MANAGER
#define RCURSES_MANAGER

#include <map>
#include <ncurses.h>

namespace rcurses_manager
{
    class screen_manager
    {   
        public:
            int AddScreen(); // add new terminal screen
            void RemoveScreen(int t); //remove terminal screen by id
            screen_manager();
            ~screen_manager();
        private:
            std::map<int, SCREEN *> screens; //list of current screens
            int screenCount;
    };
};

#endif
