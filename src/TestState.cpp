#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "TestState.h"
#include "r_SDL.h"
#include "r_utils.h"
#include "r_renderer.h"

using namespace std;

TestState TestState::_TestState;

EntityID BACKGROUND_TEXTURE, UNICODE_TEXTURE, TESTSPRITE_1, TESTSPRITE_2, TESTSPRITE_3, TESTPLAYER, TESTTIMER, TESTTEXTURE_1, TESTTEXTURE_2, TESTTEXT;

vector<EntityID> testchars;

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
    UNICODE_LATIN_SET = CreateEntity();
    _unicodeSymbolSystem.AddComponent(r_component::Create("UnicodeSymbolComponent", UNICODE_LATIN_SET), UNICODE_LATIN_SET);
    _unicodeSymbolSystem.components[UNICODE_LATIN_SET]->symbols = r_utils::HexStringToUnicode(data, ",");
    
    //setup font
    int pnt = 16;
    _font = r_SDL::LoadFont("data/font/unifont-8.0.01.ttf", pnt);
    
    //load background texture and everything needed to render
    BACKGROUND_TEXTURE = CreateEntity();
    _textureSystem.AddComponent(r_component::Create("TextureComponent", BACKGROUND_TEXTURE), BACKGROUND_TEXTURE);
    _textureSystem.LoadFromFile(BACKGROUND_TEXTURE, "data/gfx/checker.png", _windows[0]->renderer);
    //create metadata
    _dimensionsSystem.AddComponent(r_component::Create("WHComponent", BACKGROUND_TEXTURE), BACKGROUND_TEXTURE);
    _dimensionsSystem.components[BACKGROUND_TEXTURE]->w = _textureSystem.components[BACKGROUND_TEXTURE]->width;
    _dimensionsSystem.components[BACKGROUND_TEXTURE]->h = _textureSystem.components[BACKGROUND_TEXTURE]->height;

    _bgColorSystem.AddComponent(r_component::Create("ColorComponent", BACKGROUND_TEXTURE), BACKGROUND_TEXTURE);
    _bgColorSystem.components[BACKGROUND_TEXTURE]->SetColor({0x00,0x00,0x00,0x00});
    
    _fgColorSystem.AddComponent(r_component::Create("ColorComponent", BACKGROUND_TEXTURE), BACKGROUND_TEXTURE);
    _fgColorSystem.components[BACKGROUND_TEXTURE]->SetColor({0xFF,0xFF,0xFF,0xFF});   
    
    _animationSystem.AddComponent(r_component::Create("AnimationComponent",BACKGROUND_TEXTURE), BACKGROUND_TEXTURE);
    _animationSystem.AddAnimation(BACKGROUND_TEXTURE, "TEST",{{0,0,_dimensionsSystem.components[BACKGROUND_TEXTURE]->w ,_dimensionsSystem.components[BACKGROUND_TEXTURE]->h }});
    _animationSystem.SetAnimation(BACKGROUND_TEXTURE,"TEST");
    
    //create sprite for background texture
    _spriteSystem.AddComponent(r_component::Create("SpriteComponent", BACKGROUND_TEXTURE),
                                BACKGROUND_TEXTURE, 
                                BACKGROUND_TEXTURE, 
                                BACKGROUND_TEXTURE, 
                                BACKGROUND_TEXTURE, 
                                BACKGROUND_TEXTURE, 
                                BACKGROUND_TEXTURE);

    _positionSystem.AddComponent(r_component::Create("XYZComponent", BACKGROUND_TEXTURE), BACKGROUND_TEXTURE);
    _positionSystem.components[BACKGROUND_TEXTURE]->x = 0;
    _positionSystem.components[BACKGROUND_TEXTURE]->y = 0;
    
  //  _renderSystem.AddComponent(r_component::Create("RenderComponent", BACKGROUND_TEXTURE), BACKGROUND_TEXTURE, _positionSystem, _spriteSystem, true);
    
    //create rendered unicode sheet for basic latin set
    UNICODE_TEXTURE = CreateEntity();
    _textureSystem.AddComponent(r_component::Create("TextureComponent", UNICODE_TEXTURE), UNICODE_TEXTURE);
    _textureSystem.RenderUnicode(UNICODE_TEXTURE, _windows[0]->renderer, _font, &_unicodeSymbolSystem.components[UNICODE_LATIN_SET]->symbols[0]);
    
    //create metadata for latin set
    _dimensionsSystem.AddComponent(r_component::Create("WHComponent", UNICODE_TEXTURE), UNICODE_TEXTURE);
    _dimensionsSystem.components[UNICODE_TEXTURE]->w = pnt/2;
    _dimensionsSystem.components[UNICODE_TEXTURE]->h = pnt;
    
    _fgColorSystem.AddComponent(r_component::Create("ColorComponent", UNICODE_TEXTURE), UNICODE_TEXTURE);
    _fgColorSystem.components[UNICODE_TEXTURE]->SetColor({0x80,0x00,0xFF,0xFF}); 
    
    _bgColorSystem.AddComponent(r_component::Create("ColorComponent", UNICODE_TEXTURE), UNICODE_TEXTURE);
    _bgColorSystem.components[UNICODE_TEXTURE]->SetColor({0x00,0x00,0x00,0xFF});
    /*
    //create sprites
    vector<SDL_Rect> uniframes;
    int i = 0, r = 0;
    for (auto &s : _unicodeSymbolSystem.components[UNICODE_LATIN_SET]->symbols)
    {   
        uniframes.push_back({_unicodeSymbolSystem.components[UNICODE_LATIN_SET]->GetIndex(s) * _dimensionsSystem.components[UNICODE_TEXTURE]->w, 0, _dimensionsSystem.components[UNICODE_TEXTURE]->w, _dimensionsSystem.components[UNICODE_TEXTURE]->h});
        //create test character renderers
        testchars.push_back(CreateEntity());
        
        _dimensionsSystem.AddComponent(r_component::Create("WHComponent", testchars.back()), testchars.back());
        _dimensionsSystem.components[testchars.back()]->w = 16;
        _dimensionsSystem.components[testchars.back()]->h = 16;
        
        _animationSystem.AddComponent(r_component::Create("AnimationComponent",testchars.back() ), testchars.back());
        
        _spriteSystem.AddComponent(r_component::Create("SpriteComponent", testchars.back()), 
                                    testchars.back(),
                                    _textureSystem.components[UNICODE_TEXTURE],
                                    _animationSystem.components[testchars.back()], 
                                    _dimensionsSystem.components[testchars.back()], 
                                    _fgColorSystem.components[UNICODE_TEXTURE], 
                                    _bgColorSystem.components[UNICODE_TEXTURE]);
        _spriteSystem.components[testchars.back()]->renderOffsetX = _dimensionsSystem.components[UNICODE_TEXTURE]->w / 2;
        
        _positionSystem.AddComponent(r_component::Create("XYZComponent", testchars.back()), testchars.back());
        _positionSystem.components[testchars.back()]->x = 0 + (i % 16) * _dimensionsSystem.components[testchars.back()]->w;
        _positionSystem.components[testchars.back()]->y = 0 + r * _dimensionsSystem.components[testchars.back()]->h;
        
//renderSystem.AddComponent(r_component::Create("RenderComponent", testchars.back()), testchars.back(), _positionSystem, _spriteSystem, true);
    
        i++;       
        if(i % 16 == 0)
        {
            r++;
        }
    }
    i = 0;
    for (auto &s : testchars)
    {
        _animationSystem.components[s]->AddAnimation("SYMBOLS",uniframes);
        _animationSystem.components[s]->SetAnimation("SYMBOLS");
        _animationSystem.components[s]->SetFrame(i);
        i++;
    }
    
    //create custom unicode test sprite
    TESTTEXTURE_1 = CreateEntity();
    _unicodeSymbolSystem.AddComponent(r_component::Create("UnicodeSymbolComponent", TESTTEXTURE_1), TESTTEXTURE_1);
    _unicodeSymbolSystem.components[TESTTEXTURE_1]->symbols = {{0x263A, 0x263B}};
    _textureSystem.AddComponent(r_component::Create("RTexture", TESTTEXTURE_1), TESTTEXTURE_1);
    _textureSystem.components[TESTTEXTURE_1]->RenderUnicode(_windows[0]->renderer, &_unicodeSymbolSystem.components[TESTTEXTURE_1]->symbols[0], _font);

    _dimensionsSystem.AddComponent(r_component::Create("WHComponent", TESTTEXTURE_1), TESTTEXTURE_1);
    _dimensionsSystem.components[TESTTEXTURE_1]->w = pnt/2;
    _dimensionsSystem.components[TESTTEXTURE_1]->h = pnt;
    
    _fgColorSystem.AddComponent(r_component::Create("ColorComponent", TESTTEXTURE_1), TESTTEXTURE_1);
    _fgColorSystem.components[TESTTEXTURE_1]->SetColor({0x80,0x00,0xFF,0xFF}); 

    _bgColorSystem.AddComponent(r_component::Create("ColorComponent", TESTTEXTURE_1), TESTTEXTURE_1);
    _bgColorSystem.components[TESTTEXTURE_1]->SetColor({0x00,0x00,0x00,0xFF});
    
    _animationSystem.AddComponent(r_component::Create("AnimationComponent",TESTTEXTURE_1 ), TESTTEXTURE_1);
    _animationSystem.components[TESTTEXTURE_1]->AddAnimation("TEST", {{ _dimensionsSystem.components[TESTTEXTURE_1]->w * _unicodeSymbolSystem.components[TESTTEXTURE_1]->GetIndex(0x263A), 0, _dimensionsSystem.components[TESTTEXTURE_1]->w, _dimensionsSystem.components[TESTTEXTURE_1]->h },
                                                                   { _dimensionsSystem.components[TESTTEXTURE_1]->w * _unicodeSymbolSystem.components[TESTTEXTURE_1]->GetIndex(0x263B), 0, _dimensionsSystem.components[TESTTEXTURE_1]->w, _dimensionsSystem.components[TESTTEXTURE_1]->h }} );
    _animationSystem.components[TESTTEXTURE_1]->SetAnimation("TEST");
    _animationSystem.components[TESTTEXTURE_1]->animationSpeed = 30;
    
    _spriteSystem.AddComponent(r_component::Create("SpriteComponent", TESTTEXTURE_1), 
                                TESTTEXTURE_1, 
                                _textureSystem.components[TESTTEXTURE_1], 
                                _animationSystem.components[TESTTEXTURE_1], 
                                _dimensionsSystem.components[TESTTEXTURE_1], 
                                _fgColorSystem.components[TESTTEXTURE_1], 
                                _bgColorSystem.components[TESTTEXTURE_1]);

    _positionSystem.AddComponent(r_component::Create("XYZComponent", TESTTEXTURE_1), TESTTEXTURE_1);
    _positionSystem.components[TESTTEXTURE_1]->x = _windows[0]->GetWidth() - _dimensionsSystem.components[TESTTEXTURE_1]->w;
    _positionSystem.components[TESTTEXTURE_1]->y = _windows[0]->GetHeight() - _dimensionsSystem.components[TESTTEXTURE_1]->h;
   
  //  _renderSystem.AddComponent(r_component::Create("RenderComponent", TESTTEXTURE_1), TESTTEXTURE_1, _positionSystem, _spriteSystem, true);
   
    */
    
    //create "player" entity
    TESTPLAYER = CreateEntity();
    
    _textureSystem.AddComponent(r_component::Create("TextureComponent", TESTPLAYER), TESTPLAYER);
    _textureSystem.LoadFromFile(TESTPLAYER, "data/gfx/curses_square_16x16.png", _windows[0]->renderer, {0xFF,0x00,0xFF,0xFF});
    
    _positionSystem.AddComponent(r_component::Create("XYZComponent", TESTPLAYER), TESTPLAYER);
    _positionSystem.components[TESTPLAYER]->x = _windows[0]->GetWidth()  / 2;
    _positionSystem.components[TESTPLAYER]->y = _windows[0]->GetHeight() / 2;
    
    _velocitySystem.AddComponent(r_component::Create("XYZComponent", TESTPLAYER), TESTPLAYER);
    _velocitySystem.components[TESTPLAYER]->x = 0;
    _velocitySystem.components[TESTPLAYER]->y = 0;
    //create metadata
    _dimensionsSystem.AddComponent(r_component::Create("WHComponent", TESTPLAYER), TESTPLAYER);
    _dimensionsSystem.components[TESTPLAYER]->w = 16;
    _dimensionsSystem.components[TESTPLAYER]->h = 16;
    
    _bgColorSystem.AddComponent(r_component::Create("ColorComponent", TESTPLAYER), TESTPLAYER);
    _bgColorSystem.components[TESTPLAYER]->SetColor({0xBA,0xDA,0x55,0xFF});
    
    _fgColorSystem.AddComponent(r_component::Create("ColorComponent", TESTPLAYER), TESTPLAYER);
    _fgColorSystem.components[TESTPLAYER]->SetColor({0x80,0x00,0xFF,0xFF});
    
    _animationSystem.AddComponent(r_component::Create("AnimationComponent",TESTPLAYER ), TESTPLAYER);
    _animationSystem.AddAnimation(TESTPLAYER, "TEST1",{{16,0,16,16},{32,0,16,16}});
    _animationSystem.SetAnimation(TESTPLAYER, "TEST1");
    _animationSystem.components[TESTPLAYER]->animationSpeed = 30;
    
    //create sprite
    _spriteSystem.AddComponent(r_component::Create("SpriteComponent", TESTPLAYER), 
                                TESTPLAYER, 
                                TESTPLAYER, 
                                TESTPLAYER, 
                                TESTPLAYER, 
                                TESTPLAYER, 
                                TESTPLAYER);
    //setup timer
    TESTTIMER = CreateEntity();
    _timerSystem.AddComponent(r_component::Create("RTimer", TESTTIMER), TESTTIMER);
    _timerSystem.components[TESTTIMER]->Start();
    
    TTF_CloseFont(_font);
    //start input
    SDL_StartTextInput();    
    currentKeyStates = SDL_GetKeyboardState(NULL);
    
    
    
    TESTTEXT = CreateEntity();
    _stringSystem.AddComponent(r_component::Create("StringComponent", TESTTEXT), TESTTEXT);
    _stringSystem.components[TESTTEXT]->text = L"Hello World";
    _positionSystem.AddComponent(r_component::Create("XYZComponent",TESTTEXT), TESTTEXT);
    _positionSystem.components[TESTTEXT]->x = 240;
    _positionSystem.components[TESTTEXT]->y = 240;
    _dimensionsSystem.AddComponent(r_component::Create("WHComponent",TESTTEXT), TESTTEXT);
    _dimensionsSystem.components[TESTTEXT]->w = 240;
    _dimensionsSystem.components[TESTTEXT]->h = 240;
}

