#include <iostream>
#include <stdio.h>
#include "rcurses_manager.h"
using namespace rcurses_manager;

int main() {
    screen_manager scr;
    scr.AddScreen();
    getch();
}
