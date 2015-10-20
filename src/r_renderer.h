#ifndef R_RENDERER_H
#define R_RENDERER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct RenderObject
{
    SDL_Texture *texture;
    SDL_Rect sourceRect;
    SDL_Rect destRect;
    SDL_Color fgColor;
    SDL_Color bgColor;
    float angle;
    SDL_Point center;
    SDL_Point offset;
    SDL_RendererFlip flip;
    
    RenderObject(SDL_Texture *texture, 
                SDL_Rect sourceRect, 
                SDL_Rect destRect, 
                SDL_Color fgColor,
                SDL_Color bgColor,
                SDL_Point offset,
                float angle, 
                SDL_Point center, 
                SDL_RendererFlip flip);
};

namespace r_renderer
{
    void AddToQueue(SDL_Texture *texture, 
                    SDL_Rect sourceRect,
                    SDL_Rect destRect, 
                    SDL_Color fgColor = {0xFF, 0xFF, 0xFF, 0xFF},
                    SDL_Color bgColor = {0xFF, 0xFF, 0xFF, 0x00},
                    SDL_Point offset = {0,0},
                    float angle = 0.0f,
                    SDL_Point center = {0,0},
                    SDL_RendererFlip flip = SDL_FLIP_NONE);
    void Render(SDL_Renderer *renderer);
};
#endif
