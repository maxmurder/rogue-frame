#include "r_sprite.h"

using namespace std;

std::map<std::string, std::vector<SDL_Rect>> animations;

void SpriteComponent::Init( RTexture *textureComponent, WHComponent *cellDimensionsComponent, WHComponent *dimensionsComponent, ColorComponent *foregroundColor, ColorComponent *backgroundColor )
{
    texture = textureComponent;
    fgColor = foregroundColor;
    bgColor = backgroundColor;
    dimensions = dimensionsComponent;
    cellDimensions = cellDimensionsComponent;
    AddAnimation("DEFAULT", {{0,0,cellDimensions->w,cellDimensions->h}});
    currentAnimation = "DEFAULT";
    currentFrame = 0;
    renderOffsetX = 0;
    renderOffsetY = 0;
    animationSpeed = 0;
    angle = 0.0f;
    flip = SDL_FLIP_NONE;
    center = {0,0};
}

void SpriteComponent::Update()
{
    if(animationSpeed > 0)
    {
        if(frameCount > animationSpeed)
        {   
            frameCount = 0;
            currentFrame++;
            if (currentFrame >= animations[currentAnimation].size())
            {
                currentFrame = 0;
            }
        }
        frameCount++;
    }
}

void SpriteComponent::AddAnimation(std::string name, std::vector<SDL_Rect> frames)
{
    animations.insert( pair<string, vector<SDL_Rect>>(name, frames) );
}

void SpriteComponent::SetAnimation(std::string animation)
{
    currentAnimation = animation;
}

void SpriteComponent::SetFrame(int frame)
{
    currentFrame = frame;
}

SDL_Rect SpriteComponent::GetCurrentFrame()
{
    SDL_Rect f = animations[currentAnimation][currentFrame];
    return f;
}

SpriteComponent::SpriteComponent() : Component()
{

    texture = NULL;
    fgColor = 0;
    bgColor = 0;
    dimensions = NULL;
    cellDimensions = NULL;
    currentFrame = 0;
    renderOffsetX = 0;
    renderOffsetY = 0;
    animationSpeed = 0;
    angle = 0.0f;
    flip = SDL_FLIP_NONE;
    center = {0,0};
}
