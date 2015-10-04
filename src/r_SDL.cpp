#include "r_SDL.h"

SDL_Surface *r_SDL::LoadImage( std::string filename )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimisedImage = NULL;
    
    loadedImage = SDL_LoadBMP( filename.c_str() );
    
    if( loadedImage != NULL )
    {
    optimisedImage = SDL_DisplayFormat( loadedImage );
    SDL_FreeSurface( loadedImage );
    }
    return optimisedImage;
}   

