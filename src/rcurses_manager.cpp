#include <iostream>
#include <vector>
#include <ncurses.h>
#include "rcurses_manager.h"
using namespace std;

namespace rcurses_manager 
{
        class screen_manager
        {
                vector<SCREEN *> screens;
                
                public:
                int screen_manager(){
                }
                
                void ~screen_manager(){
                        for (i=0;i<screens.size();i++)
                        {
                                RemoveScreen(i);
                        }
                }
                
                SCREEN * AddScreen() {
                        t = newterm();
                        screens.push_back(t);
                        return t;
                }
                
                void RemoveScreen(SCREEN * t){
                        set_term(t);
                        endwin();
                        screens.erase(find(screens.begin(), screens.end(), t);
                }
                
                void RemoveScreen(int t){
                        set_term(screens[t]);
                        endwin();
                        screens.erase(t);
                }
                
                vector<SCREEN *> GetScreens(){
                        return screens;
                }
        }
}
