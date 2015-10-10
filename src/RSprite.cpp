#include <iostream>
#include "RSprite.h"

void RSprite::Init( RTexture* texture, std::vector<SDL_Rect> frames, int animationSpeed, SDL_Color fg, SDL_Color bg, std::string animation )
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
    static int i = 0;
    if(_animSpeed != 0)
    {
        if ( i > abs(_animSpeed))
        {   
            if(_animSpeed > 0)
            {
                NextFrame();
            }else
            {
                PreviousFrame();
            }
            i = 0;
        }
        i++;
    }
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
                RenderBackground(renderer, {x, y, curFrame->w, curFrame->h});
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

void RSprite::RenderBackground(SDL_Renderer* renderer, SDL_Rect frame)
{
    SDL_SetRenderDrawColor(renderer, _bg.r, _bg.g, _bg.b, _bg.a);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(renderer, &frame);
}

RSprite::RSprite()
{
    _texture = NULL;
    _animSpeed = 0;
    _fg = {0,0,0,0};
    _bg = {0,0,0,0};
    _center = {0,0};
    _angle = 0.0;
    _currentframe = 0;
}
RSprite::~RSprite(){}

/*-----------------------------------------RUnicodeSprite--------------------------------------------------*/

void RUnicodeSprite::Init( SDL_Renderer* renderer, TTF_Font* font, int pntsize, std::vector<uint16_t> symbols, SDL_Color fg, SDL_Color bg, std::string animation, int animationSpeed)
{
    //init variables
    _fg = fg;
    _bg = bg;
    _animSpeed = animationSpeed;
    _center = {pntsize/4,pntsize/2};
    _angle = 0.0;
    _currentframe = 0;
    _pntsize = pntsize;
    
    //check if _texture exists
    if (_texture == NULL)
    {
        _texture = new RTexture();
        _internalTexutreInstance = true;
    }else
    {
        _texture->FreeTexture();
        _internalTexutreInstance = false;
    }
    //generate sprite sheet
    CreateUnicodeSpriteSheet(renderer, font, symbols);

    //initilize sprite
    RSprite::AddAnimation(animation, {{0,0,pntsize/2,pntsize}});
    SetAnimation(animation);
    SetBlendMode( SDL_BLENDMODE_BLEND );
    SetFlipMode( SDL_FLIP_NONE );
}

void RUnicodeSprite::Init( RTexture* texture, TTF_Font* font, int pntsize, std::vector<uint16_t> symbols, SDL_Color fg, SDL_Color bg, std::string animation, int animationSpeed)
{
    //init variables
    _texture = texture;
    _fg = fg;
    _bg = bg;
    _animSpeed = animationSpeed;
    _center = {pntsize/4,pntsize/2};
    _angle = 0.0;
    _currentframe = 0;
    _pntsize = pntsize;
    for(auto &sym : symbols)
    {
        _symbols.push_back(sym);
    }
    
    //check if _texture exists
    if (_texture != NULL)
    {
        _internalTexutreInstance = false;
        
        //initilize sprite
        AddAnimation(animation, _symbols);
        SetAnimation(animation);
        SetBlendMode( SDL_BLENDMODE_BLEND );
        SetFlipMode( SDL_FLIP_NONE );
    }else
    {
        std::cout << "Sprite could not be initilized :: Missing texture \n";
    }
}

void RUnicodeSprite::AddAnimation( std::string animation, std::vector<uint16_t> frames)
{
    std::vector<SDL_Rect> animationFrames;
    for( auto &s : frames)
    {
        uint16_t frame = 0;
        frame = GetSymbolIndex(s);
        animationFrames.push_back({frame*(_pntsize/2),0,_pntsize/2,_pntsize});
    }
    RSprite::AddAnimation(animation, animationFrames);
}

void RUnicodeSprite::RenderSymbol( SDL_Renderer* renderer, int x, int y, uint16_t symbol)
{
    if(_texture != NULL )
    {   
        bool success = false;
        SDL_Rect symFrame = {0,0,_pntsize/2,_pntsize};
        for( uint16_t s = 0; s < _symbols.size(); s++ )
        {
            if( _symbols[s] == symbol)
            {
                symFrame = {s*(_pntsize/2),0,_pntsize/2,_pntsize};
                success = true;
            }   
        }
        if (!success)
        {
            std::cout << "RSprite :: Symbol not found in list \n";
        }
        //render background
        if (_bg.a > 0)
        {
            RenderBackground(renderer, {x, y, symFrame.w, symFrame.h});
        }
        //update texture
        UpdateTexture();
        //render texture
        _texture->Render(renderer, x, y, &symFrame, _angle, &_center, _flip);
    }else
    {
        std::cout << "Sprite could not be rendered :: Missing texture \n";
    }
}

int RUnicodeSprite::GetPntSize()
{
    return _pntsize;
}

void RUnicodeSprite::CreateUnicodeSpriteSheet(SDL_Renderer* renderer, TTF_Font* font, std::vector<uint16_t> symbols)
{
    if (_texture != NULL)
    {
        uint16_t *symArray =  &symbols[0];
        //fill the symbols vector
        for(auto &sym : symbols)
        {
            _symbols.push_back(sym);
        }
        _texture->RenderUnicode(renderer, symArray, font);
    } else
    {
        std::cout << "Unicode spritesheet could not be rendered :: Missing texture \n";
    }
}

uint16_t RUnicodeSprite::GetSymbolIndex(uint16_t symbol)
{
    for (uint16_t i = 0; i < _symbols.size(); i++)
    {
        if (_symbols[i] == symbol)
        {
            return i;
        }
    }
    std::cout << "RSprite :: Symbol not found in list.\n";
    return 0;
}

RUnicodeSprite::RUnicodeSprite() : RSprite()
{
    _pntsize = 0;
}

RUnicodeSprite::~RUnicodeSprite()
{
    if(_internalTexutreInstance)
    {
        _texture->FreeTexture();
        delete _texture;
    }
}



