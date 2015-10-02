#include <signal.h>
#include "r_engine.h"

using namespace std;
using namespace r_engine;

void RGameEngine::Init() 
{
    screen = new r_curses::r_screen();
    signal(SIGWINCH,screen->resizeHandler);
}

void RGameEngine::Cleanup() 
{
    delete screen;
}

void RGameEngine::HandleEvents() {};

void RGameEngine::Update() {};

void RGameEngine::Draw() {};

void RGameEngine::ChangeState(RGameState* state)
{
    //state->Init();
}

void RGameEngine::PushState(RGameState* state)
{
    states.push_back(state);
}

void RGameEngine::PopState()
{
    states.pop_back();
}

void RGameState::ChangeState(RGameEngine* game, RGameState* state)
{
   game->ChangeState(state);
}

RGameState* RGameState::Instance()
{
    static RGameState *instance;
    return instance;
}
