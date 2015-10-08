#ifndef RTEXTURE_H
#define RTEXTURE_H

#include <SDL2/SDL.h>

class RTexture
{
    public:
        
        bool LoadFromFile( std::string path, SDL_Renderer* renderer); // load from file
        bool LoadFromFile( std::string path, SDL_Renderer* renderer, int red, int green, int blue); // load from file with color keying
        void FreeTexture(); //deallocate texture
        
        void SetColor(Uint8 red, Uint8 green, Uint8 blue);//set colour modulation
        void SetBlendMode( SDL_BlendMode blending);
        void SetAlpha( Uint8 alpha );
        void Render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL); // render at point
        
        //get dimensions
        int GetWidth();
        int GetHeight();
        
        RTexture();
        ~RTexture();
    private:
        SDL_Texture* _texture;
        
        int _width;
        int _height;
};

#endif
