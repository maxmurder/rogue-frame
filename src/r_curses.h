#ifndef R_CURSES
#define R_CURSES

#include <map>
#include <vector>
#include <ncurses.h>

namespace r_curses
{
    class r_screen
    {
        SCREEN *_screenPointer;
        static std::pair<int,int> _screenDimensions; //hight, width of screen
        
        static void SetScreenDimensions(int height, int width); //sets _screenDimensions
        
        public:             
                
        std::pair<int,int> GetScreenDimensions(); //returns dimensions of the screen
        SCREEN * GetScreenPointer();
        
        r_screen();
        ~r_screen();
        
        static void resizeHandler(int); //handles resizing of the screen
    };
    class r_window
    {
        WINDOW * _windowPointer;
        int _index;
        r_screen *_screen;
        std::pair<int,int> _dimensions;
        std::vector<std::vector<char>> _buffer;
        
        
        public:
        r_window(r_screen *screen, int height,int width, int x_pos, int y_pos);
        ~r_window();
    };
}
#endif
