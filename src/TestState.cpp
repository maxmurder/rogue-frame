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

EntityID BACKGROUND_TEXTURE, UNICODE_TEXTURE, TESTSPRITE_1, TESTSPRITE_2, TESTSPRITE_3, TESTPLAYER, TESTTIMER, TESTTEXTURE_1, TESTTEXTURE_2, PARTICLE;

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
    _components.push_back(r_component::Create("RTexture", BACKGROUND_TEXTURE));
    _textureSystem.AddComponent(_components.back(), BACKGROUND_TEXTURE);
    _textureSystem.components[BACKGROUND_TEXTURE]->LoadFromFile("data/gfx/checker.png", _windows[0]->renderer);
    
    UNICODE_TEXTURE = CreateEntity();
    //create rendered unicode sheet for basic latin set
    _components.push_back(r_component::Create("RTexture", UNICODE_TEXTURE));
    _textureSystem.AddComponent(_components.back(), UNICODE_TEXTURE);
    _textureSystem.components[UNICODE_TEXTURE]->RenderUnicode(_windows[0]->renderer, &_latin[0], _font);
        
    //create sprite for basic latin set
    SPRITE_LATIN_UNI = CreateEntity();
    _components.push_back(r_component::Create("RSprite", SPRITE_LATIN_UNI));
    _spriteSystem.AddComponent(_components.back(), SPRITE_LATIN_UNI);
    _spriteSystem.components[SPRITE_LATIN_UNI]->Init(_textureSystem.components[UNICODE_TEXTURE], _font, pnt, _latin, 2 );
    _spriteSystem.components[SPRITE_LATIN_UNI]->SetForeground({0x80,0x00,0xFF,0xFF});
    _spriteSystem.components[SPRITE_LATIN_UNI]->SetBackground({0x00,0x00,0x00,0xFF});
    
    //create text style (rectangular) unicode sprite for latin set
    SPRITE_LATIN_TEXT = CreateEntity();
    _components.push_back(r_component::Create("RSprite", SPRITE_LATIN_TEXT));
    _spriteSystem.AddComponent(_components.back(), SPRITE_LATIN_TEXT);
    _spriteSystem.components[SPRITE_LATIN_TEXT]->Init(_textureSystem.components[UNICODE_TEXTURE], _font, pnt, _latin );
    _spriteSystem.components[SPRITE_LATIN_TEXT]->SetForeground({0x80,0x00,0xFF,0xFF});
    _spriteSystem.components[SPRITE_LATIN_TEXT]->SetBackground({0x00,0x00,0x00,0xFF});
    
    //generate custom spritesheet using unicode
    vector<uint16_t> sym = {0x263A,0x263B,0x007C,0x005C,0x2500,0x002F};
    uint16_t *symArray =  &sym[0];
    TESTTEXTURE_1 = CreateEntity();
    _components.push_back(r_component::Create("RTexture", TESTTEXTURE_1));
    _textureSystem.AddComponent(_components.back(), TESTTEXTURE_1);
    _textureSystem.components[TESTTEXTURE_1]->RenderUnicode( _windows[0]->renderer, symArray, _font );
    TESTSPRITE_1 = CreateEntity();
    _components.push_back(r_component::Create("RSprite", TESTSPRITE_1));
    _spriteSystem.AddComponent(_components.back(), TESTSPRITE_1);
    _spriteSystem.components[TESTSPRITE_1]->Init(_textureSystem.components[TESTTEXTURE_1], _font, pnt, sym);
    _spriteSystem.components[TESTSPRITE_1]->AddUnicodeAnimation("Test", {0x263A,0x263B});
    _spriteSystem.components[TESTSPRITE_1]->AddUnicodeAnimation("Test1", {sym[2],sym[3],sym[4],sym[5]});
    _spriteSystem.components[TESTSPRITE_1]->SetAnimation("Test");
    _spriteSystem.components[TESTSPRITE_1]->SetForeground({0x80,0x00,0xFF,0xFF});
    _spriteSystem.components[TESTSPRITE_1]->SetBackground({0xBA,0xDA,0x55,0xFF});

    //create spritesheet from png
    TESTTEXTURE_2 = CreateEntity();
    _components.push_back(r_component::Create("RTexture", TESTTEXTURE_2));
    _textureSystem.AddComponent(_components.back(), TESTTEXTURE_2);
    _textureSystem.components[TESTTEXTURE_2]->LoadFromFile("data/gfx/curses_square_16x16.png", _windows[0]->renderer, 0xFF, 0x00, 0xFF);
       
    //create list of frames
    vector<SDL_Rect> frames = {{16,0,16,16},{32,0,16,16}};
    
    //create "player" entity
    TESTPLAYER = CreateEntity();
    _components.push_back(r_component::Create("XYZComponent", TESTPLAYER));
    _positionSystem.AddComponent(_components.back(), TESTPLAYER);
    _positionSystem.components[TESTPLAYER]->x = _windows[0]->GetWidth()  / 2;
    _positionSystem.components[TESTPLAYER]->y = _windows[0]->GetHeight() / 2;
    _components.push_back(r_component::Create("XYZComponent", TESTPLAYER));
    _velocitySystem.AddComponent(_components.back(), TESTPLAYER);
    _velocitySystem.components[TESTPLAYER]->x = 0;
    _velocitySystem.components[TESTPLAYER]->y = 0;
    _components.push_back(r_component::Create("RSprite", TESTPLAYER));
    _spriteSystem.AddComponent(_components.back(), TESTPLAYER);
    _spriteSystem.components[TESTPLAYER]->Init(_textureSystem.components[TESTTEXTURE_2], frames);
    _spriteSystem.components[TESTPLAYER]->SetForeground({0x80,0x00,0xFF,0xFF});
    _spriteSystem.components[TESTPLAYER]->SetBackground({0xBA,0xDA,0x55,0xFF});
    _components.push_back(r_component::Create("RenderComponent", TESTPLAYER));
    _renderSystem.AddComponent(_components.back(), TESTPLAYER);
    _renderSystem.components[TESTPLAYER]->Init(_positionSystem,_spriteSystem);
    
    //setup timer
    TESTTIMER = CreateEntity();
    _components.push_back(r_component::Create("RTimer", TESTTIMER));
    _timerSystem.AddComponent(_components.back(), TESTTIMER);
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
    for (auto &comp : _components)
    {
        r_component::Destroy(comp);
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
        _velocitySystem.components[TESTPLAYER]->y -= 1;
    }
    if ( currentKeyStates[SDL_SCANCODE_DOWN] )
    {
        _velocitySystem.components[TESTPLAYER]->y += 1;
    }
    if ( currentKeyStates[SDL_SCANCODE_LEFT] )
    {
        _spriteSystem.components[SPRITE_LATIN_UNI]->SetTextMode( RSprite::TEXT );
        _spriteSystem.components[TESTSPRITE_1]->SetTextMode( RSprite::TEXT );
        _velocitySystem.components[TESTPLAYER]->x -= 1;
    }
    if ( currentKeyStates[SDL_SCANCODE_RIGHT] )
    {
        _spriteSystem.components[SPRITE_LATIN_UNI]->SetTextMode( RSprite::UNICODE );
        _spriteSystem.components[TESTSPRITE_1]->SetTextMode( RSprite::UNICODE );
        _velocitySystem.components[TESTPLAYER]->x += 1;
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
    
    //apply vleocity
    for(auto &c : _velocitySystem.components)
    {
        if(GetEntity(c.second->ownerID)!=NULL)
        {
            _positionSystem.components[c.second->ownerID]->x += c.second->x;
            _positionSystem.components[c.second->ownerID]->y += c.second->y;
        }
    }
    
        //update sprite animations
    for(auto &c : _spriteSystem.components)
    {
        if(GetEntity(c.second->ownerID)!=NULL)
        {
            c.second->UpdateAnimation();
        }
    }
    
    //keep player in bounds
    if( _positionSystem.components[TESTPLAYER]->x > _windows[0]->GetWidth()  - _spriteSystem.components[TESTPLAYER]->GetWidth())
    {
        _velocitySystem.components[TESTPLAYER]->x = -1 * abs(_velocitySystem.components[TESTPLAYER]->x);
    }else if ( _positionSystem.components[TESTPLAYER]->x < 0)
    {
        _velocitySystem.components[TESTPLAYER]->x = abs(_velocitySystem.components[TESTPLAYER]->x);
    }
    if( _positionSystem.components[TESTPLAYER]->y > _windows[0]->GetHeight()  - _spriteSystem.components[TESTPLAYER]->GetHeight())
    {
        _velocitySystem.components[TESTPLAYER]->y = -1 * abs(_velocitySystem.components[TESTPLAYER]->y);
    }else if ( _positionSystem.components[TESTPLAYER]->y < 0)
    {
        _velocitySystem.components[TESTPLAYER]->y = abs(_velocitySystem.components[TESTPLAYER]->y);
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
    
    msg.str(string());
    msg << "Entities: " << NumEntities() << " Free: " << NumFree();
    _spriteSystem.components[SPRITE_LATIN_TEXT]->RenderSymbol(_windows[0]->renderer, _windows[0]->GetWidth()  - msg.str().size() * _spriteSystem.components[SPRITE_LATIN_TEXT]->GetWidth()  , _spriteSystem.components[SPRITE_LATIN_TEXT]->GetHeight() , msg.str());
    
    //render input text
    _spriteSystem.components[SPRITE_LATIN_TEXT]->RenderSymbol(_windows[0]->renderer, _windows[0]->GetWidth()  / 2 - (32 * _spriteSystem.components[SPRITE_LATIN_TEXT]->GetWidth() ) / 2, _windows[0]->GetHeight()  / 2 - _spriteSystem.components[SPRITE_LATIN_TEXT]->GetHeight(), _input,_spriteSystem.components[SPRITE_LATIN_TEXT]->GetWidth() * 32);
   
    //render test sprites:
    //latin set text
    _spriteSystem.components[SPRITE_LATIN_UNI]->RenderSymbol(_windows[0]->renderer, 0 , _spriteSystem.components[SPRITE_LATIN_UNI]->GetHeight(), _latin, _spriteSystem.components[SPRITE_LATIN_UNI]->GetWidth() * 16 );
    _spriteSystem.components[SPRITE_LATIN_TEXT]->RenderSymbol(_windows[0]->renderer, _spriteSystem.components[SPRITE_LATIN_TEXT]->GetWidth() + _spriteSystem.components[SPRITE_LATIN_UNI]->GetWidth() * 16 , _spriteSystem.components[SPRITE_LATIN_TEXT]->GetHeight(), _latin, _spriteSystem.components[SPRITE_LATIN_TEXT]->GetWidth() * 16 );

    //test sprites
    _spriteSystem.components[TESTSPRITE_1]->Render(_windows[0]->renderer, 0 , 0);

    //render system
    for (auto &ren : _renderSystem.components)
    {
        if(GetEntity(ren.second->ownerID) != NULL)
        {
            ren.second->Render(_windows[0]->renderer);
        }   
    }
    
    SDL_RenderPresent( _windows[0]->renderer );
    _count++;
} 
