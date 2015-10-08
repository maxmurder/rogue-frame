#include "RSprite.h"

RSprite::(RTexture* texture, std::vector<SDL_Rect> frames = NULL, uint animationSpeed = 0, uint8 red = 0, uint8 green = 0, uint blue = 0, uint8 alpha = 0xFF, SDL_BlendMode blending = SDL_BLENDMODE_NONE )
{
    _texture = texture;
    _frames = frames;
    _animSpeed = animationSpeed;
    
    if ( red != 0 || green !=0 || blue != 0 ) 
    {
        SetColorMod(red, green, blue);
    }
    
    _currentframe = 0;
}

