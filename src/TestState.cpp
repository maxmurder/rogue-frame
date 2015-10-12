#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "TestState.h"
#include "r_SDL.h"
#include <stdlib.h>

using namespace std;

TestState TestState::_TestState;

void TestState::Init(RGameEngine* game)
{   
    _windows.push_back(new RWindow());
    _windows[0]->Init();
    
    // file writing test
    stringstream ls;
    for( uint32_t i = 0; i <= sizeof(UNICODE_LATIN_BASIC) / sizeof(uint16_t); i++ )
    {
        if (i == 0)
        {   ls << "0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << UNICODE_LATIN_BASIC[i]; 
        }else 
        {
            ls << ",0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << UNICODE_LATIN_BASIC[i]; 
        }
    } 
    string lstring = ls.str();
    r_SDL::WriteFile("data/raw/latin_basic", lstring.c_str());
    
    
    //file reading test
    char* data = r_SDL::ReadFile("data/raw/latin_basic");
    string str = data;
    string newString;
    
    size_t pos = 0;
    string token;
    while ( ( pos = str.find(',') ) != string::npos)
    {
         token = str.substr(0,pos);
         _latin.push_back( (int)strtol( token.c_str(), NULL, 0 ) );
         newString += _latin.back();
         str.erase(0, pos + 1);
    }
    
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
    _sprites.push_back(new RUnicodeSprite());
    _sprites[0]->Init(_textures[1], _font, pnt, _latin );
    _sprites[0]->SetForeground({0x80,0x00,0xFF,0xFF});
    _sprites[0]->SetBackground({0x00,0x00,0x00,0xFF});
    
    //create test unicode spritesheet texture
    vector<uint16_t> sym = {0x263B,0x263A,0x007C,0x005C,0x2500,0x002F};
    uint16_t *symArray =  &sym[0];

    //create spritesheet using unicode
    _textures.push_back(new RTexture());
    _textures[2]->RenderUnicode( _windows[0]->renderer, symArray, _font );
    
    _sprites.push_back(new RUnicodeSprite());
    _sprites[1]->Init(_textures[2], _font, pnt, sym);
    _sprites[1]->AddAnimation("Test", {0x263B,0x263A});
    _sprites[1]->AddAnimation("Test1", {sym[2],sym[3],sym[4],sym[5]});
    _sprites[1]->SetAnimation("Test");
    _sprites[1]->SetForeground({0x80,0x00,0xFF,0xFF});
    _sprites[1]->SetBackground({0xBA,0xDA,0x55,0xFF});
    
    //create unicode sprite with internal spritesheet texture
    _sprites.push_back(new RUnicodeSprite());
    _sprites[2]->Init(_windows[0]->renderer, _font, pnt, sym);
    _sprites[2]->AddAnimation("Test", {0x263A,0x263B});
    _sprites[2]->AddAnimation("Test1", {sym[2],sym[3],sym[4],sym[5]});
    _sprites[2]->SetAnimation("Test");
    _sprites[2]->SetForeground({0x80,0x00,0xFF,0xFF});
    _sprites[2]->SetBackground({0x00,0x00,0x00,0xFF});

    TTF_CloseFont(_font);
    
    //setup timer
    _timers.push_back(new RTimer());
    _timers[0]->Start();
    
    //start text input
    SDL_StartTextInput();
    _y = _windows[0]->GetHeight() / 2;
    _x = _windows[0]->GetWidth()  / 2;
}

void TestState::Cleanup(RGameEngine* game)
{
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
    for (auto &win : _windows)
    {
        delete win;
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
            _sprites[1]->SetAnimation("Test");
           der = false;
        }else
        {
            _sprites[1]->SetAnimation("Test1");
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
    
    if( _x > _windows[0]->GetWidth()  - _sprites[0]->GetWidth())
    {
        velx = -1;
    }else if ( _x < 0)
    {
        velx = 1;
    }
    if( _y > _windows[0]->GetHeight()  - _sprites[0]->GetHeight())
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
    _sprites[0]->RenderSymbol(_windows[0]->renderer, 0, _windows[0]->GetHeight()  - _sprites[0]->GetHeight(), msg.str());
    msg.str(string());
    msg << "fps:" << _fps << " ms:" << _ms;
    _sprites[0]->RenderSymbol(_windows[0]->renderer, _windows[0]->GetWidth()  - msg.str().size() * _sprites[0]->GetWidth()  , 0 , msg.str());
    
    //render test sprites
    _sprites[1]->Render(_windows[0]->renderer, 0 , 0);
    _sprites[2]->Render(_windows[0]->renderer, _windows[0]->GetWidth()  - _sprites[2]->GetWidth() , _windows[0]->GetHeight()  - _sprites[2]->GetHeight());
    _sprites[0]->RenderSymbol(_windows[0]->renderer, _x, _y, '@');
    
    _sprites[0]->RenderSymbol(_windows[0]->renderer, 0 , _sprites[0]->GetHeight(), _latin, _sprites[0]->GetWidth() * 15 );
    
    //render input text
    _sprites[0]->RenderSymbol(_windows[0]->renderer, _windows[0]->GetWidth()  / 2 - (32 * _sprites[0]->GetWidth() ) / 2, _windows[0]->GetHeight()  / 2 - _sprites[0]->GetHeight(), _input,_sprites[0]->GetWidth() * 32);
      
    SDL_RenderPresent( _windows[0]->renderer );
    _count++;
} 
