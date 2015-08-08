#ifndef R_CURSES
#define R_CURSES

#include <vector>
#include <ncurses.h>

namespace r_curses
{
        class r_screen
        {
                SCREEN *_screenPointer;
                static std::pair<int,int> _screenDimensions; //hight, width of screen
                std::vector<WINDOW *> _windows; //list of windows on the screen
                
                static void SetScreenDimensions(int height, int width); //sets _screenDimensions
                
                public:             
                        
                std::pair<int,int> GetScreenDimensions(); //returns dimensions of the screen
                
                int AddWindow(int height,int width, int x_pos, int y_pos); //adds a window to the screen
                void RemoveWindow(int window_index); //removes window at index of _windows
                
                r_screen();
                ~r_screen();
                
                static void resizeHandler(int); //handles resizing of the screen
        };
}
#endif
