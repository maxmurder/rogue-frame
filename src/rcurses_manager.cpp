#include <iostream>
#include <vector>
#include <ncurses.h>
#include "rcurses_manager.h"
using namespace std;
using namespace rcurses_manager;

//vector<SCREEN *> screen_manager::screens;

screen_manager::screen_manager(){
}

screen_manager::~screen_manager(){
        for (unsigned int i=0;i<screens.size();i++)
        {
                RemoveScreen(i);
        }
}

SCREEN * screen_manager::AddScreen() {
        SCREEN * t = newterm();
        screens.push_back(t);
        return t;
}

void screen_manager::RemoveScreen(SCREEN * t){
        set_term(t);
        endwin();
        screens.erase(find(screens.begin(), screens.end(), t);
}

void screen_manager::RemoveScreen(int t){
        set_term(screens[t]);
        endwin();
        screens.erase(t);
}

vector<SCREEN *> screen_manager::GetScreens(){
        return screens;
}

