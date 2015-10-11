#include <iostream>
#include <vector>
#include "TestState.h"
#include "r_SDL.h"

TestState TestState::_TestState;

void TestState::Init(RGameEngine* game)
{   
    //setup font
    int pnt = 16;
    _font = r_SDL::LoadFont("data/font/unifont-8.0.01.ttf", pnt);
    //_font = r_SDL::LoadFont("/usr/share/fonts/truetype/msttcorefonts/Courier_New_Bold.ttf", pnt);
    
    //load background texture
    _textures.push_back(new RTexture());
    _textures[0]->LoadFromFile("data/gfx/checker.png", game->renderer);
    
    //create rendered unicode sheet for basic latin set
    _textures.push_back(new RTexture());
    _textures[1]->RenderUnicode(game->renderer, UNICODE_LATIN_BASIC, _font );
    std::vector<uint16_t> latin(UNICODE_LATIN_BASIC, UNICODE_LATIN_BASIC + sizeof(UNICODE_LATIN_BASIC) / sizeof(UNICODE_LATIN_BASIC[0]));
    
    //create RUnicodeSprite() for basic latin set
    _sprites.push_back(new RUnicodeSprite());
    _sprites[0]->Init(_textures[1], _font, pnt, latin );
    _sprites[0]->SetForeground({0x80,0x00,0xFF,0xFF});
    _sprites[0]->SetBackground({0x00,0x00,0x00,0xFF});
    
    //create test unicode spritesheet texture
    std::vector<uint16_t> sym = {0x263B,0x263A,0x007C,0x005C,0x2500,0x002F};
    uint16_t *symArray =  &sym[0];

    //create spritesheet using unicode
    _textures.push_back(new RTexture());
    _textures[2]->RenderUnicode( game->renderer, symArray, _font );
    
    _sprites.push_back(new RUnicodeSprite());
    _sprites[1]->Init(_textures[2], _font, pnt, sym);
    _sprites[1]->AddAnimation("Test", {0x263B,0x263A});
    _sprites[1]->AddAnimation("Test1", {sym[2],sym[3],sym[4],sym[5]});
    _sprites[1]->SetAnimation("Test");
    _sprites[1]->SetForeground({0x80,0x00,0xFF,0xFF});
    _sprites[1]->SetBackground({0x80,0x00,0x00,0xFF});
    
    //create unicode sprite with internal spritesheet texture
    _sprites.push_back(new RUnicodeSprite());
    _sprites[2]->Init(game->renderer, _font, pnt, sym);
    _sprites[2]->AddAnimation("Test", {0x263A,0x263B});
    _sprites[2]->AddAnimation("Test1", {sym[2],sym[3],sym[4],sym[5]});
    _sprites[2]->SetAnimation("Test");
    _sprites[2]->SetForeground({0x80,0x00,0xFF,0xFF});
    _sprites[2]->SetBackground({0x00,0x00,0x00,0xFF});

    TTF_CloseFont(_font);
}

void TestState::Cleanup(RGameEngine* game)
{
    for (auto &p : _textures)
    {
        delete p;
    }   
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
        } else if ( _event.type == SDL_MOUSEMOTION || _event.type == SDL_MOUSEBUTTONDOWN || _event.type == SDL_MOUSEBUTTONUP )
        {
            SDL_GetMouseState( &_mouse_x, &_mouse_y);
        }
    }
    
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if ( currentKeyStates[SDL_SCANCODE_RETURN] )
    {
        game->Quit();
    }
    if ( currentKeyStates[SDL_SCANCODE_SPACE] )
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

void TestState::Update(RGameEngine* game)
{

    int last = _ticks;
    _ticks = SDL_GetTicks();
    _ms = (_ticks - last);
    _fps = _ms * 1000;
    
    
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
    _textures[0]->Render(game->renderer, 0, 0);
    
    std::string msg;
    msg = "x:" + std::to_string(_mouse_x) + " y:" + std::to_string(_mouse_y);
    
    _sprites[0]->RenderSymbol(game->renderer, 0, 480 - _sprites[0]->GetHeight(), msg);
    msg = "fps:" + std::to_string(_fps) + " ms:" + std::to_string(_ms);
    _sprites[0]->RenderSymbol(game->renderer, 640 - msg.length() * _sprites[0]->GetWidth()  , 0 , msg);
    
    _sprites[1]->Render(game->renderer, 0 , 0);
    _sprites[2]->Render(game->renderer, 640 - _sprites[2]->GetWidth() , 480 - _sprites[2]->GetHeight());
    
    SDL_RenderPresent( game->renderer );
} 
