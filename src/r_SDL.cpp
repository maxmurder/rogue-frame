#include <iostream>
#include "r_SDL.h"
#include "SDL2/SDL_image.h"

using namespace std;

SDL_Surface* r_SDL::LoadImage( std::string path, SDL_PixelFormat* format )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimisedImage = NULL;
    
    loadedImage = IMG_Load( path.c_str() );
    
    if( loadedImage == NULL)
    {
        cout << "Unable to load image: " << path << " :: " << SDL_GetError() << "\n";
    } else 
    {
        optimisedImage = SDL_ConvertSurface( loadedImage, format, 0);
        if( optimisedImage == NULL)
        {
            cout << "Unable to convert surface: " << path << " :: " << SDL_GetError() << "\n";
        }
        SDL_FreeSurface( loadedImage );
    }
    return optimisedImage;
}

SDL_Texture* r_SDL::LoadTexture( std::string path, SDL_Renderer* renderer )
{
    SDL_Texture* loadedTexture = NULL;
    SDL_Surface* loadedSurface = NULL;
    
    loadedSurface = IMG_Load( path.c_str() );
    if (loadedSurface == NULL )
    {
        cout << "Unable to load image: " << path << " :: " << SDL_GetError() << "\n";
    }else
    {
        loadedTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if ( loadedTexture == NULL )
        {
            cout << "Unable to load texture: " << path << " :: " << SDL_GetError() << "\n";
        }
        
        SDL_FreeSurface( loadedSurface );
    }
    
    return loadedTexture;
}

void r_SDL::ApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    
    SDL_BlitSurface( source, NULL, destination, &offset );
} 

