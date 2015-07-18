#include <iostream>
#include <stdio.h>
#include "rcurses_manager.h"
using namespace rcurses_manager;

int main() {
    printf("Hello!\n");
    screen_manager scr;
    scr.AddScreen();
    getchar();
}
