#ifndef R_GAMESTATE
#define R_GAMESTATE

#include "r_engine.h"

/*
* Abstract RGameState class to act as an interface for RGameStates._baseFramework
* Game logic should be constructed in a child of this class and added to the RGameEngine
* RGameState stack. 
* Methods will only be called when the state is RGameEngine's current active state.
*/

class RGameState
{
    public:
    virtual void Init(RGameEngine* game) = 0; // Called when the state becomes RGameEngine's active state.
    virtual void Cleanup(RGameEngine* game) = 0; // Called when the state stops being RGameEngine's active state and on Quit.
    
    virtual void Pause(RGameEngine* game) = 0; // Called when RGameEngine is paused.
    virtual void Resume(RGameEngine* game) = 0; //Called when RGamestate is unpaused.
    
    virtual int HandleEvents(RGameEngine* game) = 0; // Called every tick during RGameEngine HandleEvents step.
    virtual int Update(RGameEngine* game) = 0; // Called every tick during RGameEngine Update step.
    virtual int Draw(RGameEngine* game) = 0; // Called every frame during RGameEngine Draw step.
    
    // Tells the engine to change states.
    void ChangeState(RGameEngine* game, RGameState* state)
    {
        game->ChangeState(state);
    }
    
    protected:
    RGameState(){};
};

#endif
