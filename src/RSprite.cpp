#include "RSprite.h"

void RSprite::SetTexture(RTexture* texture)
{
    _texture = texture;
}

void RSprite::PushFrames(std::vector<SDL_Rect> frames)
{
    for (auto &f : frames)
    {
        _frames.push_back(f);
    }  
}

void RSprite::ClearFrames()
{
    _frames.clear();
    _currentframe = 0;
    _animSpeed = 0;
}

void RSprite::SetAnimationSpeed( int animationSpeed )
{
    _animSpeed = animationSpeed;
}

void RSprite::SetRGBA( RGBA rgba )
{
    _fg = rgba;
    if (_texture != NULL) 
    { 
        _texture->SetColor(_fg.r, _fg.g, _fg.b);
        _texture->SetAlpha(_fg.a);
    }
}

void RSprite::SetColor(uint8_t red, uint8_t green, uint8_t blue)
{
    if(red != _fg.r || green != _fg.g || blue != _fg.b)
    {
        _fg.r = red;
        _fg.g = green;
        _fg.b = blue;
        if (_texture != NULL) 
        {
        _texture->SetColor(_fg.r, _fg.g, _fg.b);
        }
    }
}

void RSprite::SetAlpha(uint8_t alpha)
{
    if (alpha != _fg.a)
    {
        _fg.a = alpha;
        if (_texture != NULL) 
        {
            _texture->SetAlpha( _fg.a );
        }
    }
}

void RSprite::SetBackground(RGBA rgba)
{
    _bg = rgba;
}

void RSprite::SetBlendMode(SDL_BlendMode blending)
{
    if (_texture != NULL) 
    {
        _texture->SetBlendMode( blending );
    }
}

void RSprite::SetFrame( int frame )
{
    _currentframe = frame;
}

void RSprite::NextFrame()
{
    if ( _currentframe < _frames.size()-1 )
    {
        _currentframe++;    
    }else
    {
        _currentframe = 0;
    }
}

void RSprite::PreviousFrame()
{
    if ( _currentframe > 0)
    {
        _currentframe--;
    }else
    {
        _currentframe = _frames.size()-1;
    }
}

void RSprite::UpdateAnimation() 
{

}

void RSprite::Render( SDL_Renderer*  renderer, int x, int y )
{
    if (_texture != NULL)
    {
        if (_currentframe >= _frames.size()-1)
        {
            _currentframe = _frames.size()-1;
        }
        
        SDL_Rect* curFrame = &_frames.at(_currentframe);
        
        //render background
        if (_bg.a > 0)
        {
            SDL_Rect bgRect = {x, y, curFrame->w, curFrame->h};
            SDL_SetRenderDrawColor(renderer, _bg.r, _bg.g, _bg.b, _bg.a);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_RenderFillRect(renderer, &bgRect);
        }
        //render texture
        _texture->Render(renderer, x, y, curFrame);
    }
}

RSprite::RSprite( RTexture* texture, std::vector<SDL_Rect> frames, int animationSpeed, RGBA rgba )
{
    _texture = texture;
    _frames = frames;
    _animSpeed = animationSpeed;
    _fg = rgba;
    _bg = {0,0,0,0};
    SetBlendMode( SDL_BLENDMODE_BLEND );
    _currentframe = 0;
}
RSprite::~RSprite(){};



