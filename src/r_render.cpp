#include "r_render.h"
#include <iostream>

void RenderSystem::Render(SDL_Renderer *renderer)
{
    SDL_RenderClear( renderer );
    //select the top tiles to render
    for (auto &r : components)
    {
        if(GetEntity(r.first) != NULL)
        {
            //get the animation
            if(r.second->spriteComp != NULL)
            {
                //select texture frame to render
                SDL_Rect frameRect = r.second->spriteComp->GetCurrentFrame();
                if(r.second->positionComp != NULL && r.second->spriteComp->bgColor != NULL && r.second->spriteComp->fgColor != NULL)
                {
                    //select screen area to render
                    SDL_Rect renderQuad = {r.second->positionComp->x, r.second->positionComp->y, r.second->spriteComp->dimensions->w, r.second->spriteComp->dimensions->h};
                    //draw background
                    if(r.second->spriteComp->bgColor->color.a > 0)
                    {
                        SDL_SetRenderDrawColor(renderer, r.second->spriteComp->bgColor->color.r, r.second->spriteComp->bgColor->color.g, r.second->spriteComp->bgColor->color.b, r.second->spriteComp->bgColor->color.a);
                        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                        SDL_RenderFillRect(renderer, &renderQuad);
                    }
                    
                    //apply render offset
                    renderQuad.x += r.second->spriteComp->renderOffsetX;
                    renderQuad.y += r.second->spriteComp->renderOffsetY;
                    if(r.second->spriteComp->texture->GetTexture() != NULL)
                    {
                        //update the texture
                        r.second->spriteComp->texture->SetColor(r.second->spriteComp->fgColor->color.r, r.second->spriteComp->fgColor->color.g, r.second->spriteComp->fgColor->color.b);
                        r.second->spriteComp->texture->SetAlpha(r.second->spriteComp->fgColor->color.a);
                        //render to screen
                        SDL_RenderCopyEx( renderer, r.second->spriteComp->texture->GetTexture(), &frameRect, &renderQuad, r.second->spriteComp->angle, &r.second->spriteComp->center, r.second->spriteComp->flip );
                        
                        //r.second->spriteComp->texture->Render(renderer, renderQuad.x, renderQuad.y, &frameRect, r.second->spriteComp->angle, &r.second->spriteComp->center, r.second->spriteComp->flip );
                                                               
                    }else
                    {
                        std::cout << "Could not render, Missing texture." << std::endl;
                    }
                }
            }else
            {
                std::cout << "Could not render, Missing sprite." << std::endl;
            }
        }
    }
    
    SDL_RenderPresent( renderer );
}
/*
void TileRenderSystem::Render(SDL_Renderer *renderer)
{
    //select the top tiles to render
    for (auto &r : components)
    {
        if(GetEntity(r.first) != NULL)
        {
            if (r.second->render)
            {
                if(!framebuffer.empty())
                {
                    bool found = false;
                    for (auto &f : framebuffer)
                    {
                        if (f->positionComp->x == r.second->positionComp->x && f->positionComp->y == r.second->positionComp->y)
                        {
                            if(f->positionComp->z < r.second->positionComp->z)
                            {
                                f = r.second;
                            }else
                            {
                                found = true;
                            }
                        } 
                    }
                    if (!found)
                    {
                        framebuffer.push_back(r.second);
                    }
                }else
                {
                    framebuffer.push_back(r.second);
                }
            }
        }else
        {
            components.erase(r.first);
        }
    }
    
    //render the tiles
    for (auto &f : framebuffer)
    {
        //get the animation
        if (f->spriteComp != NULL)
        {
            //select texture frame to render
            SDL_Rect frameRect = { f->spriteComp->GetCurrentFrame() * f->spriteComp->cell_w, 0, f->spriteComp->cell_w, f->spriteComp->cell_h };
            if (f->positionComp != NULL && f->spriteComp->bgColor != NULL && f->spriteComp->fgColor != NULL)
            {
                //select screen area to render
                SDL_Rect renderQuad = {f->positionComp->x, f->positionComp->y, f->spriteComp->dimensions->w, f->spriteComp->dimensions->h};
                //draw background
                if (f->spriteComp->bgColor->color.a > 0)
                {
                    SDL_SetRenderDrawColor(renderer, f->spriteComp->bgColor->color.r, f->spriteComp->bgColor->color.g, f->spriteComp->bgColor->color.b, f->spriteComp->bgColor->color.a);
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_RenderFillRect(renderer, &renderQuad);
                }
                
                //apply render offset
                renderQuad.x += f->spriteComp->renderOffsetX;
                renderQuad.y += f->spriteComp->renderOffsetY;
                
                if(f->spriteComp->texture->GetTexture() != NULL)
                {
                    //update the texture
                    f->spriteComp->texture->SetColor(f->spriteComp->fgColor->color.r, f->spriteComp->fgColor->color.g, f->spriteComp->fgColor->color.b);
                    f->spriteComp->texture->SetAlpha(f->spriteComp->fgColor->color.a);
                    //render to screen
                    SDL_RenderCopyEx( renderer, f->spriteComp->texture->GetTexture(), &frameRect, &renderQuad, f->spriteComp->angle, &f->spriteComp->center, f->spriteComp->flip );
                                                            
                }else
                {
                    std::cout << "Could not render, Missing texture." << std::endl;
                }
            }
        }else
        {
            std::cout << "Could not render, Missing sprite." << std::endl;
        }
    }
    
    SDL_RenderPresent( renderer );
    
    framebuffer.clear();
}
*/
