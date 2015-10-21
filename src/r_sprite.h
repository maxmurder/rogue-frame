#ifndef R_SPRITE_H
#define R_SPRITE_H
#include "r_entity/r_entity.h"
#include "r_entity/r_component.h"
#include "r_util_components.h"
#include "RTexture.h"
#include "r_animation.h"

struct SpriteComponent : public Component
{
    EntityID texture;
    EntityID fgColor;
    EntityID bgColor;
    EntityID dimensions;
    EntityID animations;
    
    int renderOffsetX, renderOffsetY;
    float angle;
    SDL_RendererFlip flip;
    SDL_Point center;

    void Init( EntityID textureComponent,  EntityID animationComponent, EntityID dimensionsComponent, EntityID foregroundColorComponent, EntityID backgroundColorComponent);
};

COMPONENT_REGISTER(SpriteComponent, "SpriteComponent");

struct SpriteSystem: public System<SpriteComponent>
{
    System<RTexture> *textureSystem;
    System<ColorComponent> *fgColorSystem;
    System<ColorComponent> *bgColorSystem;
    System<WHComponent> *dimensionSystem;
    System<AnimationComponent> *animationSystem;
    
    void Init(System<RTexture> *textureSys, System<ColorComponent> *fgColorSys, System<ColorComponent> *bgColorSys, System<WHComponent> *dimensionSys, System<AnimationComponent> *animationSys);
    
    void AddComponent(Component *component, 
                        EntityID ownerID, 
                        EntityID textureID,
                        EntityID animationID,
                        EntityID dimensionsID, 
                        EntityID foregroundColorID, 
                        EntityID backgroundColorID);
    private:
        bool init;
};

#endif
