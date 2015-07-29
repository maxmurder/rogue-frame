#ifndef R_CURSES
#define R_CURSES

#include <map>
#include <ncurses.h>

namespace r_curses
{
        class r_screen
        {
                SCREEN *_screenPointer;
                
                public:
                r_screen();
                ~r_screen();
        }
}
#endif
