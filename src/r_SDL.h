#ifndef R_SDL_H
#define R_SDL_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


namespace r_SDL
{
         char* ReadFile(const char* filename, int* size = NULL); //reads a file at filename
         bool WriteFile( const char* filename, const char* data ); // writes/creates a file at filename
         
         SDL_Surface* LoadSurface( std::string path ); //load surface from fike 
         SDL_Surface* LoadSurface( std::string path, int red, int green, int blue ); //load surface with color keying
         SDL_Surface* LoadSurface( std::string path , SDL_PixelFormat* format); //load optomised surface from file
        
         SDL_Texture* LoadTexture( std::string path, SDL_Renderer* renderer ); //Load optomised texure from file
         SDL_Texture* LoadTexture( std::string path, SDL_Renderer* renderer, int red, int green, int blue ); //Load optomised texure from file with color keying
         TTF_Font* LoadFont( std::string path , int pointSize = 16);
        
         SDL_Texture* RenderText( std::string string, TTF_Font* font, SDL_Renderer* renderer, SDL_Texture* texture = NULL, SDL_Color color = {0xFF,0xFF,0xFF,0xFF}); //renders a string to a texture
         SDL_Texture* RenderUnicode( uint16_t symbols[], TTF_Font* font, SDL_Renderer* renderer, SDL_Texture* texture = NULL, SDL_Color color = {0xFF,0xFF,0xFF,0xFF}); // renders a unicode symbol
         void ApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination ); // apply sdl surface
        
         std::string TextInputHandler( SDL_Event &event, std::string inputString ); //fills a string with inputString + current event keyboard input.
};

#endif
