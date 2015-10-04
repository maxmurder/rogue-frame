#ifndef R_GAMESTATE
#define R_GAMESTATE

#include "r_engine.h"

class RGameState //base class for game states
{
    public:
    virtual void Init(RGameEngine* game) = 0;
    virtual void Cleanup(RGameEngine* game) = 0;
    
    virtual void Pause(RGameEngine* game) = 0;
    virtual void Resume(RGameEngine* game) = 0;
    
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
