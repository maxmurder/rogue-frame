#ifndef RTEXTURE_H
#define RTEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class RTexture
{
    public:
        
        bool LoadFromFile( std::string path, SDL_Renderer* renderer); // load from file
        bool LoadFromFile( std::string path, SDL_Renderer* renderer, int red, int green, int blue); // load from file with color keying
        void RenderText( SDL_Renderer* renderer, std::string string, TTF_Font* font, SDL_Color textColor = {0,0,0,0} ); //Renders a string to the texture

        void FreeTexture(); //deallocate texture
        
        void SetColor(uint8_t red, uint8_t green, uint8_t blue);//set colour modulation
        void SetAlpha( uint8_t alpha );
        void SetBlendMode( SDL_BlendMode blending);
        void Render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE ); // render at point
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
