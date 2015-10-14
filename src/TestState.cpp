#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "TestState.h"
#include "r_SDL.h"
#include "r_utils.h"


using namespace std;

TestState TestState::_TestState;

void TestState::Init(RGameEngine* game)
{   
    //initilize window
    _windows.push_back(new RWindow());
    _windows[0]->Init();
    
    // file writing test
    string lstring = r_utils::UnicodeToHexString (UNICODE_LATIN_BASIC, ",") ;
    r_SDL::WriteFile( "data/raw/latin_basic", lstring.c_str() );
    
    //file read test
    char* data = r_SDL::ReadFile("data/raw/latin_basic");
    _latin = r_utils::HexStringToUnicode(data, ",");
    
    //setup font
    int pnt = 16;
    _font = r_SDL::LoadFont("data/font/unifont-8.0.01.ttf", pnt);
    
    //load background texture
    _textures.push_back(new RTexture());
    _textures[0]->LoadFromFile("data/gfx/checker.png", _windows[0]->renderer);
    
    //create rendered unicode sheet for basic latin set
    _textures.push_back(new RTexture());
    _textures[1]->RenderUnicode(_windows[0]->renderer, &_latin[0], _font);
    
    //create RUnicodeSprite() for basic latin set
    _unicodeSprites.push_back(new RUnicodeSprite());
    _unicodeSprites[0]->Init(_textures[1], _font, pnt, _latin );
    _unicodeSprites[0]->SetForeground({0x80,0x00,0xFF,0xFF});
    _unicodeSprites[0]->SetBackground({0x00,0x00,0x00,0xFF});
    
    //create text style (rectangular) unicode sprite for latin set
    _unicodeSprites.push_back(new RUnicodeSprite());
    _unicodeSprites[1]->Init(_textures[1], _font, pnt, _latin, 0);
    _unicodeSprites[1]->SetForeground({0x80,0x00,0xFF,0xFF});
    _unicodeSprites[1]->SetBackground({0x00,0x00,0x00,0xFF});
    
    //generate custom spritesheet using unicode
    vector<uint16_t> sym = {0x263A,0x263B,0x007C,0x005C,0x2500,0x002F};
    uint16_t *symArray =  &sym[0];
    _textures.push_back(new RTexture());
    _textures[2]->RenderUnicode( _windows[0]->renderer, symArray, _font );
    
    _unicodeSprites.push_back(new RUnicodeSprite());
    _unicodeSprites[2]->Init(_textures[2], _font, pnt, sym);
    _unicodeSprites[2]->AddAnimation("Test", {0x263A,0x263B});
    _unicodeSprites[2]->AddAnimation("Test1", {sym[2],sym[3],sym[4],sym[5]});
    _unicodeSprites[2]->SetAnimation("Test");
    _unicodeSprites[2]->SetForeground({0x80,0x00,0xFF,0xFF});
    _unicodeSprites[2]->SetBackground({0xBA,0xDA,0x55,0xFF});
    
    //create unicode sprite with internal spritesheet texture
    _unicodeSprites.push_back(new RUnicodeSprite());
    _unicodeSprites[3]->Init(_windows[0]->renderer, _font, pnt, sym);
    _unicodeSprites[3]->AddAnimation("Test", {0x263A,0x263B});
    _unicodeSprites[3]->AddAnimation("Test1", {sym[2],sym[3],sym[4],sym[5]});
    _unicodeSprites[3]->SetAnimation("Test");
    _unicodeSprites[3]->SetForeground({0x80,0x00,0xFF,0xFF});
    _unicodeSprites[3]->SetBackground({0xBA,0xDA,0x55,0xFF});
    _unicodeSprites[3]->SetDimensions(24, 24);
    _unicodeSprites[3]->SetRenderOffset(8,4);

    //create spritesheet from png
    _textures.push_back(new RTexture());
    _textures[3]->LoadFromFile("data/gfx/curses_square_16x16.png", _windows[0]->renderer, 0xFF, 0x00, 0xFF);
    
    //create list of frames
    vector<SDL_Rect> frames = {{16,0,16,16},{32,0,16,16}};
    
    //create sprite
    _sprites.push_back(new RSprite());
    _sprites[0]->Init(_textures[3], frames);
    _sprites[0]->SetForeground({0x80,0x00,0xFF,0xFF});
    _sprites[0]->SetBackground({0xBA,0xDA,0x55,0xFF});
    
    //setup timer
    _timers.push_back(new RTimer());
    _timers[0]->Start();
    
    //start text input
    SDL_StartTextInput();
    _y = _windows[0]->GetHeight() / 2;
    _x = _windows[0]->GetWidth()  / 2;
    
    TTF_CloseFont(_font);
}

