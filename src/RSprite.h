#ifndef RSPRITE_H
#define RSPRITE_H

#include <vector>
#include <SDL2/SDL.h>
#include "RTexture.h"

class RSprite
{
    public:
        //sprite creation and metadata setting
        void SetTexture(RTexture* texture);
        void PushFrames(std::vector<SDL_Rect> frames);
        void ClearFrames();
        
        void SetAnimationSpeed(uint animationSpeed);
        void SetColorMod(uint8 red, uint8 green, uint8 blue);
        void SetAlpha(uint8 alpha);
        void SetBlendMode();
        
        //animation interface
        void SetFrame(uint frame);
        void NextFrame();
        void PreviousFrame();
        void UpdateAnimation();
        void Render(SDL_Renderer, int x, int y);
        
        RSprite(RTexture* texture, std::vector<SDL_Rect> frames = NULL, uint animationSpeed = 0, uint8 red = 0, uint8 green = 0, uint blue = 0, uint8 alpha = 0xFF, SDL_BlendMode blending = SDL_BLENDMODE_BLENDING );
        ~RSprite();
    
    private:
        RTexture* _texture;
        std::vector<SDL_Rect> _frames;
        uint _currentframe;
        uint _animSpeed;
        uint[4] _rgba;
        
}
#endif
