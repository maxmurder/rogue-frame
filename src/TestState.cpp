#include <iostream>
#include "TestState.h"
#include "r_SDL.h"

TestState TestState::m_TestState;

void TestState::Init(RGameEngine* game)
{
    _texture = r_SDL::LoadTexture("src/test.bmp", game->renderer);
}
void TestState::Cleanup(RGameEngine* game)
{
    SDL_DestroyTexture( _texture );
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
        } else if ( _event.type == SDL_KEYDOWN )
        {
            if ( _event.key.keysym.sym == SDLK_RETURN )
            {
                game->Quit();
            }
        }
    }
}
void TestState::Update(RGameEngine* game)
{}
void TestState::Draw(RGameEngine* game)
{
    SDL_RenderClear( game->renderer );
    SDL_RenderCopy( game->renderer, _texture, NULL, NULL );
    SDL_RenderPresent( game->renderer );
} 
