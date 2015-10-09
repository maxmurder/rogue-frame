#include <iostream>
#include <vector>
#include "TestState.h"
#include "r_SDL.h"

TestState TestState::_TestState;

void TestState::Init(RGameEngine* game)
{
    _texture = new RTexture();
    _texture->LoadFromFile("src/test.bmp", game->renderer);
    
    _spriteTex = new RTexture();
    _spriteTex->LoadFromFile("data/gfx/curses_square_16x16.png", game->renderer, 0xFF,0x00,0xFF);
    
    _font = r_SDL::LoadFont("data/font/FSEX300.ttf", 64);
    _textTex = new RTexture();
    _textTex->RenderText( game->renderer, "Hello World!", _font, {0xFF, 0x00, 0x00, 0xFF} );
    
    SDL_Rect f1 = {16,0,16,16};
    SDL_Rect f2 = {32,0,16,16};
    std::vector<SDL_Rect> frames = {f1,f2};
    
    _sprite = new RSprite(_spriteTex, frames);
    _sprite->SetRGBA({0x80,0x00,0xFF,0xFF});
}

void TestState::Cleanup(RGameEngine* game)
{
   delete _texture;
   
   delete _spriteTex;
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

void TestState::Update(RGameEngine* game)
{
    static int i = 0;
    
    if ( i > 10000)
    {
        _sprite->NextFrame();
        i = 0;
    }
    i++;
}

void TestState::Draw(RGameEngine* game)
{
    SDL_SetRenderDrawColor( game->renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( game->renderer );
    
    _texture->Render(game->renderer, 0, 0);
  
    _textTex->Render(game->renderer, 320 - _textTex->GetWidth() / 2, 240 - _textTex->GetHeight() / 2 );
    _sprite->Render(game->renderer, 0, 0);
    
    SDL_RenderPresent( game->renderer );
} 
