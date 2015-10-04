#include "r_gamestate.h"

class TestState: public RGameState {

    public:
    void Init();
    void Cleanup();
    
    void HandleEvents();
    void Update();
    void Draw();
    
    static TestState* Instance()
    {
        return &m_TestState;
    }
    
    protected:
    TestState() { }
    
    private:
    static TestState m_TestState;
};

