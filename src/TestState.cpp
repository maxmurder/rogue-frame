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

EntityID BACKGROUND_TEXTURE, UNICODE_TEXTURE, TESTSPRITE_1, TESTSPRITE_2, TESTSPRITE_3, TESTPLAYER, TESTTIMER, TESTTEXTURE_1, TESTTEXTURE_2;

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
    BACKGROUND_TEXTURE = CreateEntity();
    _textureSystem.components[BACKGROUND_TEXTURE] = new RTexture(BACKGROUND_TEXTURE);
    _textureSystem.components[BACKGROUND_TEXTURE]->LoadFromFile("data/gfx/checker.png", _windows[0]->renderer);
    
    UNICODE_TEXTURE = CreateEntity();
    //create rendered unicode sheet for basic latin set
    _textureSystem.components[UNICODE_TEXTURE] = new RTexture(UNICODE_TEXTURE);
    _textureSystem.components[UNICODE_TEXTURE]->RenderUnicode(_windows[0]->renderer, &_latin[0], _font);
        
    //create sprite for basic latin set
    SPRITE_LATIN_UNI = CreateEntity();
    _spriteSystem.components[SPRITE_LATIN_UNI] = new RSprite(SPRITE_LATIN_UNI);
    _spriteSystem.components[SPRITE_LATIN_UNI]->Init(_textureSystem.components[UNICODE_TEXTURE], _font, pnt, _latin, 2 );
    _spriteSystem.components[SPRITE_LATIN_UNI]->SetForeground({0x80,0x00,0xFF,0xFF});
    _spriteSystem.components[SPRITE_LATIN_UNI]->SetBackground({0x00,0x00,0x00,0xFF});
    
    //create text style (rectangular) unicode sprite for latin set
    SPRITE_LATIN_TEXT = CreateEntity();
    _spriteSystem.components[SPRITE_LATIN_TEXT] = new RSprite(SPRITE_LATIN_TEXT);
    _spriteSystem.components[SPRITE_LATIN_TEXT]->Init(_textureSystem.components[UNICODE_TEXTURE], _font, pnt, _latin );
    _spriteSystem.components[SPRITE_LATIN_TEXT]->SetForeground({0x80,0x00,0xFF,0xFF});
    _spriteSystem.components[SPRITE_LATIN_TEXT]->SetBackground({0x00,0x00,0x00,0xFF});
    
    //generate custom spritesheet using unicode
    vector<uint16_t> sym = {0x263A,0x263B,0x007C,0x005C,0x2500,0x002F};
    uint16_t *symArray =  &sym[0];
    TESTTEXTURE_1 = CreateEntity();
    _textureSystem.components[TESTTEXTURE_1] = new RTexture(TESTTEXTURE_1);
    _textureSystem.components[TESTTEXTURE_1]->RenderUnicode( _windows[0]->renderer, symArray, _font );
    TESTSPRITE_1 = CreateEntity();
    _spriteSystem.components[TESTSPRITE_1] = new RSprite(TESTSPRITE_1);
    _spriteSystem.components[TESTSPRITE_1]->Init(_textureSystem.components[TESTTEXTURE_1], _font, pnt, sym);
    _spriteSystem.components[TESTSPRITE_1]->AddUnicodeAnimation("Test", {0x263A,0x263B});
    _spriteSystem.components[TESTSPRITE_1]->AddUnicodeAnimation("Test1", {sym[2],sym[3],sym[4],sym[5]});
    _spriteSystem.components[TESTSPRITE_1]->SetAnimation("Test");
    _spriteSystem.components[TESTSPRITE_1]->SetForeground({0x80,0x00,0xFF,0xFF});
    _spriteSystem.components[TESTSPRITE_1]->SetBackground({0xBA,0xDA,0x55,0xFF});
    
    //create unicode sprite with internal spritesheet texture
    TESTSPRITE_2 = CreateEntity();
    _spriteSystem.components[TESTSPRITE_2] = new RSprite(TESTSPRITE_2);
    _spriteSystem.components[TESTSPRITE_2]->Init(_windows[0]->renderer, &_textureSystem, _font, pnt, sym);
    _spriteSystem.components[TESTSPRITE_2]->AddUnicodeAnimation("Test", {0x263A,0x263B});
    _spriteSystem.components[TESTSPRITE_2]->AddUnicodeAnimation("Test1", {sym[2],sym[3],sym[4],sym[5]});
    _spriteSystem.components[TESTSPRITE_2]->SetAnimation("Test");
    _spriteSystem.components[TESTSPRITE_2]->SetForeground({0x80,0x00,0xFF,0xFF});
    _spriteSystem.components[TESTSPRITE_2]->SetBackground({0xBA,0xDA,0x55,0xFF});
    _spriteSystem.components[TESTSPRITE_2]->SetDimensions(24, 24);
    _spriteSystem.components[TESTSPRITE_2]->SetRenderOffset(8,4);

    //create spritesheet from png
    TESTTEXTURE_2 = CreateEntity();
    _textureSystem.components[TESTTEXTURE_2] = new RTexture(TESTTEXTURE_2);
    _textureSystem.components[TESTTEXTURE_2]->LoadFromFile("data/gfx/curses_square_16x16.png", _windows[0]->renderer, 0xFF, 0x00, 0xFF);
    
    //create list of frames
    vector<SDL_Rect> frames = {{16,0,16,16},{32,0,16,16}};
    
    //create "player" entity
    TESTPLAYER = CreateEntity();
    _positionSystem.components[TESTPLAYER] = new PositionComponent(TESTPLAYER);
    _positionSystem.components[TESTPLAYER]->x = _windows[0]->GetWidth()  / 2;
    _positionSystem.components[TESTPLAYER]->y = _windows[0]->GetHeight() / 2;
    _spriteSystem.components[TESTPLAYER] = new RSprite(TESTPLAYER);
    _spriteSystem.components[TESTPLAYER]->Init(_textureSystem.components[TESTTEXTURE_2], frames);
    _spriteSystem.components[TESTPLAYER]->SetForeground({0x80,0x00,0xFF,0xFF});
    _spriteSystem.components[TESTPLAYER]->SetBackground({0xBA,0xDA,0x55,0xFF});
    _renderSystem.components[TESTPLAYER] = new RenderComponent(TESTPLAYER, _positionSystem, _spriteSystem);
    
    //setup timer
    TESTTIMER = CreateEntity();
    _timerSystem.components[TESTTIMER] = new RTimer(TESTTIMER);
    _timerSystem.components[TESTTIMER]->Start();
    
    TTF_CloseFont(_font);

    //start input
    SDL_StartTextInput();    
    currentKeyStates = SDL_GetKeyboardState(NULL);
}

