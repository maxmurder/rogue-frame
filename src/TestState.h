#ifndef TESTSTATE_H
#define TESTSTATE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "r_SDL.h"
#include "RSprite.h"
#include "RTexture.h"
#include "r_gamestate.h"

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
            return &_TestState;
        }
    
    protected:
        TestState() { }
    
    private:
        static TestState _TestState;
        SDL_Renderer* _renderer;
        RTexture* _texture;
        SDL_Event _event;
        
        RTexture* _spriteTex;
        RSprite* _sprite;
        
        TTF_Font* _font;
        RTexture* _textTex;
        
};

#endif
