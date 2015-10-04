#ifndef R_ENGINE
#define R_ENGINE

#include <vector>
#include "SDL/SDL.h"

class RGameState;

class RGameEngine
{
    public:
    void Init(const char* title, int width=640, int height=480, int bbp=0, bool fullscreen=false);
    void Cleanup();
    
    void HandleEvents();
    void Update();
    void Draw();
    
    bool Running() {return m_running;}
    void Quit() {m_running = false;}
    
    void ChangeState(RGameState*);
    void PushState(RGameState*);
    void PopState();
    
    private:
    std::vector<RGameState*> states; //game state stack

    SDL_Surface* screen;
    
    bool m_fullscreen;
    bool m_running;
};

#endif
