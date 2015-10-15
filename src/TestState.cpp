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
        
    //create sprite for basic latin set
    _spriteSystem.components[SPRITE_LATIN_UNI] = new RSprite(SPRITE_LATIN_UNI);
    _spriteSystem.components[SPRITE_LATIN_UNI]->Init(_textures[1], _font, pnt, _latin, 2 );
    _spriteSystem.components[SPRITE_LATIN_UNI]->SetForeground({0x80,0x00,0xFF,0xFF});
    _spriteSystem.components[SPRITE_LATIN_UNI]->SetBackground({0x00,0x00,0x00,0xFF});
    
    //create text style (rectangular) unicode sprite for latin set
    _spriteSystem.components[SPRITE_LATIN_TEXT] = new RSprite(SPRITE_LATIN_TEXT);
    _spriteSystem.components[SPRITE_LATIN_TEXT]->Init(_textures[1], _font, pnt, _latin );
    _spriteSystem.components[SPRITE_LATIN_TEXT]->SetForeground({0x80,0x00,0xFF,0xFF});
    _spriteSystem.components[SPRITE_LATIN_TEXT]->SetBackground({0x00,0x00,0x00,0xFF});
    
    //generate custom spritesheet using unicode
    vector<uint16_t> sym = {0x263A,0x263B,0x007C,0x005C,0x2500,0x002F};
    uint16_t *symArray =  &sym[0];
    _textures.push_back(new RTexture());
    _textures[2]->RenderUnicode( _windows[0]->renderer, symArray, _font );
    
    _spriteSystem.components[3] = new RSprite(3);
    _spriteSystem.components[3]->Init(_textures[2], _font, pnt, sym);
    _spriteSystem.components[3]->AddUnicodeAnimation("Test", {0x263A,0x263B});
    _spriteSystem.components[3]->AddUnicodeAnimation("Test1", {sym[2],sym[3],sym[4],sym[5]});
    _spriteSystem.components[3]->SetAnimation("Test");
    _spriteSystem.components[3]->SetForeground({0x80,0x00,0xFF,0xFF});
    _spriteSystem.components[3]->SetBackground({0xBA,0xDA,0x55,0xFF});
    
    //create unicode sprite with internal spritesheet texture
    _spriteSystem.components[4] = new RSprite(4);
    _spriteSystem.components[4]->Init(_windows[0]->renderer, _font, pnt, sym);
    _spriteSystem.components[4]->AddUnicodeAnimation("Test", {0x263A,0x263B});
    _spriteSystem.components[4]->AddUnicodeAnimation("Test1", {sym[2],sym[3],sym[4],sym[5]});
    _spriteSystem.components[4]->SetAnimation("Test");
    _spriteSystem.components[4]->SetForeground({0x80,0x00,0xFF,0xFF});
    _spriteSystem.components[4]->SetBackground({0xBA,0xDA,0x55,0xFF});
    _spriteSystem.components[4]->SetDimensions(24, 24);
    _spriteSystem.components[4]->SetRenderOffset(8,4);

    //create spritesheet from png
    _textures.push_back(new RTexture());
    _textures[3]->LoadFromFile("data/gfx/curses_square_16x16.png", _windows[0]->renderer, 0xFF, 0x00, 0xFF);
    
    //create list of frames
    vector<SDL_Rect> frames = {{16,0,16,16},{32,0,16,16}};
    
    //create "player entity"
    _positionSystem.components[5] = new PositionComponent(5);
    _positionSystem.components[5]->x = _windows[0]->GetWidth()  / 2;
    _positionSystem.components[5]->y = _windows[0]->GetHeight() / 2;
    _spriteSystem.components[5] = new RSprite(5);
    _spriteSystem.components[5]->Init(_textures[3], frames);
    _spriteSystem.components[5]->SetForeground({0x80,0x00,0xFF,0xFF});
    _spriteSystem.components[5]->SetBackground({0xBA,0xDA,0x55,0xFF});
    _renderSystem.components[5] = new RenderComponent(5, _positionSystem, _spriteSystem);
    
    //setup timer
    _timerSystem.components[0] = new RTimer(0);
    _timerSystem.components[0]->Start();
    
    TTF_CloseFont(_font);

    //start input
    SDL_StartTextInput();    
    currentKeyStates = SDL_GetKeyboardState(NULL);
}