void TestState::Cleanup(RGameEngine* game)
{
    for (auto &win : _windows)
    {
        delete win;
    }
    _spriteSystem.Cleanup();
    _textureSystem.Cleanup();
    _animationSystem.Cleanup();
    _timerSystem.Cleanup();
    _fgColorSystem.Cleanup();
    _bgColorSystem.Cleanup();
    _positionSystem.Cleanup();
    _velocitySystem.Cleanup();
    _dimensionsSystem.Cleanup();
    _unicodeSymbolSystem.Cleanup();   
    
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
                der = false;
            }else
            {
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
        _velocitySystem.components[TESTPLAYER]->x -= 1;
    }
    if ( currentKeyStates[SDL_SCANCODE_RIGHT] )
    {
        _velocitySystem.components[TESTPLAYER]->x += 1;
    }
}

void TestState::Update(RGameEngine* game)
{
    
    //update sprite animations
    _animationSystem.Update();
    
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
            _positionSystem.components[c.first]->x += c.second->x;
            _positionSystem.components[c.first]->y += c.second->y;
        }
    }
 
    //keep player in bounds
    if( _positionSystem.components[TESTPLAYER]->x > _windows[0]->GetWidth()  - _dimensionsSystem.components[TESTPLAYER]->w)
    {
        _velocitySystem.components[TESTPLAYER]->x = -1 * abs(_velocitySystem.components[TESTPLAYER]->x);
    }else if ( _positionSystem.components[TESTPLAYER]->x < 0)
    {
        _velocitySystem.components[TESTPLAYER]->x = abs(_velocitySystem.components[TESTPLAYER]->x);
    }
    if( _positionSystem.components[TESTPLAYER]->y > _windows[0]->GetHeight()  - _dimensionsSystem.components[TESTPLAYER]->h)
    {
        _velocitySystem.components[TESTPLAYER]->y = -1 * abs(_velocitySystem.components[TESTPLAYER]->y);
    }else if ( _positionSystem.components[TESTPLAYER]->y < 0)
    {
        _velocitySystem.components[TESTPLAYER]->y = abs(_velocitySystem.components[TESTPLAYER]->y);
    }
}

void TestState::Draw(RGameEngine* game)
{   
    r_renderer::AddToQueue(_textureSystem.components[TESTPLAYER]->texture, _animationSystem.GetCurrentFrame(TESTPLAYER), {_positionSystem.components[TESTPLAYER]->x,_positionSystem.components[TESTPLAYER]->y,_dimensionsSystem.components[TESTPLAYER]->w,_dimensionsSystem.components[TESTPLAYER]->h}, {0x80,0x00,0xFF,0xFF});
    r_renderer::AddToQueue(_textureSystem.components[BACKGROUND_TEXTURE]->texture, {0,0,640,480}, {0,0,640,480});
    
    r_renderer::Render(_windows[0]->renderer);
    
    _count++;
} 
