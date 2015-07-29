#include <iostream>
#include <algorithm>
#include "r_curses.h"

using namespace std;
using namespace r_curses;

r_screen::r_screen(){
    _screenPointer = newterm(NULL,stdout,stdin);
    //init ncurses
    cbreak();
    noecho();
    keypad(stdscr,0);
    curs_set(0);
    clear();
}

r_screen::~r_screen(){
    set_term(_screenPointer);
    endwin();
}

