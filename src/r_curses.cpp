#include <iostream>
#include <algorithm>
#include "r_curses.h"

using namespace std;
using namespace r_curses;

pair <int,int> r_screen::_screenDimensions = make_pair(0,0);

pair<int,int> r_screen::GetScreenDimensions(){
    return _screenDimensions;
}

void r_screen::SetScreenDimensions(int height, int width){
    _screenDimensions.first = height;
    _screenDimensions.second = width;
}

int r_screen::AddWindow(int height, int width, int x_pos, int y_pos){
    static int w;
    w++;
    set_term(_screenPointer);
    //if window wont fit on screen, resize
    if( x_pos + width > _screenDimensions.second ){
        width -= width - _screenDimensions.second + x_pos;
    }
    if( y_pos + height > _screenDimensions.first ){
        height -= height - _screenDimensions.first + y_pos;
    }
    //add window
    WINDOW *win = newwin(height, width, x_pos, y_pos);   
    _windows[w] = win;
    return w;
}

void r_screen::RemoveWindow(int window_key){
    set_term(_screenPointer);
    werase(_windows.at(window_key));
    delwin(_windows.at(window_key));
    _windows.erase(window_key);
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

