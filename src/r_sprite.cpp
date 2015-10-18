#include "r_sprite.h"

void SpriteComponent::Init( RTexture *textureComponent, int cellWidth, int cellHeight, WHComponent *dimensionsComponent, ColorComponent *foregroundColor, ColorComponent *backgroundColor )
{
    cell_w = cellWidth;
    cell_h = cellHeight;
    texture = textureComponent;
    fgColor = foregroundColor;
    bgColor = backgroundColor;
    dimensions = dimensionsComponent;
    animations.insert(std::pair<std::string, std::vector<SDL_Rect>>("DEFAULT",{{0,0,cell_w,cell_h}}));
    currentAnimation = "DEFAULT";
    currentFrame = 0;
    renderOffsetX = 0;
    renderOffsetY = 0;
    animationSpeed = 0;
    angle = 0.0f;
    flip = SDL_FLIP_NONE;
    center = {cell_w/2, cell_h/2};
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
    animations[name] = frames;
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
