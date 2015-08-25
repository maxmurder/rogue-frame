#include <iostream>
#include <algorithm>
#include "r_curses.h"

using namespace std;
using namespace r_curses;

pair <int,int> r_screen::_screenDimensions = make_pair(0,0);

pair<int,int> r_screen::GetScreenDimensions(){
    return _screenDimensions;
}

SCREEN *r_screen::GetScreenPointer(){
    return _screenPointer;
}

void r_screen::SetScreenDimensions(int height, int width){
    _screenDimensions.first = height;
    _screenDimensions.second = width;
}

r_screen::r_screen(){
    _screenPointer = newterm(NULL,stdout,stdin);
    //init ncurses
    cbreak();
    noecho();
    keypad(stdscr,0);
    curs_set(0);
    getmaxyx(stdscr,_screenDimensions.first,_screenDimensions.second);
    clear();
}

r_screen::~r_screen(){
    set_term(_screenPointer);
    endwin();
}

void r_screen::resizeHandler(int sig)
{
    getmaxyx(stdscr, _screenDimensions.first, _screenDimensions.second); 
}

r_window::r_window(r_screen *screen, int height,int width, int x_pos, int y_pos) {
    _screen = screen;
    set_term(_screen->GetScreenPointer());
    pair<int,int> dims = _screen->GetScreenDimensions();
    
    //if window wont fit on screen, resize
    if( x_pos + width > dims.second ){
        width -= width - dims.second + x_pos;
    }
    if( y_pos + height > dims.first ){
        height -= height - dims.first + y_pos;
    }
    //add window
    _windowPointer = newwin(height, width, x_pos, y_pos);
    _dimensions = make_pair(height,width);
}
