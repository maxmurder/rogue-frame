#ifndef R_ENGINE
#define R_ENGINE

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "RWindow.h"

class RGameState;

class RGameEngine
{
    public:
    bool Init(const char* title, int width=640, int height=480, int bbp=0, bool fullscreen=false);
    void Cleanup();
    
    void HandleEvents();
    void Update();
    void Draw();
    
    bool Running() {return _running;}
    void Quit() {_running = false;}
    
    void ChangeState(RGameState*);
    void PushState(RGameState*);
    void PopState();
    
    RWindow* window;
    SDL_Renderer* renderer;
    
    private:
    std::vector<RGameState*> states; //game state stack
    bool _fullscreen;
    bool _running;
};

#endif
