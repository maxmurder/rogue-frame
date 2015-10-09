#ifndef RSPRITE_H
#define RSPRITE_H

#include <vector>
#include <SDL2/SDL.h>
#include "r_SDL.h"
#include "RTexture.h"

class RSprite
{
    public:
        void SetTexture(RTexture* texture);
        void PushFrames(std::vector<SDL_Rect> frames);
        void ClearFrames();
        
        void SetAnimationSpeed(int animationSpeed);
        void SetRGBA( RGBA rgba );
        void SetColor(uint8_t red, uint8_t green, uint8_t blue);
        void SetAlpha(uint8_t alpha);
        void SetBackground(RGBA rgba);
        void SetBlendMode(SDL_BlendMode blending);
        
        //animation interface
        void SetFrame(int frame);
        void NextFrame();
        void PreviousFrame();
        void UpdateAnimation();
        void Render(SDL_Renderer* renderer, int x, int y);
        
        RSprite(RTexture* texture, std::vector<SDL_Rect> frames, int animationSpeed = 0, RGBA rgba = {0,0,0,0});
        ~RSprite();
    
    private:
        RTexture* _texture;
        std::vector<SDL_Rect> _frames;
        uint8_t _currentframe;
        int _animSpeed;
        RGBA _fg;
        RGBA _bg;
};
#endif
