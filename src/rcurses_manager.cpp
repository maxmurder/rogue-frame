#include <iostream>
#include <vector>
#include <algorithm>
#include "rcurses_manager.h"
using namespace std;
using namespace rcurses_manager;

vector<SCREEN *> screens; //list of current terminal screens

screen_manager::screen_manager(){
    SCREEN *t = newterm(NULL,NULL,NULL);
    screens.push_back(t);
}

screen_manager::~screen_manager(){
    for (int i=screens.size()-1;i>=0;i--)
    {
        RemoveScreen(i);
    }
}

SCREEN *screen_manager::AddScreen() {
    FILE *i = new FILE;
    FILE *o = new FILE;
    i = tmpfile();
    o = tmpfile();
    SCREEN *t = newterm(NULL,i,o);
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

