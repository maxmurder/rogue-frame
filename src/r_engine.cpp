#include <iostream>
#include <signal.h>
#include "r_engine.h"
#include "r_gamestate.h"

using namespace std;

int RGameEngine::Init(const char* title, int width, int height, int bpp, bool fullscreen) 
{
    int flags = 0;    
    
    //initialize SDL
    if (SDL_Init( SDL_INIT_EVERYTHING ) == -1) 
    {
        cout << "SDL initilization failure\n";
        return 1;
    }
    SDL_WM_SetCaption(title, title);

    if ( fullscreen ) {
        flags = SDL_FULLSCREEN;
    }
    
    //setup screen
    screen = SDL_SetVideoMode(width, height, bpp, flags);
    if (screen == NULL) 
    {
        cout << "Error setting up SDL screen\n";
        return 1;
    }
    
    m_fullscreen = fullscreen;
    m_running = true;
    
    cout << "RGameEngine Init\n";
    return 0;
}

void RGameEngine::Cleanup() 
{
    while ( !states.empty() ) 
    {
        states.back()->Cleanup();
        states.pop_back();
    }
    
    // release fullscreen mode
    if (m_fullscreen) 
    {
        screen = SDL_SetVideoMode(640, 480, 0, 0);
    }
    
    cout << "RGameEngine Cleanup\n";
    
    SDL_Quit();
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
        states.back()->Cleanup();
        states.pop_back();
    }

    //add and initilize new state    
    states.push_back(state);
    states.back()->Init();
}

void RGameEngine::PushState(RGameState* state)
{
    if ( !states.empty() ) 
    {
        states.back()->Pause();
    }
    
    states.push_back(state);
    states.back()->Init();
}

void RGameEngine::PopState()
{
    if ( !states.empty() ) {
        states.back()->Cleanup();
        states.pop_back();
    }
    
    if ( !states.empty() ) {
        states.back()->Resume();
    }
}
