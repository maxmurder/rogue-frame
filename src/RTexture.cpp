#include <iostream>
#include "RTexture.h"
#include "r_SDL.h"

using namespace std;

RTexture::RTexture()
{
    _texture = NULL;
    _width = 0;
    _height = 0;
}

RTexture::~RTexture()
{
    FreeTexture();
}

bool RTexture::LoadFromFile( std::string path, SDL_Renderer* renderer )
{
    FreeTexture();
    
    SDL_Texture* newTexture = NULL;
    newTexture = r_SDL::LoadTexture( path, renderer );
    if ( newTexture == NULL )
    {
        cout << "RTexture could not load " << SDL_GetError() << "\n";
    } else
    {
       SDL_QueryTexture( newTexture, NULL, NULL, &_width, &_height ); 
    }
    _texture = newTexture;
    return _texture != NULL;
}

bool RTexture::LoadFromFile( std::string path, SDL_Renderer* renderer, int red, int green, int blue )
{
    FreeTexture();
    
    SDL_Texture* newTexture = NULL;
    newTexture = r_SDL::LoadTexture( path, renderer, red, green, blue );
    if ( newTexture == NULL )
    {
        cout << "RTexture could not load :: " << SDL_GetError() << "\n";
    } else
    {
       SDL_QueryTexture( newTexture, NULL, NULL, &_width, &_height ); 
    }
    _texture = newTexture;
    return _texture != NULL;
}

void RTexture::FreeTexture()
{
    if (_texture != NULL) 
    {
        SDL_DestroyTexture (_texture);
        _texture = NULL;
        _width = 0;
        _height = 0;
    }
}

void RTexture::Render( SDL_Renderer* renderer, int x, int y )
{
    SDL_Rect quad = {x, y, _width, _height};
    SDL_RenderCopy( renderer, _texture, NULL, &quad );
}

int RTexture::GetWidth()
{
    return _width;
}

int RTexture::GetHeight()
{
    return _height;
}
