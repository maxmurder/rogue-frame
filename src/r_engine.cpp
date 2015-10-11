#include <iostream>
#include "r_engine.h"
#include "r_gamestate.h"

using namespace std;

bool RGameEngine::Init(const char* title, int width, int height, int bpp, bool fullscreen) 
{
    int flags = 0;
    int imgFlag = IMG_INIT_PNG;
    
    //initialize SDL
    if (SDL_Init( SDL_INIT_EVERYTHING ) == -1) 
    {
        cout << "SDL initilization failure" << " :: " << SDL_GetError() << endl;
        return false;
    }
    if ( !(IMG_Init( imgFlag) & imgFlag ) )
    {
        cout << "SDL-IMG initilization failure" << " :: " << IMG_GetError() << endl;
        return false;
    }
    
    if ( TTF_Init() == -1 )
    {
        cout << "SDL-IMG initilization failure" << " :: " << TTF_GetError() << endl;
        return false;
    }

    if ( fullscreen ) {
        flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    
    //initialize window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags );
    if (window == NULL)
    {
        cout << "Error setting up SDL window" << " :: " << SDL_GetError() << endl;
        return false;
    }
    //initilize renderer
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if (renderer == NULL)
    {
        cout << "Error initilizing SDL renderer"  << " :: " << SDL_GetError() << endl;
        return false;
    }
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    
    m_fullscreen = fullscreen;
    m_running = true;
    
    cout << "RGameEngine Init\n";
    return true;
}

void RGameEngine::Cleanup() 
{
    while ( !states.empty() ) 
    {
        states.back()->Cleanup(this);
        states.pop_back();
    }
    
    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( renderer);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    
    cout << "RGameEngine Cleanup" << endl;
}

void RGameEngine::HandleEvents() 
{
    if( !states.empty() )
    {
        states.back()->HandleEvents(this);
    }
};

void RGameEngine::Update() 
{
    if( !states.empty() )
    {
        states.back()->Update(this);
    }
};

void RGameEngine::Draw() 
{
    if( !states.empty() )
    {
        states.back()->Draw(this);
    }
};

void RGameEngine::ChangeState(RGameState* state)
{
    //cleanup current state
    if( !states.empty() )
    {
        states.back()->Cleanup(this);
        states.pop_back();
    }

    //add and initilize new state    
    states.push_back(state);
    states.back()->Init(this);
}

void RGameEngine::PushState(RGameState* state)
{
    if ( !states.empty() ) 
    {
        states.back()->Pause(this);
    }
    
    states.push_back(state);
    states.back()->Init(this);
}

void RGameEngine::PopState()
{
    if ( !states.empty() ) {
        states.back()->Cleanup(this);
        states.pop_back();
    }
    
    if ( !states.empty() ) {
        states.back()->Resume(this);
    }
}
