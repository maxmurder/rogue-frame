#include <iostream>
#include <map>
#include <algorithm>
#include "rcurses_manager.h"
using namespace std;
using namespace rcurses_manager;

screen_manager::screen_manager(){
}

screen_manager::~screen_manager(){
    for (auto& s: screens){
        RemoveScreen(s.first);
    }
}

int screen_manager::AddScreen() {
    //create terminal and add to the screen list
    SCREEN *t = newterm(NULL,stdout,stdin);
    screens[++screenCount] = t;
    
    //init ncurses
    cbreak();
    noecho();
    keypad(stdscr,0);
    curs_set(0);
    clear();
    
    return screenCount;
}

void screen_manager::RemoveScreen(int t){
    set_term(screens[t]);
    endwin();
    screens.erase(t);
}


