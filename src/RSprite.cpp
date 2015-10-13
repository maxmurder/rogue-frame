#include <iostream>
#include <iomanip>
#include "RSprite.h"

using namespace std;

void RSprite::Init( RTexture* texture, vector<SDL_Rect> frames, int animationSpeed, SDL_Color fg, SDL_Color bg, string animation )
{
    _texture = texture;
    _animSpeed = animationSpeed;
    _fg = fg;
    _bg = bg;
    _center = {0,0};
    _angle = 0.0;
    _w = frames[0].w;
    _h = frames[0].h;
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

void RSprite::AddAnimation(string animation, vector<SDL_Rect> frames)
{
    _animations.insert( pair<string, vector<SDL_Rect>>(animation, frames) );
}

void RSprite::RemoveAnimation(string animation)
{
    _animations.erase( animation );
}

void RSprite::ClearAnimations()
{
    _animations.clear();
}

void RSprite::PushFrames(string animation, vector<SDL_Rect> frames)
{
    for (auto &f : frames)
    {
        _animations[animation].push_back(f);
    }  
}

void RSprite::ClearFrames(string animation)
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

void RSprite::SetDimensions(int width, int height )
{
    _w = width;
    _h = height;
}

void RSprite::SetRenderOffset( int xOffset, int yOffset)
{
    _xRenderOffset = xOffset;
    _yRenderOffset = yOffset;
}

int RSprite::GetWidth()
{
    return _w;
}

int RSprite::GetHeight()
{
    return _h;
}


void RSprite::SetAnimation(string animation, uint16_t frame)
{
    _currentAnimation = animation;
    _currentframe = frame;
    ResetAnimCounter();
}

void RSprite::SetFrame( uint16_t frame )
{
    _currentframe = frame;
    ResetAnimCounter();
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

void RSprite::Pause()
{
    _paused = true;
}

void RSprite::Play()
{
    _paused = false;
}

void RSprite::UpdateAnimation() 
{
    if(_animSpeed != 0 || _paused)
    {
        if ( _animCount > abs(_animSpeed))
        {   
            if(_animSpeed > 0)
            {
                NextFrame();
            }else
            {
                PreviousFrame();
            }
            ResetAnimCounter();
        }
        _animCount++;
    }
}

void RSprite::Render( SDL_Renderer*  renderer, int x, int y )
{
    if (_texture != NULL)
    {
        if (_animations.size() > 0)
        {
            //verify there is an animation to play
            if (_animations.count(_currentAnimation) == 0 )
            {
                _currentAnimation = _animations.begin()->first;
            }
            //verify current frame is not out of range
            if (_currentframe >= _animations[_currentAnimation].size()-1)
            {
                _currentframe = _animations[_currentAnimation].size()-1;
            }
            
            //select frame to render
            SDL_Rect* curFrame = &_animations[_currentAnimation].at(_currentframe);
        
            //render background
            if (_bg.a > 0)
            {
                RenderBackground(renderer, { x , y, _w, _h});
            }
            //update texture
            UpdateTexture();
            //render texture
            _texture->Render(renderer, x + _xRenderOffset, y + _yRenderOffset, curFrame, _angle, &_center, _flip);
        }else
        {
            cout << "Sprite could not be rendered :: Missing animation" << endl;
        }
    }else
    {
        cout << "Sprite could not be rendered :: Missing texture" << endl;
    }
}

void RSprite::RenderBackground(SDL_Renderer* renderer, SDL_Rect frame)
{
    SDL_SetRenderDrawColor(renderer, _bg.r, _bg.g, _bg.b, _bg.a);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(renderer, &frame);
}

void RSprite::ResetAnimCounter()
{
    _animCount = 0;
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
    _animCount = 0;
    _paused = false;
    _w = 0;
    _h = 0;
    _xRenderOffset = 0;
    _yRenderOffset = 0;
}
RSprite::~RSprite(){}

/*-----------------------------------------RUnicodeSprite--------------------------------------------------*/

void RUnicodeSprite::Init( SDL_Renderer* renderer, TTF_Font* font, int pntsize, vector<uint16_t> symbols, int mode, SDL_Color fg, SDL_Color bg, string animation, int animationSpeed)
{
    //init variables
    _fg = fg;
    _bg = bg;
    _animSpeed = animationSpeed;
    _angle = 0.0;
    _currentframe = 0;
    SetTextMode(mode, pntsize);
    
    //fill the sembols table
    for(auto &sym : symbols)
    {
        _symbols.push_back(sym);
    }
    
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
    RSprite::AddAnimation(animation, {{0,0,_w,_h}});
    SetAnimation(animation);
    SetBlendMode( SDL_BLENDMODE_BLEND );
    SetFlipMode( SDL_FLIP_NONE );
}

void RUnicodeSprite::Init( RTexture* texture, TTF_Font* font, int pntsize, vector<uint16_t> symbols, int mode, SDL_Color fg, SDL_Color bg, string animation, int animationSpeed)
{
    //init variables
    _texture = texture;
    _fg = fg;
    _bg = bg;
    _animSpeed = animationSpeed;
    _angle = 0.0;
    _currentframe = 0;
    SetTextMode(mode, pntsize);

    //fill the sembols table
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
        cout << "Sprite could not be initilized :: Missing texture" << endl;
    }
}

void RUnicodeSprite::AddAnimation( string animation, vector<uint16_t> frames)
{
    vector<SDL_Rect> animationFrames;
    for( auto &s : frames)
    {
        uint16_t frame = 0;
        frame = GetSymbolIndex(s);
        animationFrames.push_back( { frame * _charw, 0 , _charw, _charh } );
    }
    RSprite::AddAnimation(animation, animationFrames);
}

void RUnicodeSprite::RenderSymbol( SDL_Renderer* renderer, int x, int y, uint16_t symbol)
{
    if(_texture != NULL )
    {   
        SDL_Rect symFrame = {0,0, _charw , _charh};
        symFrame = { GetSymbolIndex(symbol) * _charw , 0 , _charw , _charh };
        
        //render background
        if (_bg.a > 0)
        {
            RenderBackground(renderer, {x, y, _w, _h});
        }
        //update texture
        UpdateTexture();
        //render texture
        _texture->Render(renderer, x + _xRenderOffset, y + _yRenderOffset, &symFrame, _angle, &_center, _flip);
    }else
    {
        cout << "Sprite could not be rendered :: Missing texture" << endl;
    }
}

void RUnicodeSprite::RenderSymbol( SDL_Renderer* renderer, int x, int y, string symbols, int width)
{
    vector<uint16_t> vec;
    for (auto &s : symbols)
    {
        vec.push_back(s);
    }
    RenderSymbol(renderer, x, y, vec, width);
}

void RUnicodeSprite::RenderSymbol( SDL_Renderer* renderer, int x, int y, vector<uint16_t> symbols, int width)
{
    if(_texture != NULL )
    { 
        int i = 0, r = 0;
        for (auto &c : symbols)
        {
            int xOffset = 0;
            int yOffset = 0;
            SDL_Rect frame = {0,0,_charw,_charh};   
            
            //handle carrige return and line feed characters
            if ( (c == 0x000A) || (c == 0x000D) )
            {
                r++;
                i = 0;
            } else {
                CalculateOffset( &xOffset, &yOffset, &r, width, i);
                
                //choose frame
                frame = { GetSymbolIndex(c) * _charw , 0 , _charw , _charh };
                
                //render background
                if (_bg.a > 0)
                {
                    RenderBackground(renderer , { x + xOffset , y + yOffset, _w, _h});
                }
                
                //update texture and render
                UpdateTexture();
                _texture->Render(renderer, x + xOffset + _xRenderOffset, y + yOffset + _yRenderOffset, &frame, _angle, &_center, _flip);
                i++;
            }
        }
    }else
    {
        cout << "Sprite could not be rendered :: Missing texture" << endl;
    }
}

int RUnicodeSprite::GetPntSize()
{
    return _pntsize;
}

void RUnicodeSprite::SetTextMode(int mode, int pntsize)
{   
    _pntsize = pntsize;
    switch (mode)
    {
    case TEXT:
        _charw = pntsize / 2;
        _charh = pntsize;
        SetDimensions(_charw, _charh);
        SetRenderOffset( 0 , 0);
        break;
    case UNICODE:
        _charw = pntsize / 2;
        _charh = pntsize;
        SetDimensions(pntsize, pntsize);
        SetRenderOffset( _charw / 2, 0);
        break;
    case UTF8:
        _charw = pntsize / 2;
        _charh = pntsize;
        SetDimensions(pntsize, pntsize);
        SetRenderOffset( _charw / 2, 0);
    break;
    default:
        cout << "Unkown TextMode: " << mode;
    }
}

void RUnicodeSprite::CreateUnicodeSpriteSheet(SDL_Renderer* renderer, TTF_Font* font, vector<uint16_t> symbols)
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
        cout << "Unicode spritesheet could not be rendered :: Missing texture" << endl;
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
    cout << "RUnicodeSprite :: Symbol: '0x" << std::uppercase << std::setfill('0') << std::setw(4) << symbol << "' not found in list." << endl;
    return 0;
}

void RUnicodeSprite::CalculateOffset(int *xOffset, int *yOffset, int *r, int width, int c)
{
 //calculate offsets
    *xOffset = (c * _w);
    int i = *r;
    
    if (width >= _w)
    {
        if ( *xOffset % width == 0 && c > 0)
        {
            i++;
        }
        *xOffset = *xOffset % width;
    }
    *yOffset = ( i * _h);
    *r = i;
}

RUnicodeSprite::RUnicodeSprite() : RSprite()
{
    _pntsize = 0;
    _charh = 0;
    _charw = 0;
}

RUnicodeSprite::~RUnicodeSprite()
{
    if(_internalTexutreInstance)
    {
        _texture->FreeTexture();
        delete _texture;
    }
}



