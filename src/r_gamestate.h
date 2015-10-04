#ifndef R_GAMESTATE
#define R_GAMESTATE

#include "r_engine.h"

class RGameState //base class for game states
{
    public:
    virtual void Init() = 0;
    virtual void Cleanup() = 0;
    
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    
    virtual void HandleEvents(RGameEngine* game) = 0;
    virtual void Update(RGameEngine* game) = 0;
    virtual void Draw(RGameEngine* game) = 0;
    
    void ChangeState(RGameEngine* game, RGameState* state)
    {
        game->ChangeState(state);
    }
    
    protected:
    RGameState(){};
};

#endif
