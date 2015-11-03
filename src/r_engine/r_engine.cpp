#include <iostream>
#include "r_engine.h"
#include "r_gamestate.h"
#include "r_time.h"

using namespace std;

int RGameEngine::Init(const char* title, int width, int height, int bpp, bool fullscreen) 
{
    int imgFlag = IMG_INIT_PNG;   
    //initialize SDL
    if (SDL_Init( SDL_INIT_EVERYTHING ) == -1) 
    {
        cout << "SDL initilization failure" << " :: " << SDL_GetError() << endl;
        return 1;
    }
    if ( !(IMG_Init( imgFlag) & imgFlag ) )
    {
        cout << "SDL-IMG initilization failure" << " :: " << IMG_GetError() << endl;
        return 1;
    }
    
    if ( TTF_Init() == -1 )
    {
        cout << "SDL-IMG initilization failure" << " :: " << TTF_GetError() << endl;
        return 1;
    }

    if ( fullscreen ) {
        //todo: add fullscreen
    }
    
    _fullscreen = fullscreen;
    _running = true;
    cout << "RGameEngine Init\n";
    return 0;
}

int RGameEngine::Start()
{
    static bool started = false;
    if(!started)
    {
        started = true;
        while (_running)
        {
            if (HandleEvents() != 0) return 1;
            if (Update() != 0) return 1;
            if (Draw() != 0) return 1;
        } 
        Cleanup();
        return 0;
    }
    cout << "Somebody tried to start a running game.\n";
    return 1;
}

void RGameEngine::Cleanup() 
{
    for (auto s : states )
    {
        s->Cleanup(this);
    }
    states.clear();
    
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    
    
    cout << "RGameEngine Cleanup" << endl;
}

int RGameEngine::HandleEvents() 
{           
    if( !states.empty() )
    {
       return states.back()->HandleEvents(this);
    }
    return 0;
};

int RGameEngine::Update() 
{
    //update global time
    r_time::Update();
    
    if( !states.empty() )
    {
        return states.back()->Update(this);
    }
    return 0;
};

int RGameEngine::Draw() 
{
    if( !states.empty() )
    {
       return states.back()->Draw(this);
    }
    return 0;
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

