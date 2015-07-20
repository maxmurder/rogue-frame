#include <iostream>
#include <algorithm>
#include <assert.h>
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
    //create screen and add to the screen list
    
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

SCREEN * screen_manager::GetScreen(int screen_index){
    return screens[screen_index];    
}

SCREEN * screen_manager::GetScreen(WINDOW * win){
    SCREEN *s;
    for(auto& w: windows){
        if (w.second == win){
            s = w.first;
            return s;
        }
    }
    assert (s != NULL && "Window pointer does not appear to exist.");
    return s;
}

WINDOW * screen_manager::AddWindow(int screen_index, int height, int width, int startx, int starty){
    set_term(screens[screen_index]);
    WINDOW *w = newwin(height,width,startx,starty);
    windows.insert(make_pair( screens[screen_index] , w ));
    wrefresh(w);    
    return w;
}

void screen_manager::RemoveWindow(WINDOW * win_p){
    int s = GetScreen(win_p);
    set_term(screens[s]);
    werase(win_p);
    delwin(windows[win]);
    windows[screen_index].erase(window_index);
}