void TestState::Cleanup(RGameEngine* game)
{
    for (auto &win : _windows)
    {
        delete win;
    }
    for (auto &tex : _textureSystem.components)
    {
        delete tex.second;
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
                _positionSystem.components[TESTPLAYER]->x = _mouse_x;
                _positionSystem.components[TESTPLAYER]->y = _mouse_y;
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
                _spriteSystem.components[TESTSPRITE_1]->SetAnimation("Test");
               der = false;
            }else
            {
                _spriteSystem.components[TESTSPRITE_1]->SetAnimation("Test1");
                der = true;
            }
        }
        sp_down = true;
    }else{
        sp_down = false;
    }
    
    if ( currentKeyStates[SDL_SCANCODE_UP] )
    {
        _positionSystem.components[TESTPLAYER]->y -= 1;
    }
    if ( currentKeyStates[SDL_SCANCODE_DOWN] )
    {
        _positionSystem.components[TESTPLAYER]->y += 1;
    }
    if ( currentKeyStates[SDL_SCANCODE_LEFT] )
    {
        _spriteSystem.components[SPRITE_LATIN_UNI]->SetTextMode( RSprite::TEXT );
        _spriteSystem.components[TESTSPRITE_1]->SetTextMode( RSprite::TEXT );
        _positionSystem.components[TESTPLAYER]->x -= 1;
    }
    if ( currentKeyStates[SDL_SCANCODE_RIGHT] )
    {
        _spriteSystem.components[SPRITE_LATIN_UNI]->SetTextMode( RSprite::UNICODE );
        _spriteSystem.components[TESTSPRITE_1]->SetTextMode( RSprite::UNICODE );
        _positionSystem.components[TESTPLAYER]->x += 1;
    }
}

void TestState::Update(RGameEngine* game)
{
    //calculate fps
    int thisT = _timerSystem.components[TESTTIMER]->GetTicks();
    static int lastT;
    _ms =  thisT - lastT;
    lastT = thisT;
    _fps = _count / (thisT / 1000.f);
    
    for(auto &s : _spriteSystem.components)
    {
        s.second->UpdateAnimation();
    }
    
    //keep player in bounds
    if( _positionSystem.components[TESTPLAYER]->x > _windows[0]->GetWidth()  - _spriteSystem.components[TESTPLAYER]->GetWidth())
    {
        _positionSystem.components[TESTPLAYER]->x -= 1;
    }else if ( _positionSystem.components[TESTPLAYER]->x < 0)
    {
        _positionSystem.components[TESTPLAYER]->x += 1;
    }
    if( _positionSystem.components[TESTPLAYER]->y > _windows[0]->GetHeight()  - _spriteSystem.components[TESTPLAYER]->GetHeight())
    {
        _positionSystem.components[TESTPLAYER]->y -= 1;
    }else if ( _positionSystem.components[TESTPLAYER]->y < 0)
    {
        _positionSystem.components[TESTPLAYER]->y += 1;
    }    
}

void TestState::Draw(RGameEngine* game)
{
    SDL_SetRenderDrawColor( _windows[0]->renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( _windows[0]->renderer );
    
    //render background
    _textureSystem.components[BACKGROUND_TEXTURE]->Render(_windows[0]->renderer, 0, 0);
    
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
    _spriteSystem.components[TESTSPRITE_1]->Render(_windows[0]->renderer, 0 , 0);
    _spriteSystem.components[TESTSPRITE_2]->Render(_windows[0]->renderer, _windows[0]->GetWidth()  - _spriteSystem.components[TESTSPRITE_2]->GetWidth() , _windows[0]->GetHeight()  - _spriteSystem.components[TESTSPRITE_2]->GetHeight());
    
    //render system
    for (auto &ren : _renderSystem.components)
    {
        ren.second->Render(_windows[0]->renderer);
    }

    SDL_RenderPresent( _windows[0]->renderer );
    _count++;
} 
