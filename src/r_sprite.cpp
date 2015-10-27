#include "r_sprite.h"

using namespace std;

void SpriteComponent::Init( TextureComponent *textureComponent,  AnimationComponent *animationComponent, SDL_Rect dimensions, SDL_Color foregroundColor, SDL_Color backgroundColor)
{
    texture = textureComponent;
    fgColor = foregroundColor;
    bgColor = backgroundColor;
    dimensions = dimensions;
    animations = animationComponent;
    renderOffsetX = 0;
    renderOffsetY = 0;
    angle = 0.0f;
    flip = SDL_FLIP_NONE;
    center = {0,0};
}

void SpriteSystem::AddComponent(EntityID ownerID, TextureComponent *textureComponent, AnimationComponent *animationComponent, SDL_Rect dimensions, SDL_Color fgColor, SDL_Color bgColor)
{
    System::AddComponent( r_component::Create("SpriteComponent", ownerID) , ownerID);
    components[ownerID]->Init(textureComponent, animationComponent, dimensions, fgColor, bgColor);
}

