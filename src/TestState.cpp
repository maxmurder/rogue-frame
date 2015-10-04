#include <iostream>
#include "TestState.h"
#include "r_SDL.h"

TestState TestState::m_TestState;

void TestState::Init()
{
    _bg = r_SDL::LoadImage("src/test.bmp");
}
void TestState::Cleanup()
{
    SDL_FreeSurface( _bg );
}
void TestState::Pause(){}
void TestState::Resume(){}
void TestState::HandleEvents(RGameEngine* game){}
void TestState::Update(RGameEngine* game)
{
    static int i = 0;
    if (i>2000)
    {
        game->Quit();
    }
    i++;
}
void TestState::Draw(RGameEngine* game)
{
    r_SDL::ApplySurface(0, 0, _bg, game->screen);
    SDL_Flip( game->screen );
} 
