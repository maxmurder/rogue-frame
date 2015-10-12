#ifndef R_SDL_H
#define R_SDL_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


class r_SDL
{
    public:
        static char* ReadFile(const char* filename, int* size = NULL);
        static bool* WriteFile( const char* filename, char* data );
         
        static SDL_Surface* LoadSurface( std::string path ); //load surface from fike 
        static SDL_Surface* LoadSurface( std::string path, int red, int green, int blue ); //load surface with color keying
        static SDL_Surface* LoadSurface( std::string path , SDL_PixelFormat* format); //load optomised surface from file
        
        static SDL_Texture* LoadTexture( std::string path, SDL_Renderer* renderer ); //Load optomised texure from file
        static SDL_Texture* LoadTexture( std::string path, SDL_Renderer* renderer, int red, int green, int blue ); //Load optomised texure from file with color keying
        static TTF_Font* LoadFont( std::string path , int pointSize = 16);
        
        static SDL_Texture* RenderText( std::string string, TTF_Font* font, SDL_Renderer* renderer, SDL_Texture* texture = NULL, SDL_Color color = {0xFF,0xFF,0xFF,0xFF}); //renders a string to a texture
        static SDL_Texture* RenderUnicode( uint16_t symbols[], TTF_Font* font, SDL_Renderer* renderer, SDL_Texture* texture = NULL, SDL_Color color = {0xFF,0xFF,0xFF,0xFF}); // renders a unicode symbol
        static void ApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination ); // apply sdl surface
};

#endif
