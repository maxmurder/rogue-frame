#include "r_SDL.h"
#include "SDL/SDL_image.h"

SDL_Surface *r_SDL::LoadImage( std::string filename, SDL_PixelFormat* format )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimisedImage = NULL;
    
    loadedImage = IMG_Load( filename.c_str() );
    
    if( loadedImage != NULL)
    {
    optimisedImage = SDL_ConvertSurface( loadedImage, format, 0);
    SDL_FreeSurface( loadedImage );
    }
    return optimisedImage;
}

void r_SDL::ApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    
    SDL_BlitSurface( source, NULL, destination, &offset );
} 