void TestState::Cleanup(RGameEngine* game)
{
    for (auto &tex : _textures)
    {
        delete tex;
    }   
    for (auto &win : _windows)
    {
        delete win;
    }
    for (auto &tim : _timerSystem.components)
    {
        delete tim.second;
    }
    for (auto &pos: _positionSystem.components)
    {
        delete pos.second;
    }
    for (auto &spr : _spriteSystem.components)
    {
        delete spr.second;
    }
    for (auto &ren : _renderSystem.components)
    {
        delete ren.second;
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
                _positionSystem.components[5]->x = _mouse_x;
                _positionSystem.components[5]->y = _mouse_y;
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
                _spriteSystem.components[3]->SetAnimation("Test");
               der = false;
            }else
            {
                _spriteSystem.components[3]->SetAnimation("Test1");
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
        _positionSystem.components[5]->y -= 1;
    }
    if ( currentKeyStates[SDL_SCANCODE_DOWN] )
    {
        _positionSystem.components[5]->y += 1;
    }
    if ( currentKeyStates[SDL_SCANCODE_LEFT] )
    {
        _spriteSystem.components[SPRITE_LATIN_UNI]->SetTextMode( RSprite::TEXT );
        _spriteSystem.components[3]->SetTextMode( RSprite::TEXT );
        _positionSystem.components[5]->x -= 1;
    }
    if ( currentKeyStates[SDL_SCANCODE_RIGHT] )
    {
        _spriteSystem.components[SPRITE_LATIN_UNI]->SetTextMode( RSprite::UNICODE );
        _spriteSystem.components[3]->SetTextMode( RSprite::UNICODE );
        _positionSystem.components[5]->x += 1;
    }
}

void TestState::Update(RGameEngine* game)
{
    //calculate fps
    int thisT = _timerSystem.components[0]->GetTicks();
    static int lastT;
    _ms =  thisT - lastT;
    lastT = thisT;
    _fps = _count / (thisT / 1000.f);
    
    for(auto &s : _spriteSystem.components)
    {
        s.second->UpdateAnimation();
    }
    
    //keep player in bounds
    if( _positionSystem.components[5]->x > _windows[0]->GetWidth()  - _spriteSystem.components[SPRITE_LATIN_UNI]->GetWidth())
    {
        _positionSystem.components[5]->x -= 1;
    }else if ( _positionSystem.components[5]->x < 0)
    {
        _positionSystem.components[5]->x += 1;
    }
    if( _positionSystem.components[5]->y > _windows[0]->GetHeight()  - _spriteSystem.components[SPRITE_LATIN_UNI]->GetHeight())
    {
        _positionSystem.components[5]->y -= 1;
    }else if ( _positionSystem.components[5]->y < 0)
    {
        _positionSystem.components[5]->y += 1;
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
    _spriteSystem.components[SPRITE_LATIN_TEXT]->RenderSymbol(_windows[0]->renderer, 0, _windows[0]->GetHeight()  - _spriteSystem.components[SPRITE_LATIN_TEXT]->GetHeight(), msg.str());
    msg.str(string());
    msg << "fps:" << std::setfill('0') << std::setw(5) << _fps << " ms:" << _ms;
    _spriteSystem.components[SPRITE_LATIN_TEXT]->RenderSymbol(_windows[0]->renderer, _windows[0]->GetWidth()  - msg.str().size() * _spriteSystem.components[SPRITE_LATIN_TEXT]->GetWidth()  , 0 , msg.str());
    
    //render input text
    _spriteSystem.components[SPRITE_LATIN_TEXT]->RenderSymbol(_windows[0]->renderer, _windows[0]->GetWidth()  / 2 - (32 * _spriteSystem.components[SPRITE_LATIN_TEXT]->GetWidth() ) / 2, _windows[0]->GetHeight()  / 2 - _spriteSystem.components[SPRITE_LATIN_TEXT]->GetHeight(), _input,_spriteSystem.components[SPRITE_LATIN_TEXT]->GetWidth() * 32);
   
    //render test sprites:
    //latin set text
    _spriteSystem.components[SPRITE_LATIN_UNI]->RenderSymbol(_windows[0]->renderer, 0 , _spriteSystem.components[SPRITE_LATIN_UNI]->GetHeight(), _latin, _spriteSystem.components[SPRITE_LATIN_UNI]->GetWidth() * 16 );
    _spriteSystem.components[SPRITE_LATIN_TEXT]->RenderSymbol(_windows[0]->renderer, _spriteSystem.components[SPRITE_LATIN_TEXT]->GetWidth() + _spriteSystem.components[SPRITE_LATIN_UNI]->GetWidth() * 16 , _spriteSystem.components[SPRITE_LATIN_TEXT]->GetHeight(), _latin, _spriteSystem.components[SPRITE_LATIN_TEXT]->GetWidth() * 16 );
   
    //test sprites
    _spriteSystem.components[3]->Render(_windows[0]->renderer, 0 , 0);
    _spriteSystem.components[4]->Render(_windows[0]->renderer, _windows[0]->GetWidth()  - _spriteSystem.components[4]->GetWidth() , _windows[0]->GetHeight()  - _spriteSystem.components[4]->GetHeight());
    
    for (auto &ren : _renderSystem.components)
    {
        ren.second->Render(_windows[0]->renderer);
    }

    SDL_RenderPresent( _windows[0]->renderer );
    _count++;
} 
