#include <iostream>
#include <stdio.h>
#include <signal.h>
#include "r_curses.h"
using namespace r_curses;

int main() {
    r_screen *screen = new r_screen();
    signal(SIGWINCH,screen->resizeHandler);
    int w = screen->AddWindow(0,0,10,10);
    int w1 = screen->AddWindow(10,10,10,10);
    getch();
    screen->RemoveWindow(w);
    delete screen;
    return 0;
}
