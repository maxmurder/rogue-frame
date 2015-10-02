#include <iostream>
#include <stdio.h>
#include "r_engine.h"
#include "TestState.h"

int main() 
{
    r_engine::RGameEngine game;

    game.Init();
    game.ChangeState( TestState::Instance() );
    
    /*while (game.Running() )
    {
        game.HandleEvents();
        game.Update();
        game.Draw();
    }*/
    getch();
    
    game.Cleanup();
    return 0;
}
