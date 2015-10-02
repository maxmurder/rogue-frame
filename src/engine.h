#include <vector>

namespace engine 
{
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
        
        void ChangeState(RGameState* state);
        void PushState(RGameState* state);
        void PopState();
        
        private:
        vector<RGameState*> states;
        
        bool _running;
    };
    
    class RGameState
    {
        public:
        virtual void Init() = 0;
        virtual void Cleanup() = 0;
        
        virtual void HandleEvents() = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;
        
        void ChangeState(RGameEngine* game, RGameState* state){
            game->ChangeState(state);
        }
        
        static RGameState& getInstance()
        {
            static RGameState instance;
            return instance;
        }
        
        private:
        RGameState(){};
    };
}
