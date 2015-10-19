#include "r_sprite.h"

using namespace std;

//std::map<std::string, std::vector<SDL_Rect>> animations;

void SpriteComponent::Init( RTexture *textureComponent, AnimationComponent *animationComponent, WHComponent *dimensionsComponent, ColorComponent *foregroundColor, ColorComponent *backgroundColor )
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

SpriteComponent::SpriteComponent() : Component()
{

    texture = NULL;
    fgColor = NULL;
    bgColor = NULL;
    dimensions = NULL;
    animations = NULL;
    renderOffsetX = 0;
    renderOffsetY = 0;
    angle = 0.0f;
    flip = SDL_FLIP_NONE;
    center = {0,0};
}

void SpriteSystem::AddComponent(Component *component, EntityID ownerID, RTexture *textureComponent, AnimationComponent *animationComponent, WHComponent *dimensionsComponent, ColorComponent *foregroundColorComponent, ColorComponent *backgroundColorComponent)
{
    System::AddComponent(component, ownerID);
    components[ownerID]->Init(textureComponent, animationComponent, dimensionsComponent, foregroundColorComponent, backgroundColorComponent);
}

