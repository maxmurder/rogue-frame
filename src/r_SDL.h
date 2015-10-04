#ifndef R_SDL
#define R_SDL

#include <string>
#include <SDL2/SDL.h>


class r_SDL
{
    public:
    static SDL_Surface *LoadImage( std::string filename , SDL_PixelFormat* format);
    static void ApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
};  


#endif
