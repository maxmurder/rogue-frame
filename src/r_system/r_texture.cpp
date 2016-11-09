#include "r_texture.h"
#include "r_entity/r_entity.h"
#include "r_utils/r_SDL.h"
#include "r_utils/r_logging.h"

TextureComponent::TextureComponent() : Component()
{
    texture = NULL;
    width = 0;
    height = 0;
}

void TextureSystem::LoadFromFile( EntityID ownerID, std::string path, SDL_Renderer* renderer, SDL_Color clipping)
{
    if(GetEntity(ownerID) != NULL)
    {
        FreeTexture(ownerID);
        if(clipping.a > 0)
        {
            components[ownerID]->texture = r_SDL::LoadTexture( path, renderer, clipping.r, clipping.g, clipping.b );
        }else
        {
            components[ownerID]->texture = r_SDL::LoadTexture( path, renderer);
        }
        if(components[ownerID]->texture != NULL)
        {
            SDL_QueryTexture( components[ownerID]->texture, NULL, NULL, &components[ownerID]->width, &components[ownerID]->height );
        }else
        {
            R_LOG(r_logging::ERROR) << "Texture could not load :: " << SDL_GetError();
        }
    }else
    {
        R_LOG(r_logging::ERROR)  << "Texture could not load :: invalid EntityID";
    }
}

void TextureSystem::RenderUnicode( EntityID ownerID, SDL_Renderer* renderer, TTF_Font* font, uint16_t text[], SDL_Color color )
{
    if(GetEntity(ownerID) != NULL)
    {
        FreeTexture(ownerID);
        components[ownerID]->texture = r_SDL::RenderUnicode(text, font, renderer, components[ownerID]->texture, color);
        if (components[ownerID]->texture == NULL)
        {
            R_LOG(r_logging::WARNING) << "Symbol could not be rendered :: " << SDL_GetError();
        } else
        {
            SDL_QueryTexture( components[ownerID]->texture, NULL, NULL, &components[ownerID]->width, &components[ownerID]->height );
        }
    }
}

void TextureSystem::Cleanup()
{
    for (auto &tex : components)
    {
        if (tex.second->texture != NULL)
        {
            SDL_DestroyTexture (tex.second->texture);
        }
        r_component::Destroy(tex.second);
    }
    components.clear();
}

void TextureSystem::FreeTexture(EntityID ownerID)
{
    if(GetEntity(ownerID) != NULL)
    {
        if (components[ownerID]->texture != NULL)
        {
            SDL_DestroyTexture (components[ownerID]->texture);
            components[ownerID]->texture = NULL;
            components[ownerID]->width = 0;
            components[ownerID]->height = 0;
        }
    }
}
