#include <iostream>
#include <map>
#include <algorithm>
#include "rcurses_manager.h"
using namespace std;
using namespace rcurses_manager;

screen_manager::screen_manager(){}
screen_manager::~screen_manager(){
    for (auto& s: screens){
        RemoveScreen(s.first);
    }
}

int screen_manager::AddScreen() {
    //create terminal and add to the screen list
    
    static int screenCount;
    int i = screenCount;
    SCREEN *s = newterm(NULL,stdout,stdin);
    screens[i] = s;
    screenCount++;
    
    //init ncurses
    cbreak();
    noecho();
    keypad(stdscr,0);
    curs_set(0);
    clear();
    
    return i;
}

void screen_manager::RemoveScreen(int s){
    set_term(screens[s]);
    endwin();
    screens.erase(s);
}

SCREEN * GetScreen(int screen_index){
    return screens[screen_index];    
}

/*element_manager::~element_manager(){
    for (auto& w: windows){
        int i = w.first;
        RemoveWindow(i);
    }
}*/

int element_manager::AddWindow(int screen_index, int height, int width, int startx, int starty){
    static int windowCount;
    int i = windowCount;
    set_term(screens[screen_index]);
    WINDOW *w = newwin(height,width,startx,starty);
    windows[i] = w;
    wrefresh(w);    
    return i;
}
void element_manager::RemoveWindow(int screen_index, int window_index){
    set_term(screens[screen_index]);
    werase(windows[window_index]);
    delwin(windows[window_index]);
    windows.erase(window_index);
}


