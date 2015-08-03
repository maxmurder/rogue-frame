#ifndef R_CURSES
#define R_CURSES

#include <map>
#include <ncurses.h>

namespace r_curses
{
        class r_screen
        {
                SCREEN *_screenPointer;
                std::pair<int,int> _screenDimensions; //hight, width of screen
                
                public:
                r_screen();
                ~r_screen();
                
                static void resizeHandler(int);                
                        
                std::pair<int,int> GetScreenDimensions();
        
        };
}
#endif
