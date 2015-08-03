#include <iostream>
#include <stdio.h>
#include <signal.h>
#include "r_curses.h"
using namespace r_curses;

int main() {
    r_screen *screen = new r_screen();
    signal(SIGWINCH,screen->resizeHandler);
    getch();
    delete screen;
    return 0;
}
