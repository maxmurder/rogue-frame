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
    int pnt = 32;
    _font = r_SDL::LoadFont("data/font/unifont-8.0.01.ttf", pnt);
    
    //create rendered unicode sheet
    _textTex = new RTexture();
    _textTex->RenderUnicode(game->renderer, UNICODE_LATIN_BASIC, _font );
    std::vector<uint16_t> latin(UNICODE_LATIN_BASIC, UNICODE_LATIN_BASIC + sizeof(UNICODE_LATIN_BASIC) / sizeof(UNICODE_LATIN_BASIC[0]));
    
    
    //create unicode spritesheet texture
    std::vector<uint16_t> sym = {0x263B,0x263A,0x007C,0x005C,0x2500,0x002F};
    uint16_t *symArray =  &sym[0];

    //create spritesheet using unicode
    _spriteTex = new RTexture();
    _spriteTex->RenderUnicode( game->renderer, symArray, _font );
    
    //enw
    _sprites.push_back(new RUnicodeSprite());
    _sprites[0]->Init(_textTex, _font, pnt, latin );
    _sprites[0]->SetForeground({0x80,0x00,0xFF,0xFF});
    _sprites[0]->SetBackground({0x00,0x00,0x00,0xFF});
    
    _sprites.push_back(new RUnicodeSprite());
    _sprites[1]->Init(_spriteTex, _font, pnt, sym);
    _sprites[1]->AddAnimation("Test", {0x263B,0x263A});
    _sprites[1]->AddAnimation("Test1", {sym[2],sym[3],sym[4],sym[5]});
    _sprites[1]->SetAnimation("Test");
    _sprites[1]->SetForeground({0x80,0x00,0xFF,0xFF});
    _sprites[1]->SetBackground({0x80,0x00,0x00,0xFF});
    
    //create unicode sprite with internal spritesheet texture
    _sprites.push_back(new RUnicodeSprite());
    _sprites[2]->Init(game->renderer, _font, pnt, sym);
    _sprites[2]->AddAnimation("Test", {0x263B,0x263A});
    _sprites[2]->AddAnimation("Test1", {sym[2],sym[3],sym[4],sym[5]});
    _sprites[2]->SetAnimation("Test");
    _sprites[2]->SetForeground({0x80,0x00,0xFF,0xFF});
    _sprites[2]->SetBackground({0x00,0x00,0x00,0xFF});

    TTF_CloseFont(_font);
}

void TestState::Cleanup(RGameEngine* game)
{
    delete _texture;
   
    for (auto &p : _sprites)
    {
        delete p;
    }
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
                    _sprites[1]->SetAnimation("Test");
                   der = false;
                }else
                {
                    _sprites[1]->SetAnimation("Test1");
                    der = true;
                }
            }
        }
    }
}

void TestState::Update(RGameEngine* game)
{
    for(auto &s : _sprites)
    {
        s->UpdateAnimation();
    }
}

void TestState::Draw(RGameEngine* game)
{
    SDL_SetRenderDrawColor( game->renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( game->renderer );
    
    //render background
    _texture->Render(game->renderer, 0, 0);
    
    _sprites[0]->RenderSymbol(game->renderer, 320, 240, "Hello World!");
    //render sprites
    _sprites[1]->Render(game->renderer, 0 , 0);
    _sprites[2]->Render(game->renderer, 640 - _sprites[2]->GetPntSize()/2 , 480 - _sprites[2]->GetPntSize());
    
    SDL_RenderPresent( game->renderer );
} 
