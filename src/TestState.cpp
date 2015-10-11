#include <iostream>
#include <sstream>
#include <vector>
#include "TestState.h"
#include "r_SDL.h"

using namespace std;

TestState TestState::_TestState;

void TestState::Init(RGameEngine* game)
{   
    //setup font
    int pnt = 16;
    _font = r_SDL::LoadFont("data/font/unifont-8.0.01.ttf", pnt);
    
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
    
    //setup timer
    _timers.push_back(new RTimer());
    _timers[0]->Start();
    
    //start text input
    SDL_StartTextInput();
    _y = game->GetWindowHeight() / 2;
    _x = game->GetWindowWidth() / 2;
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
            } else if ( _event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
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
        _y-=1;
    }
    if ( currentKeyStates[SDL_SCANCODE_DOWN] )
    {
        _y+=1;
    }
    if ( currentKeyStates[SDL_SCANCODE_LEFT] )
    {
        _x-=1;
    }
    if ( currentKeyStates[SDL_SCANCODE_RIGHT] )
    {
        _x+=1;
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
}

void TestState::Draw(RGameEngine* game)
{
    SDL_SetRenderDrawColor( game->renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( game->renderer );
    
    //render background
    _textures[0]->Render(game->renderer, 0, 0);
    
    //render mouse and fps
    stringstream msg;
    msg.precision(4);
    msg << "x:" << _mouse_x << " y:" << _mouse_y;
    _sprites[0]->RenderSymbol(game->renderer, 0, game->GetWindowHeight() - _sprites[0]->GetHeight(), msg.str());
    msg.str(std::string());
    msg << "fps:" << _fps << " ms:" << _ms;
    _sprites[0]->RenderSymbol(game->renderer, game->GetWindowWidth() - msg.str().size() * _sprites[0]->GetWidth()  , 0 , msg.str());
    
    //render test sprites
    _sprites[1]->Render(game->renderer, 0 , 0);
    _sprites[2]->Render(game->renderer, game->GetWindowWidth() - _sprites[2]->GetWidth() , game->GetWindowHeight() - _sprites[2]->GetHeight());
    _sprites[0]->RenderSymbol(game->renderer, _x, _y, '@');
    
    
    //render test latin set
    string latin;
    for( auto &s : UNICODE_LATIN_BASIC)
    {
        latin += s;
    }
    _sprites[0]->RenderSymbol(game->renderer, 0 , _sprites[0]->GetHeight(), latin, game->GetWindowWidth() );
    
    //render input text
    _sprites[0]->RenderSymbol(game->renderer, game->GetWindowWidth() / 2 - ( _input.size() * _sprites[0]->GetWidth() ) / 2, game->GetWindowHeight() / 2 - _sprites[0]->GetHeight(), _input );
    
    SDL_RenderPresent( game->renderer );
    _count++;
} 
