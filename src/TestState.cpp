#include <iostream>
#include "TestState.h"
#include "r_SDL.h"

TestState TestState::m_TestState;

void TestState::Init(RGameEngine* game)
{
    _texture = r_SDL::LoadTexture("src/test.bmp", game->renderer);
    tex = new RTexture();
    tex->LoadFromFile("ColorkeyTest.png", game->renderer, 0, 0xFF, 0xFF);

}
void TestState::Cleanup(RGameEngine* game)
{
    SDL_DestroyTexture( _texture );
    
    tex->FreeTexture();
    delete tex;
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

    int width;
    int height;
    SDL_GetWindowSize(game->window, &width, &height);
    
    SDL_SetRenderDrawColor( game->renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( game->renderer );
    
    SDL_RenderCopy( game->renderer, _texture, NULL, NULL );
    
    tex->Render(game->renderer, 240, 190);

    SDL_RenderPresent( game->renderer );
} 
