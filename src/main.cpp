#include <iostream>
#include "r_engine.h"
#include "TestState.h"

int main( int argc, char* args[] ) 
{
    RGameEngine game;

    game.Init("Test");
    game.ChangeState( TestState::Instance() );
    
    while (game.Running() )
    {
        game.HandleEvents();
        game.Update();
        game.Draw();
    } 
    game.Cleanup();
    return 0;
}
