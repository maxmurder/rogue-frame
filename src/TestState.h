#include "r_gamestate.h"
#include "SDL/SDL.h"

class TestState: public RGameState {

    public:
    void Init();
    void Cleanup();
    
    void Pause();
    void Resume();
    
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
    
};

