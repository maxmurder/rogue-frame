#ifndef R_ENGINE
#define R_ENGINE

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class RGameState;

class RGameEngine
{
    public:
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
    
    private:
    std::vector<RGameState*> states; //game state stack
    bool _fullscreen;
    bool _running; 
    SDL_Event _event;
};

#endif