void TestState::Cleanup(RGameEngine* game)
{
    for (auto &uspr : _unicodeSprites)
    {
        delete uspr;
    }
    for (auto &spr : _sprites)
    {
        delete spr;
    }
    for (auto &tex : _textures)
    {
        delete tex;
    }   
    for (auto &tim : _timers)
    {
        delete tim;
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
            if ( _event.type == SDL_MOUSEBUTTONDOWN )
            {
                _x = _mouse_x;
                _y = _mouse_y;
            }
            
            //handle text input
        } else if ( _event.type == SDL_KEYDOWN )
        {
            if( _event.key.keysym.sym == SDLK_BACKSPACE && _input.length() > 0 )
            {
                _input.pop_back();
            } else if( _event.key.keysym.sym == SDLK_RETURN )
            {
                _input.push_back(0x000D);
            }else if ( _event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
            {
                SDL_SetClipboardText( _input.c_str() );
            } else if ( _event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
            {
                _input = SDL_GetClipboardText();
            }
        } else if ( _event.type == SDL_TEXTINPUT )
        {
            if( !( ( _event.text.text[0] == 'c' || _event.text.text[0] == 'C') && (_event.text.text[0] == 'v' && _event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL ) )
            {
                _input += _event.text.text;
            }
        }
        for (auto &win : _windows)
        {
            win->HandleEvent(_event);
        }
    }
    
    static int velx;
    static int vely;
    
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if ( currentKeyStates[SDL_SCANCODE_ESCAPE] )
    {
        game->Quit();
    }
    if ( currentKeyStates[SDL_SCANCODE_SPACE] )
    {
        static bool der;
        if (der)
        {
            _unicodeSprites[1]->SetAnimation("Test");
           der = false;
        }else
        {
            _unicodeSprites[1]->SetAnimation("Test1");
            der = true;
        }
    }
    if ( currentKeyStates[SDL_SCANCODE_UP] )
    {
        vely = -1;
    }
    if ( currentKeyStates[SDL_SCANCODE_DOWN] )
    {
        vely = 1;
    }
    if ( currentKeyStates[SDL_SCANCODE_LEFT] )
    {
        velx = -1;
    }
    if ( currentKeyStates[SDL_SCANCODE_RIGHT] )
    {
        velx = 1;
    }
    
    if( _x > _windows[0]->GetWidth()  - _unicodeSprites[0]->GetWidth())
    {
        velx = -1;
    }else if ( _x < 0)
    {
        velx = 1;
    }
    if( _y > _windows[0]->GetHeight()  - _unicodeSprites[0]->GetHeight())
    {
        vely = -1;
    }else if ( _y < 0)
    {
        vely = 1;
    }
    
    _x += velx;
    _y += vely;
}

void TestState::Update(RGameEngine* game)
{
    //calculate fps
    int thisT = _timers[0]->GetTicks();
    static int lastT;
    _ms =  thisT - lastT;
    lastT = thisT;
    _fps = _count / (thisT / 1000.f);
    
    //update animations
    for(auto &s : _unicodeSprites)
    {
        s->UpdateAnimation();
    }
    for(auto &s : _sprites)
    {
        s->UpdateAnimation();
    }
}

void TestState::Draw(RGameEngine* game)
{
    SDL_SetRenderDrawColor( _windows[0]->renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( _windows[0]->renderer );
    
    //render background
    _textures[0]->Render(_windows[0]->renderer, 0, 0);
    
    //render mouse and fps
    stringstream msg;
    msg.precision(4);
    msg << "x:" << _mouse_x << " y:" << _mouse_y;
    _unicodeSprites[1]->RenderSymbol(_windows[0]->renderer, 0, _windows[0]->GetHeight()  - _unicodeSprites[1]->GetHeight(), msg.str());
    msg.str(string());
    msg << "fps:" << _fps << " ms:" << _ms;
    _unicodeSprites[1]->RenderSymbol(_windows[0]->renderer, _windows[0]->GetWidth()  - msg.str().size() * _unicodeSprites[1]->GetWidth()  , 0 , msg.str());
    
    //render input text
    _unicodeSprites[1]->RenderSymbol(_windows[0]->renderer, _windows[0]->GetWidth()  / 2 - (32 * _unicodeSprites[1]->GetWidth() ) / 2, _windows[0]->GetHeight()  / 2 - _unicodeSprites[1]->GetHeight(), _input,_unicodeSprites[1]->GetWidth() * 32);
   
    //render test sprites:
    //latin set text
    _unicodeSprites[0]->RenderSymbol(_windows[0]->renderer, 0 , _unicodeSprites[0]->GetHeight(), _latin, _unicodeSprites[0]->GetWidth() * 16 );
    _unicodeSprites[1]->RenderSymbol(_windows[0]->renderer, _unicodeSprites[1]->GetWidth() + _unicodeSprites[0]->GetWidth() * 16 , _unicodeSprites[1]->GetHeight(), _latin, _unicodeSprites[1]->GetWidth() * 16 );
   
    //test sprites
    _unicodeSprites[2]->Render(_windows[0]->renderer, 0 , 0);
    _unicodeSprites[3]->Render(_windows[0]->renderer, _windows[0]->GetWidth()  - _unicodeSprites[3]->GetWidth() , _windows[0]->GetHeight()  - _unicodeSprites[3]->GetHeight());
    
    _sprites[0]->Render(_windows[0]->renderer, _x, _y);
     
    SDL_RenderPresent( _windows[0]->renderer );
    _count++;
} 
