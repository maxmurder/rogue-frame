#include <signal.h>
#include "r_engine.h"
#include "r_gamestate.h"

using namespace std;

void RGameEngine::Init() 
{
    screen = new r_curses::r_screen();
    signal(SIGWINCH,screen->resizeHandler);
}

void RGameEngine::Cleanup() 
{
    while ( !states.empty() ) 
    {
        states.back()->Cleanup();
        states.pop_back();
    }
    delete screen;
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
