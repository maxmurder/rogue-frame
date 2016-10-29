#include "r_renderer.h"
#include <vector>
#include <iostream>

std::vector<RenderObject> renderQueue;

RenderObject::RenderObject(SDL_Texture *tex, SDL_Rect sRect, SDL_Rect dRect, SDL_Color fg, SDL_Color bg, SDL_Point off, float ang, SDL_Point cen,SDL_RendererFlip fli)
{
    texture = tex;
    sourceRect = sRect;
    destRect = dRect;
    fgColor = fg;
    bgColor = bg;
    angle = ang;
    center = cen;
    offset = off;
    flip = fli;
}


void r_renderer::AddToQueue(SDL_Texture *texture, SDL_Rect sourceRect, SDL_Rect destRect, SDL_Color fgColor, SDL_Color bgColor, SDL_Point offset, float angle, SDL_Point center, SDL_RendererFlip flip)
{
    renderQueue.push_back(RenderObject(texture, sourceRect, destRect, fgColor, bgColor, offset, angle, center, flip));
}

void r_renderer::Render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear( renderer );
    while(!renderQueue.empty())
    {    
        SDL_Rect frame = renderQueue.back().destRect;
        //render the background
        if(renderQueue.back().bgColor.a > 0)
        {
            SDL_SetRenderDrawColor(renderer, renderQueue.back().bgColor.r, renderQueue.back().bgColor.g, renderQueue.back().bgColor.b, renderQueue.back().bgColor.a);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_RenderFillRect(renderer, &frame);    
        }
        
        //prepare the texture copy rect
        frame.x += renderQueue.back().offset.x;
        frame.y += renderQueue.back().offset.y;
        frame.w = renderQueue.back().sourceRect.w;
        frame.h = renderQueue.back().sourceRect.h;
        
        SDL_SetTextureColorMod( renderQueue.back().texture, renderQueue.back().fgColor.r, renderQueue.back().fgColor.g, renderQueue.back().fgColor.b );
        SDL_SetTextureAlphaMod( renderQueue.back().texture, renderQueue.back().fgColor.a );
        
        SDL_RenderCopyEx(renderer, renderQueue.back().texture, &renderQueue.back().sourceRect, &renderQueue.back().destRect, renderQueue.back().angle, &renderQueue.back().center, renderQueue.back().flip);
        renderQueue.pop_back();
    }
    SDL_RenderPresent( renderer );
}
