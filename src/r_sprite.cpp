#include "r_sprite.h"

using namespace std;

void SpriteComponent::Init( EntityID textureComponent, EntityID animationComponent, EntityID dimensionsComponent, EntityID foregroundColor, EntityID backgroundColor )
{
    texture = textureComponent;
    fgColor = foregroundColor;
    bgColor = backgroundColor;
    dimensions = dimensionsComponent;
    animations = animationComponent;
    renderOffsetX = 0;
    renderOffsetY = 0;
    angle = 0.0f;
    flip = SDL_FLIP_NONE;
    center = {0,0};
}

void SpriteSystem::Init(System<RTexture> *tex, System<ColorComponent> *fg, System<ColorComponent> *bg, System<WHComponent> *dim, System<AnimationComponent> *anim)
{
    textureSystem = tex;
    fgColorSystem = fg;
    bgColorSystem = bg;
    dimensionSystem = dim;
    animationSystem = anim;
    
    init = true;
}

void SpriteSystem::AddComponent(Component *component, EntityID ownerID, EntityID textureID, EntityID animationID, EntityID dimensionsID, EntityID fgColorID, EntityID bgColorID)
{
    System::AddComponent(component, ownerID);
    components[ownerID]->Init(textureID, animationID, dimensionsID, fgColorID, bgColorID);
}

