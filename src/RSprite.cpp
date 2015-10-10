#include <iostream>
#include "RSprite.h"

void RSprite::SetTexture(RTexture* texture)
{
    _texture = texture;
}

void RSprite::AddAnimation(std::string animation, std::vector<SDL_Rect> frames)
{
    _animations.insert( std::pair<std::string, std::vector<SDL_Rect>>(animation, frames) );
}

void RSprite::RemoveAnimation(std::string animation)
{
    _animations.erase( animation );
}

void RSprite::ClearAnimations()
{
    _animations.clear();
}

void RSprite::PushFrames(std::string animation, std::vector<SDL_Rect> frames)
{
    for (auto &f : frames)
    {
        _animations[animation].push_back(f);
    }  
}

void RSprite::ClearFrames(std::string animation)
{
    _animations[animation].clear();
}

void RSprite::SetAnimationSpeed( int animationSpeed )
{
    _animSpeed = animationSpeed;
}

void RSprite::SetForeground(SDL_Color color)
{
    _fg = color;
}

void RSprite::SetBackground(SDL_Color color)
{
    _bg = color;
}

void RSprite::UpdateTexture()
{
    if (_texture != NULL) 
    {
        _texture->SetColor(_fg.r, _fg.g, _fg.b);
        _texture->SetAlpha(_fg.a);
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
    if(alpha != _bg.a)
    {
        _bg.a = alpha;
        if (_texture != NULL) 
        {
            _texture->SetAlpha( _bg.a );
        }
    }
}

void RSprite::SetBlendMode(SDL_BlendMode blending)
{
    if (_texture != NULL) 
    {
        _texture->SetBlendMode( blending );
    }
}

void RSprite::SetFlipMode(SDL_RendererFlip flip)
{
    _flip = flip;
}

void RSprite::SetAngle(double angle)
{
    _angle = angle;
}

void RSprite::SetCenter(SDL_Point center)
{
    _center = center;
}

void RSprite::SetAnimation(std::string animation, uint16_t frame)
{
    _currentAnimation = animation;
    _currentframe = frame;
}

void RSprite::SetFrame( uint16_t frame )
{
    _currentframe = frame;
}

void RSprite::NextFrame()
{
    if ( _currentframe < _animations[_currentAnimation].size()-1 )
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
        _currentframe = _animations[_currentAnimation].size()-1;
    }
}

void RSprite::UpdateAnimation() 
{

}

void RSprite::Render( SDL_Renderer*  renderer, int x, int y )
{
    if (_texture != NULL)
    {
        if (_animations.size() > 0)
        {
            if (_animations.count(_currentAnimation) == 0 )
            {
                _currentAnimation = _animations.begin()->first;
            }
            if (_currentframe >= _animations[_currentAnimation].size()-1)
            {
                _currentframe = _animations[_currentAnimation].size()-1;
            }
            
            SDL_Rect* curFrame = &_animations[_currentAnimation].at(_currentframe);
        
            //render background
            if (_bg.a > 0)
            {
                SDL_Rect bgRect = {x, y, curFrame->w, curFrame->h};
                SDL_SetRenderDrawColor(renderer, _bg.r, _bg.g, _bg.b, _bg.a);
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_RenderFillRect(renderer, &bgRect);
            }
            //update texture
            UpdateTexture();
            //render texture
            _texture->Render(renderer, x, y, curFrame, _angle, &_center, _flip);
        }else
        {
            std::cout << "Sprite could not be rendered :: Missing animation \n";
        }
    }else
    {
        std::cout << "Sprite could not be rendered :: Missing texture \n";
    }
}

RSprite::RSprite( RTexture* texture, std::vector<SDL_Rect> frames, int animationSpeed, SDL_Color fg, SDL_Color bg, std::string animation )
{
    _texture = texture;
    _animSpeed = animationSpeed;
    _fg = fg;
    _bg = bg;
    _center = {0,0};
    _angle = 0.0;
    AddAnimation(animation, frames );
    SetAnimation(animation);
    SetBlendMode( SDL_BLENDMODE_BLEND );
    SetFlipMode( SDL_FLIP_NONE );
    _currentframe = 0;
}
RSprite::~RSprite(){};



