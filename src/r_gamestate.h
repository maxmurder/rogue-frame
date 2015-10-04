#ifndef R_GAMESTATE
#define R_GAMESTATE

#include "r_engine.h"

class RGameState //base class for game states
{
    public:
    virtual void Init() = 0;
    virtual void Cleanup() = 0;
    
    virtual void HandleEvents() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    
    void ChangeState(RGameEngine* game, RGameState* state)
    {
        game->ChangeState(state);
    }
    
    static RGameState& Instance();
    
    protected:
    RGameState(){};
};

#endif
