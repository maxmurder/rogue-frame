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
    
    //create RSprite() for basic latin set
    _sprites.push_back(new RSprite());
    _sprites[0]->Init(_textures[1], _font, pnt, _latin, 2 );
    _sprites[0]->SetForeground({0x80,0x00,0xFF,0xFF});
    _sprites[0]->SetBackground({0x00,0x00,0x00,0xFF});
    
    //create text style (rectangular) unicode sprite for latin set
    _sprites.push_back(new RSprite());
    _sprites[1]->Init(_textures[1], _font, pnt, _latin );
    _sprites[1]->SetForeground({0x80,0x00,0xFF,0xFF});
    _sprites[1]->SetBackground({0x00,0x00,0x00,0xFF});
    
    //generate custom spritesheet using unicode
    vector<uint16_t> sym = {0x263A,0x263B,0x007C,0x005C,0x2500,0x002F};
    uint16_t *symArray =  &sym[0];
    _textures.push_back(new RTexture());
    _textures[2]->RenderUnicode( _windows[0]->renderer, symArray, _font );
    
    _sprites.push_back(new RSprite());
    _sprites[2]->Init(_textures[2], _font, pnt, sym);
    _sprites[2]->AddUnicodeAnimation("Test", {0x263A,0x263B});
    _sprites[2]->AddUnicodeAnimation("Test1", {sym[2],sym[3],sym[4],sym[5]});
    _sprites[2]->SetAnimation("Test");
    _sprites[2]->SetForeground({0x80,0x00,0xFF,0xFF});
    _sprites[2]->SetBackground({0xBA,0xDA,0x55,0xFF});
    
    //create unicode sprite with internal spritesheet texture
    _sprites.push_back(new RSprite());
    _sprites[3]->Init(_windows[0]->renderer, _font, pnt, sym);
    _sprites[3]->AddUnicodeAnimation("Test", {0x263A,0x263B});
    _sprites[3]->AddUnicodeAnimation("Test1", {sym[2],sym[3],sym[4],sym[5]});
    _sprites[3]->SetAnimation("Test");
    _sprites[3]->SetForeground({0x80,0x00,0xFF,0xFF});
    _sprites[3]->SetBackground({0xBA,0xDA,0x55,0xFF});
    _sprites[3]->SetDimensions(24, 24);
    _sprites[3]->SetRenderOffset(8,4);

    //create spritesheet from png
    _textures.push_back(new RTexture());
    _textures[3]->LoadFromFile("data/gfx/curses_square_16x16.png", _windows[0]->renderer, 0xFF, 0x00, 0xFF);
    
    //create list of frames
    vector<SDL_Rect> frames = {{16,0,16,16},{32,0,16,16}};
    
    //create sprite
    _sprites.push_back(new RSprite());
    _sprites[4]->Init(_textures[3], frames);
    _sprites[4]->SetForeground({0x80,0x00,0xFF,0xFF});
    _sprites[4]->SetBackground({0xBA,0xDA,0x55,0xFF});
    
    //setup timer
    _timers.push_back(new RTimer());
    _timers[0]->Start();
    
    _y = _windows[0]->GetHeight() / 2;
    _x = _windows[0]->GetWidth()  / 2;
    
    TTF_CloseFont(_font);

    //start input
    SDL_StartTextInput();    
    currentKeyStates = SDL_GetKeyboardState(NULL);
}

void TestState::Cleanup(RGameEngine* game)
{
    for (auto &uspr : _sprites)
    {
        delete uspr;
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
    
    SDL_StopTextInput(); 
}

void TestState::Pause(RGameEngine* game){}
void TestState::Resume(RGameEngine* game){}
void TestState::HandleEvents(RGameEngine* game)
{
    //handle important key events
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
        }
        
        //get keyboard text input
        _input = r_SDL::TextInputHandler(_event, _input);
        
        //handle window events
        for (auto &win : _windows)
        {
            win->HandleEvent(_event);
        }
    }
    
    if ( currentKeyStates[SDL_SCANCODE_ESCAPE] )
    {
        game->Quit();
    }
    
    static bool sp_down;
    
    if ( currentKeyStates[SDL_SCANCODE_SPACE] )
    {
        if(!sp_down)
        {
            static bool der;
            if (der)
            {
                _sprites[2]->SetAnimation("Test");
               der = false;
            }else
            {
                _sprites[2]->SetAnimation("Test1");
                der = true;
            }
        }
        sp_down = true;
    }else{
        sp_down = false;
    }
    
    //'player' movement
    if ( currentKeyStates[SDL_SCANCODE_UP] )
    {
        _y -= 1;
    }
    if ( currentKeyStates[SDL_SCANCODE_DOWN] )
    {
        _y += 1;
    }
    if ( currentKeyStates[SDL_SCANCODE_LEFT] )
    {
        _sprites[0]->SetTextMode( RSprite::TEXT );
        _sprites[2]->SetTextMode( RSprite::TEXT );
        _x -= 1;
    }
    if ( currentKeyStates[SDL_SCANCODE_RIGHT] )
    {
        _sprites[0]->SetTextMode( RSprite::UNICODE );
        _sprites[2]->SetTextMode( RSprite::UNICODE );
        _x += 1;
    }
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
    
    //keep player in bounds
    if( _x > _windows[0]->GetWidth()  - _sprites[0]->GetWidth())
    {
        _x -= 1;
    }else if ( _x < 0)
    {
        _x += 1;
    }
    if( _y > _windows[0]->GetHeight()  - _sprites[0]->GetHeight())
    {
        _y -= 1;
    }else if ( _y < 0)
    {
        _y += 1;
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
    _sprites[1]->RenderSymbol(_windows[0]->renderer, 0, _windows[0]->GetHeight()  - _sprites[1]->GetHeight(), msg.str());
    msg.str(string());
    msg << "fps:" << std::setfill('0') << std::setw(5) << _fps << " ms:" << _ms;
    _sprites[1]->RenderSymbol(_windows[0]->renderer, _windows[0]->GetWidth()  - msg.str().size() * _sprites[1]->GetWidth()  , 0 , msg.str());
    
    //render input text
    _sprites[1]->RenderSymbol(_windows[0]->renderer, _windows[0]->GetWidth()  / 2 - (32 * _sprites[1]->GetWidth() ) / 2, _windows[0]->GetHeight()  / 2 - _sprites[1]->GetHeight(), _input,_sprites[1]->GetWidth() * 32);
   
    //render test sprites:
    //latin set text
    _sprites[0]->RenderSymbol(_windows[0]->renderer, 0 , _sprites[0]->GetHeight(), _latin, _sprites[0]->GetWidth() * 16 );
    _sprites[1]->RenderSymbol(_windows[0]->renderer, _sprites[1]->GetWidth() + _sprites[0]->GetWidth() * 16 , _sprites[1]->GetHeight(), _latin, _sprites[1]->GetWidth() * 16 );
   
    //test sprites
    _sprites[2]->Render(_windows[0]->renderer, 0 , 0);
    _sprites[3]->Render(_windows[0]->renderer, _windows[0]->GetWidth()  - _sprites[3]->GetWidth() , _windows[0]->GetHeight()  - _sprites[3]->GetHeight());
    
    _sprites[4]->Render(_windows[0]->renderer, _x, _y);

    SDL_RenderPresent( _windows[0]->renderer );
    _count++;
} 
