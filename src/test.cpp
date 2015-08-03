#include <iostream>
#include <stdio.h>
#include <signal.h>
#include "r_curses.h"
using namespace r_curses;

void resizeHandler(int);

int main() {
    r_screen *screen = new r_screen();
    signal(SIGWINCH,resizeHandler);
    getch();
    delete screen;
    return 0;
}

void resizeHandler(int sig)
{
    int nh,nw;
    getmaxyx(stdscr, nh, nw);    
}
