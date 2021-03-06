#include "r_engine.h"
#include "r_gamestate.h"
#include "r_utils/r_logging.h"

int RGameEngine::Init(const char* title, int width, int height, int bpp, bool fullscreen)
{
    int imgFlag = IMG_INIT_PNG;
    //initialize SDL
    if (SDL_Init( SDL_INIT_EVERYTHING ) == -1)
    {
        R_LOG(r_logging::ERROR) << "SDL initilization failure" << " :: " << SDL_GetError();
        return 1;
    }
    if ( !(IMG_Init( imgFlag) & imgFlag ) )
    {
         R_LOG(r_logging::ERROR) << "SDL-IMG initilization failure" << " :: " << IMG_GetError();
        return 1;
    }

    if ( TTF_Init() == -1 )
    {
         R_LOG(r_logging::ERROR) << "SDL-IMG initilization failure" << " :: " << TTF_GetError();
        return 1;
    }

    if ( fullscreen ) {
        //todo: add fullscreen
    }

    _fullscreen = fullscreen;
    _running = true;
    R_LOG(r_logging::INFO) << "RGameEngine Init\n";
    return 0;
}

int RGameEngine::Start()
{
    static bool started = false;
    if(!started)
    {
        unsigned lag = 0;
        started = true;
        while (_running)
        {
            //update global time
            _time.Update();
            lag += _time.ElapsedTime();

            if (HandleEvents() != 0) return 1;
            while (lag >= UPDATE_MS)
            {
                if (Update() != 0) return 1;
                lag -= UPDATE_MS;
            }
            if (Draw() != 0) return 1;
        }
        Cleanup();
        return 0;
    }
    R_LOG(r_logging::WARNING) << "Somebody tried to start a running game.";
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

    R_LOG(r_logging::INFO) << "RGameEngine Cleanup";
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
