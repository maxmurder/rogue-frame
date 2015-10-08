#include <iostream>
#include "TestState.h"
#include "r_SDL.h"

TestState TestState::m_TestState;

void TestState::Init(RGameEngine* game)
{
    _texture = new RTexture();
    _texture->LoadFromFile("src/test.bmp", game->renderer);
    
    _sprite = new RTexture();
    _sprite->LoadFromFile("data/gfx/curses_square_16x16.bmp", game->renderer, 0xFF, 0, 0xFF );
    _spriteClip[0].x = 16;
    _spriteClip[0].y = 0;
    _spriteClip[0].h = 16;
    _spriteClip[0].w = 16;
    
    _spriteClip[1].x = 32;
    _spriteClip[1].y = 0;
    _spriteClip[1].h = 16;
    _spriteClip[1].w = 16;
    
    _sprite->SetColor( 0x72, 0x00, 0xFF );
}
void TestState::Cleanup(RGameEngine* game)
{
   delete _texture;
   delete _sprite;
   
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
void TestState::Update(RGameEngine* game){}
void TestState::Draw(RGameEngine* game)
{

    static int width;
    static int height;
    SDL_GetWindowSize(game->window, &width, &height);
    
    
    SDL_SetRenderDrawColor( game->renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( game->renderer );
    
    _texture->Render(game->renderer, 0, 0);
    
    _sprite->Render(game->renderer, 0, 0, &_spriteClip[0]);
    _sprite->Render(game->renderer, width - 16, height - 16, &_spriteClip[1]);

    SDL_RenderPresent( game->renderer );
} 
