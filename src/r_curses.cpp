#include <iostream>
#include <algorithm>
#include "r_curses.h"

using namespace std;
using namespace r_curses;

pair<int,int> r_screen::GetScreenDimensions(){
    return _screenDimensions;
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
    int nh,nw;
    getmaxyx(stdscr, nh, nw);    
}

