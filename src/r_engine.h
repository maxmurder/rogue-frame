#ifndef R_ENGINE
#define R_ENGINE

#include <vector>
#include "r_curses.h"

namespace r_engine 
{
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
    
    class RGameState //base class for game states
    {
        public:
        virtual void Init() = 0;
        virtual void Cleanup() = 0;
        
        virtual void HandleEvents() = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;
        
        void ChangeState(RGameEngine* game, RGameState* state);
        
        static RGameState* Instance();
        
        private:
        RGameState();
    };
}

#endif
