#ifndef R_SPRITE_H
#define R_SPRITE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <map>
#include "r_entity/r_entity.h"
#include "r_entity/r_component.h"
#include "r_util_components.h"
#include "r_animation.h"

struct SpriteComponent : public Component
{
    RTexture *texture;
    ColorComponent *fgColor;
    ColorComponent *bgColor;
    WHComponent *dimensions;
    AnimationComponent *animations;
    
    int renderOffsetX, renderOffsetY;
    float angle;
    SDL_RendererFlip flip;
    SDL_Point center;

    void Init( RTexture *textureComponent,  AnimationComponent *animationComponent, WHComponent *dimensionsComponent, ColorComponent *foregroundColorComponent, ColorComponent *backgroundColorComponent);
    
    SpriteComponent();
};

COMPONENT_REGISTER(SpriteComponent, "SpriteComponent");

struct SpriteSystem: public System<SpriteComponent>
{
    void AddComponent(Component *component, 
                        EntityID ownerID, 
                        RTexture *textureComponent,
                        AnimationComponent *animationComponent, 
                        WHComponent *dimensionsComponent, 
                        ColorComponent *foregroundColorComponent, 
                        ColorComponent *backgroundColorComponent);
};

#endif
