#ifndef R_ENGINE
#define R_ENGINE

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "r_time.h"

class RGameState; // RGameState forward declaration

/*
* Core game engine class. 
* Runs the main loop and calls the appropriate RGameState functions.
*/

class RGameEngine
{
    public:
    unsigned UPDATE_MS = 17; //ms per each fixed update step.
    
    int Init(const char* title, int width=640, int height=480, int bbp=0, bool fullscreen=false); //initilizes the game, starts SDL etc.
    int Start(); //starts the main gameloop. engine must be initilized first. also good to set a state before starting.
    void Cleanup(); //cleans up and closes the game
    
    int HandleEvents(); // calls the current RGameState HandleEvents() method every tick.
    int Update(); // calls the current RGameState Update() method every tick.
    int Draw(); // calls the curren RGameState Draw function method every frame.
    
    bool Running() {return _running;} // Returns the current running state.
    void Quit() {_running = false;} // Tells the engine to shut down at the next oppertunity.
    
    void ChangeState(RGameState*); // Changes to a new RGameState.
    void PushState(RGameState*); // Adds a RGamestate to the state list.
    void PopState(); //Pops a RGameState from the states list.
    
    unsigned GlobalTime(){return _time.CurrentTime();} //returns the current engine time.
    unsigned GlobalMS() {return _time.ElapsedTime();} //returns the current time since start.
    double GlobalDelta() {return _time.Delta();} //returns the current dynamic frame delta.
    double FixedUpdateDelta() { return UPDATE_MS * 0.001; } //returns the fixed update delta time.
    
    private:
    std::vector<RGameState*> states; //game state stack
    r_time::RTime _time;
    bool _fullscreen;
    bool _running;
    SDL_Event _event;
};

#endif
