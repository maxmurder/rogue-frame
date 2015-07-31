#include <iostream>
#include <stdio.h>
#include "r_curses.h"
using namespace r_curses;

int main() {
    r_screen *screen = new r_screen();
    getch();
    #ifndef _WIN32
    system("reset");
    #endif
    return 0;
}
