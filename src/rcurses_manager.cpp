#include <iostream>
#include <vector>
#include <algorithm>
#include "rcurses_manager.h"
using namespace std;
using namespace rcurses_manager;

screen_manager::screen_manager(){
}

screen_manager::~screen_manager(){
    for (int i=screens.size()-1;i>=0;i--)
    {
        RemoveScreen(i);
    }
}

SCREEN *screen_manager::AddScreen() {
    SCREEN *t = newterm(NULL,stdout,stdin);
    cbreak();
    noecho();
    keypad();
    curs_set(0);
    clear();
    screens.push_back(t);
    
    return t;
}

void screen_manager::RemoveScreen(SCREEN * t){
    set_term(t);
    endwin();
    screens.erase(find(screens.begin(), screens.end(), t));
}

void screen_manager::RemoveScreen(int t){
    set_term(screens[t]);
    endwin();
    screens.erase(screens.begin()+t);
}

vector<SCREEN *> screen_manager::GetScreens(){
    return screens;
}

