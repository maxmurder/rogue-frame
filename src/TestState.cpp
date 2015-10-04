#include <iostream>
#include "TestState.h"
#include "r_SDL.h"

TestState TestState::m_TestState;

void TestState::Init(RGameEngine* game)
{
    _bg = r_SDL::LoadImage("src/test.bmp", game->screen->format);
}
void TestState::Cleanup(RGameEngine* game)
{
    SDL_FreeSurface( _bg );
}
void TestState::Pause(RGameEngine* game){}
void TestState::Resume(RGameEngine* game){}
void TestState::HandleEvents(RGameEngine* game)
{
    while( SDL_PollEvent( &_event ) )
    {
        if( _event.type == SDL_QUIT )
        {
            game->Quit();
        }
    }
}
void TestState::Update(RGameEngine* game){}
void TestState::Draw(RGameEngine* game)
{
    r_SDL::ApplySurface(0, 0, _bg, game->screen);
    SDL_UpdateWindowSurface( game->window );
} 
