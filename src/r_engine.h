#ifndef R_ENGINE
#define R_ENGINE

#include <vector>
#include "r_curses.h"

class RGameState;

class RGameEngine
{
    public:
    void Init();
    void Cleanup();
    
    void HandleEvents();
    void Update();
    void Draw();
    
    bool Running() {return _running;}
    void Quit() {_running = false;}
    
    void ChangeState(RGameState*);
    void PushState(RGameState*);
    void PopState();
    
    private:
    std::vector<RGameState*> states; //game state stack
    
    r_curses::r_screen *screen; // game screen
    
    bool _running;
};

#endif
