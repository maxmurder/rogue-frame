#include <iostream>
#include "r_engine.h"
#include "r_gamestate.h"

using namespace std;

bool RGameEngine::Init(const char* title, int width, int height, int bpp, bool fullscreen) 
{
    int flags = 0;    
    
    //initialize SDL
    if (SDL_Init( SDL_INIT_EVERYTHING ) == -1) 
    {
        cout << "SDL initilization failure\n";
        return false;
    }

    if ( fullscreen ) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    //initialize window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags );
    if (window == NULL)
    {
        cout << "Error setting up SDL window\n";
        return false;
    }
    screen = SDL_GetWindowSurface( window );
    if (screen == NULL) 
    {
        cout << "Error setting up SDL screen\n";
        return false;
    }
    
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
    
    // release fullscreen mode
    if (m_fullscreen) 
    {}
    
    SDL_DestroyWindow( window );
    SDL_Quit();
    
    cout << "RGameEngine Cleanup\n";
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
