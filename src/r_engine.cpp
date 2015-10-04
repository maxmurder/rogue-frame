#include <signal.h>
#include "r_engine.h"
#include "r_gamestate.h"

using namespace std;

void RGameEngine::Init(const char* title, int width, int height, int bpp, bool fullscreen) 
{
    int flags = 0;    
    
    SDL_Init( SDL_INIT_VIDEO );
    
    if ( fullscreen ) {
        flags = SDL_FULLSCREEN;
    }
    screen = SDL_SetVideoMode(width, height, bpp, flags);
    
    m_fullscreen = fullscreen;
    m_running = true;
    
    printf("RGameEngine Init\n");
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
    
    printf("RGameEngine Cleanup\n");
    
    SDL_Quit();
}

void RGameEngine::HandleEvents() 
{
    states.back()->HandleEvents(this);
};

void RGameEngine::Update() 
{
    states.back()->Update(this);
};

void RGameEngine::Draw() 
{
    states.back()->Draw(this);
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
