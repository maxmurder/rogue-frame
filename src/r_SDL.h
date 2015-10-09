#ifndef R_SDL_H
#define R_SDL_H

#include <string>
#include <SDL2/SDL.h>


class r_SDL
{
    public:
        static SDL_Surface* LoadSurface( std::string path ); //load surface from fike 
        static SDL_Surface* LoadSurface( std::string path, int red, int green, int blue ); //load surface with color keying
        static SDL_Surface* LoadSurface( std::string path , SDL_PixelFormat* format); //load optomised surface from file
        static SDL_Texture* LoadTexture( std::string path, SDL_Renderer* renderer ); //Load optomised texure from file
        static SDL_Texture* LoadTexture( std::string path, SDL_Renderer* renderer, int red, int green, int blue ); //Load optomised texure from file with color keying
        static void ApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination ); // apply sdl surface
};

struct RGBA
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    friend bool operator==(const RGBA& lhs, const RGBA& rhs) 
    {
        if (lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a)
        {
            return true;
        }
        return false;
    }
    
    friend bool operator!=(const RGBA& lhs, const RGBA& rhs)
    {
        return !(lhs==rhs);
    }
};

#endif
