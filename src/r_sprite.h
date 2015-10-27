#ifndef R_SPRITE_H
#define R_SPRITE_H
#include <SDL2/SDL.h>
#include "r_entity/r_entity.h"
#include "r_entity/r_component.h"
#include "r_util_components.h"
#include "r_animation.h"
#include "r_texture.h"

struct SpriteComponent : public Component
{
    TextureComponent *texture;
    AnimationComponent *animations;
    SDL_Color fgColor;
    SDL_Color bgColor;
    SDL_Rect dimensions;
    
    int renderOffsetX, renderOffsetY;
    float angle;
    SDL_RendererFlip flip;
    SDL_Point center;

    void Init( TextureComponent *textureComponent,  AnimationComponent *animationComponent, SDL_Rect dimensions, SDL_Color foregroundColor, SDL_Color backgroundColor);
};

COMPONENT_REGISTER(SpriteComponent, "SpriteComponent");

struct SpriteSystem: public System<SpriteComponent>
{
    void AddComponent(EntityID ownerID, 
                        TextureComponent *textureComponent,
                        AnimationComponent *animationComponent,
                        SDL_Rect dimensions,
                        SDL_Color fgColor = {0xFF,0xFF,0xFF,0xFF},
                        SDL_Color bgColor = {0x00,0x00,0x00,0x00});
};

#endif
