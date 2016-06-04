#ifndef R_TEXTURE_H
#define R_TEXTURE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "r_entity/r_component.h"

struct TextureComponent : public Component
{
    SDL_Texture *texture;
    int width, height;
    
    TextureComponent();
};

COMPONENT_REGISTER( TextureComponent, "TextureComponent");

struct TextureSystem : public System<TextureComponent>
{
    void LoadFromFile( EntityID ownerID, std::string path, SDL_Renderer* renderer, SDL_Color clipping = {0x00, 0x00, 0x00, 0x00});
    void RenderUnicode( EntityID ownerID, SDL_Renderer* renderer, TTF_Font* font, uint16_t text[], SDL_Color color = {0xFF,0xFF,0xFF,0xFF} );
    void Cleanup();
    void FreeTexture( EntityID ownerID);
};

#endif
