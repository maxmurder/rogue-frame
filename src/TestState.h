#include "r_gamestate.h"
#include "SDL/SDL.h"

class TestState: public RGameState {

    public:
    void Init(RGameEngine* game);
    void Cleanup(RGameEngine* game);
    
    void Pause(RGameEngine* game);
    void Resume(RGameEngine* game);
    
    void HandleEvents(RGameEngine* game);
    void Update(RGameEngine* game);
    void Draw(RGameEngine* game);
    
    static TestState* Instance()
    {
        return &m_TestState;
    }
    
    protected:
    TestState() { }
    
    private:
    static TestState m_TestState;
    SDL_Surface* _bg;
    SDL_Event _event;
    
};

