#include <iostream>
#include "r_engine/r_engine.h"
#include "TestState.h"

int main( int argc, char* args[] ) 
{
    RGameEngine game;

    if (game.Init("Test") != 0)
    {
        return 1;
    }
    game.ChangeState( new TestState() );
    
    return game.Start();
}
