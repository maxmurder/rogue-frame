#ifndef R_ENGINE
#define R_ENGINE

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "r_time.h"

class RGameState;

class RGameEngine
{
    public:
    unsigned UPDATE_MS = 17; //ms per each fixed update step.
    
    int Init(const char* title, int width=640, int height=480, int bbp=0, bool fullscreen=false); //initilizes the game, starts SDL etc.
    int Start(); //starts the main gameloop. engine must be initilized first. also good to set a state before starting.
    void Cleanup(); //cleans up and closes the game
    
    int HandleEvents();
    int Update();
    int Draw();
    
    bool Running() {return _running;}
    void Quit() {_running = false;}
    
    void ChangeState(RGameState*);
    void PushState(RGameState*);
    void PopState();
    
    unsigned GlobalTime(){return _time.CurrentTime();}
    unsigned GlobalMS() {return _time.ElapsedTime();}
    double GlobalDelta() {return _time.Delta();}
    double FixedUpdateDelta() { return UPDATE_MS * 0.001; }
    
    private:
    std::vector<RGameState*> states; //game state stack
    RTime _time;
    bool _fullscreen;
    bool _running;
    SDL_Event _event;
};

#endif
