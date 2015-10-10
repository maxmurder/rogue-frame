#include <iostream>
#include <vector>
#include "TestState.h"
#include "r_SDL.h"

TestState TestState::_TestState;

void TestState::Init(RGameEngine* game)
{   
    //load background texture
    _texture = new RTexture();
    _texture->LoadFromFile("src/test.bmp", game->renderer);
    
    //setup font
    int pnt = 64;
    _font = r_SDL::LoadFont("data/font/unifont-8.0.01.ttf", pnt);
    
    //create text element
    _textTex = new RTexture();
    _textTex->RenderText( game->renderer, "Hello World!", _font, {0xFF, 0x00, 0x00, 0xFF} );
    
    //create unicode spritesheet texture
    std::vector<uint16_t> sym = {0x263B,0x263A,0x007C,0x005C,0x2500,0x002F};
    uint16_t *symArray =  &sym[0];
    
    _spriteTex = new RTexture();
    _spriteTex->RenderUnicode( game->renderer, symArray, _font );
    
    //create unicode sprite from unicode spritesheet
    _sprite = new RUnicodeSprite();
    _sprite->Init(_spriteTex, _font, pnt, sym);
    _sprite->AddAnimation("Test", {0x263B,0x263A});
    _sprite->AddAnimation("Test1", {0x007C,0x005C,0x2500,0x002F});
    _sprite->SetAnimation("Test");
    _sprite->SetForeground({0x80,0x00,0xFF,0xFF});
    _sprite->SetBackground({0x00,0x00,0x00,0xFF});
    
    //create unicode sprite with internal spritesheet texture
    _unicode = new RUnicodeSprite();
    _unicode->Init(game->renderer, _font, pnt, {0x263B,0x263A,0x007C,0x005C,0x2500,0x002F});
    _unicode->AddAnimation("Test", {0x263B,0x263A});
    _unicode->AddAnimation("Test1", {0x007C,0x005C,0x2500,0x002F});
    _unicode->SetAnimation("Test");
    _unicode->SetForeground({0x80,0x00,0xFF,0xFF});
    _unicode->SetBackground({0x00,0x00,0x00,0xFF});
}

void TestState::Cleanup(RGameEngine* game)
{
    TTF_CloseFont(_font);
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
            else if ( _event.key.keysym.sym == SDLK_SPACE )
            {
                static bool der;
                if (der)
                {
                   _sprite->SetAnimation("Test");
                   _unicode->SetAnimation("Test");
                   der = false;
                }else
                {
                    _sprite->SetAnimation("Test1");
                    _unicode->SetAnimation("Test1");
                    der = true;
                }
            }
        }
    }
}

void TestState::Update(RGameEngine* game)
{
    _sprite->UpdateAnimation();
    _unicode->UpdateAnimation();
}

void TestState::Draw(RGameEngine* game)
{
    SDL_SetRenderDrawColor( game->renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( game->renderer );
    
    _texture->Render(game->renderer, 0, 0);
  
    _textTex->Render(game->renderer, 320 - _textTex->GetWidth() / 2, 240 - _textTex->GetHeight() / 2 );
    _sprite->Render(game->renderer, 0, 0);
    _unicode->Render(game->renderer, 640-_unicode->GetPntSize()/2, 480 - _unicode->GetPntSize());
    
    SDL_RenderPresent( game->renderer );
} 
