#include <iostream>
#include <stdio.h>
#include <signal.h>
#include "r_curses.h"
using namespace r_curses;

int main() {
    r_screen *screen = new r_screen();
    signal(SIGWINCH,screen->resizeHandler);
    getch();
    r_window *window = r_window(screen,10,10,10,10);
    delete screen;
    return 0;
}
